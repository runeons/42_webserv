
# include <webserv.hpp>

// ********************************************* server utils *********************************************

void		Server::stop_server()
{
	std::cerr << GREY << "Server shut down" <<  C_RES << std::endl;
	close(_master_socket); // pas besoin de protéger le close parce qu'on va quitter le programme
}

void Server::print_config(void)
{
	std::cout	<< ORANGE
				<< "[SERVER] <" << _config->get__host() << ":" << _config->get__port() << "> : "
				<< "root=\""
				<< _config->get__root_dir()
				<< "\""
				<< C_RES << std::endl;
	return ;
}

// ********************************************* ::socket() + ::setsockopt() *********************************************

void		Server::create_server_socket()
{
	int option = 1;

	_master_socket = ::socket(AF_INET, SOCK_STREAM, 0);
	if (::setsockopt(_master_socket, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option)) < 0)
		throw (Exceptions::ServerException("set socket option"));
	// _master_socket = -1;
	if (_master_socket == -1)
		throw (Exceptions::ServerException("Master socket not created"));
	// std::cout << GREEN << "Server socket created !" <<  C_RES << std::endl;
}

// ********************************************* ::bind() *********************************************

void		Server::bind_address_and_port()
{
	if (::bind(_master_socket, reinterpret_cast<const struct sockaddr *>(&_address), sizeof(_address)) == -1)
		throw (Exceptions::ServerException("Cannot bind address and port on master socket"));
	// std::cout << GREEN << "Server ready at <" << inet_ntoa(_address.sin_addr) << ":" << _config->get__port() << ">" <<  C_RES << std::endl;
}

// ********************************************* ::accept() + Client.treat_client() *********************************************

void Server::listen_connections(void)
{
	// MAX CLIENTS = plutot MAX PENDING CONNECTIONS ?
	// fcntl(_master_socket, F_SETFL, O_NONBLOCK); // TOCHECK - only client sockets must be O_NONBLOCK ?
	if (::listen(_master_socket, MAX_CLIENTS) == -1)
		throw (Exceptions::ServerException("Server failed to listen"));
	std::cout << GREEN << "[SERVER] <" << _config->get__host() << ":" << _config->get__port() << "> : listening" << C_RES << std::endl;
}

void Server::accept_new_connection(int server_socket)
{
	// std::cerr << GREY << "[SERVER] : accepting new connection on server_socket " << server_socket << C_RES << std::endl;
	(void)server_socket;
	Client *cl = new Client(*_config); // dans lequel j'envoie Config
	int client_socket = ::accept(_master_socket, NULL, NULL);
	if (client_socket < 0)
		throw (Exceptions::ServerException("Server failed to accept connection"));
	cl->setSocket(client_socket);
	if (fcntl(client_socket, F_SETFL, O_NONBLOCK) == -1)
		throw (Exceptions::ServerException("Client socket non blocking option failure (fcntl)")); // TOCHECK to move in Client ?
	_clients_map[client_socket] = cl;
	std::cerr << GREEN << "[SERVER] <" << _config->get__host() << ":" << _config->get__port() << "> : accepting new connection from socket <" << client_socket << ">" << C_RES << std::endl;
	FD_SET(client_socket, &_read_fds);
	if (_max_fd < client_socket)
		_max_fd = client_socket;
	// std::cout << GREY << "[SERVER] : " << client_socket << " added to _clients_map and _read_fds" << C_RES << std::endl;
}

void Server::init_fd_sets(void)
{
	FD_ZERO(&_read_fds);
	FD_ZERO(&_write_fds);
	FD_SET(_master_socket, &_read_fds);
	_max_fd = _master_socket;
}

void Server::receive_and_process_request(int client_socket)
{
	std::cerr << std::endl << GREEN << "[SERVER] <" << _config->get__host() << ":" << _config->get__port() << "> : reading on already connected socket <" << client_socket << ">" << C_RES << std::endl;
	_clients_map[client_socket]->receive_request(); // recv
	if (_clients_map[client_socket]->get_remaining_bytes_to_recv())
		std::cerr << YELLOW << "[SERVER] <" << _config->get__host() << ":" << _config->get__port() << "> : chunked request in progress on socket <" << client_socket << ">" << C_RES << std::endl;
	if (_clients_map[client_socket]->get_remaining_bytes_to_recv() == 0 && _clients_map[client_socket]->getRequest().find(""PAT_CRLF""PAT_CRLF) != std::string::npos)
	{
		if (_clients_map[client_socket]->is_response_successful())
			_clients_map[client_socket]->check_request(); // check if request OK
		if (_clients_map[client_socket]->is_response_successful())
			_clients_map[client_socket]->apply_location(); // 404 if error
		if (_clients_map[client_socket]->is_response_successful())
			_clients_map[client_socket]->adjust_applied_location();
		if (_clients_map[client_socket]->is_response_successful())
			_clients_map[client_socket]->translate_path(); // 500 if can't exec tree for autoindex
		if (_clients_map[client_socket]->is_response_successful())
			_clients_map[client_socket]->read_resource();
		_clients_map[client_socket]->generate_response();
		FD_SET(client_socket, &_write_fds);
		if (_max_fd < client_socket)
			_max_fd = client_socket;
	}
}

void Server::shutdown_client_socket(int client_socket)
{
	FD_CLR(client_socket, &_read_fds);
	FD_CLR(client_socket, &_write_fds);
	if (_max_fd == client_socket)
		_max_fd--;
	close(client_socket);
}


void Server::prepare_and_send_response(int client_socket)
{
	std::cerr << GREEN << "[SERVER] <" << _config->get__host() << ":" << _config->get__port() << "> : writing on already connected socket <" << client_socket << ">" << C_RES << std::endl;
	_clients_map[client_socket]->send_response();
	if (_clients_map[client_socket]->get_remaining_bytes_to_send() <= 0)
		shutdown_client_socket(client_socket);
}

void Server::select_and_treat_connections(void)
{
	init_fd_sets();
	while (1)
	{
		fd_set read_fds = _read_fds;
		fd_set write_fds = _write_fds;

		int socketCount = ::select(_max_fd + 1, &read_fds, &write_fds, NULL, NULL);
		if (socketCount < 0)
			throw (Exceptions::ServerException("Select failure"));
		// Accept new connection - Server loop
		if (FD_ISSET(_master_socket, &read_fds)) // si incoming NEW connection
			accept_new_connection(_master_socket);
		std::map<int, Client *>::iterator it;
		for (it = _clients_map.begin(); it != _clients_map.end(); it++) // client_loop - pour chaque client existant
		{
			try
			{
				if (FD_ISSET(it->first, &read_fds)) // read / recv() possible
					receive_and_process_request(it->first);
				if (FD_ISSET(it->first, &write_fds)) // write / send() possible
					prepare_and_send_response(it->first);
			}
			catch (Exceptions::ClientException & e)
			{
				std::cerr << RED << e.what() <<  C_RES << std::endl;
				shutdown_client_socket(it->first);
				_clients_map.erase(it);
				break;
			}
		}
	}
}

// ********************************************* main - launch() *********************************************

int		Server::launch(void)
{
	try
	{
		print_config();
		create_server_socket();
		bind_address_and_port();
		listen_connections();
		select_and_treat_connections();
	}
	catch (Exceptions::ServerException & e)
	{
		std::cerr << RED << e.what() <<  C_RES << std::endl;
		this->stop_server();
		return (1);
	}
	return (0);
}