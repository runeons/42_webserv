
# include <webserv.hpp>

// ********************************************* server utils *********************************************

void		Server::stop_server()
{
	// TO DO : close all clients too ? close only port with issue ?
	std::cerr << C_HIDDEN << "Server shut down (close all servers_sockets)" <<  C_RES << std::endl;
	std::map<int, Config>::iterator it = _servers_map.begin();
	for (; it != _servers_map.end(); it++)
		stop_one_server(it->first);
}

void		Server::stop_one_server(int server_socket)
{
	// TO DO : close all clients too ? close only port with issue ?
	std::cerr << C_HIDDEN << "Server on socket " << server_socket << " shut down" <<  C_RES << std::endl;
	int ret = close(server_socket);
	if (ret == -1)
	{
		std::cerr << C_G_RED << "Error: " << C_G_WHITE << " server socket closing failure - quitting program" << C_RES << std::endl;
		exit(EXIT_FAILURE);
	}
}

// ********************************************* init servers : socket + bind + listen *********************************************

int		Server::create_server_socket()
{
	int option = 1;
	int	server_socket = 0;

	server_socket = ::socket(AF_INET, SOCK_STREAM, 0);
	int ret = ::setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
	if (ret < 0)
		throw (Exceptions::ServerException("set socket option"));
	if (server_socket == -1)
		throw (Exceptions::ServerException("Server socket not created"));
	return (server_socket);
}

std::map<int, Config> Server::init_servers_map()
{
	std::map<int, Config> m;

	std::vector<Config>::iterator it = _config_vec.begin();
	std::vector<Config>::iterator it_end= _config_vec.end();

	for (; it != it_end; it++)
	{
		// create socket
		int					server_socket = create_server_socket();
		try
		{
			struct sockaddr_in	address;
			// bind address and port
			address.sin_family = AF_INET;
			address.sin_addr.s_addr = INADDR_ANY;
			if (inet_aton((*it).get__host().c_str(), &address.sin_addr) <= 0)
				throw (Exceptions::ServerException("Server invalid address"));
			address.sin_port = htons((*it).get__port());
			if (::bind(server_socket, reinterpret_cast<const struct sockaddr *>(&address), sizeof(address)) == -1)
				throw (Exceptions::ServerException("Cannot bind address and port on server socket"));
				// listen
			if (::listen(server_socket, MAX_CLIENTS) == -1)
				throw (Exceptions::ServerException("Server failed to listen"));
			m[server_socket] = *it;
			std::cout << C_SERVER << "[SERVER] <" << (*it).get__host() << ":" << (*it).get__port() << "> : listens new connections" << C_RES << std::endl;
		}
		catch (Exceptions::ServerException & e)
		{
			std::cerr << C_G_RED << "Error: " << C_G_WHITE << e.what() << C_RES << std::endl;
			stop_one_server(server_socket);
		}
	}
	return m;
}

// ********************************************* select_and_treat_connections *********************************************

void Server::accept_new_connection(int server_socket, Config & config)
{
	Client *cl = new Client(config); // dans lequel j'envoie Config
	int client_socket = ::accept(server_socket, NULL, NULL);
	if (client_socket < 0)
		throw (Exceptions::ServerException("Server failed to accept connection"));

	cl->set__socket(client_socket);
	if (fcntl(client_socket, F_SETFL, O_NONBLOCK) == -1)
		throw (Exceptions::ServerException("Client socket non blocking option failure (fcntl)"));
	_clients_map[client_socket] = cl;
	std::cerr << C_G_RED << "CREATION: " << C_G_WHITE << "_clients_map[" << client_socket << "]" << C_RES << std::endl;
	std::cerr << C_SERVER << "[SERVER] <" << config.get__host() << ":" << config.get__port() << "> : accepting new connection from socket <" << client_socket << ">" << C_RES << std::endl;
	FD_SET(client_socket, &_read_fds);
	if (_max_fd < client_socket)
		_max_fd = client_socket;
}

void Server::init_fd_sets(void)
{
	FD_ZERO(&_read_fds);
	FD_ZERO(&_write_fds);
	std::map<int, Config>::iterator it = _servers_map.begin();
	std::map<int, Config>::iterator it_end = _servers_map.end();
	for (; it != it_end; it++)
	{
		FD_SET(it->first, &_read_fds);
		if (it->first > _max_fd)
			_max_fd = it->first;
	}
}

void Server::receive_and_process_request(int client_socket)
{
	std::cerr << std::endl << C_SERVER << "[SERVER] <" << _clients_map[client_socket]->get__config().get__host() << ":" << _clients_map[client_socket]->get__config().get__port() << "> : reading on already connected socket <" << client_socket << ">" << C_RES << std::endl;
	_clients_map[client_socket]->receive_request(); // recv
	if (_clients_map[client_socket]->get__remaining_bytes_to_recv())
		std::cerr << C_OTHER << "[SERVER] <" << _clients_map[client_socket]->get__config().get__host() << ":" << _clients_map[client_socket]->get__config().get__port() << "> : chunked request in progress on socket <" << client_socket << ">" << C_RES << std::endl;
	if (_clients_map[client_socket]->get__remaining_bytes_to_recv() == 0 && (_clients_map[client_socket]->get__request().find(""PAT_CRLF""PAT_CRLF) != std::string::npos || !(_clients_map[client_socket]->is_response_successful()))) // dernier condition, importante si requete jamais recue par exemple et qu'on veut retourner quand meme une reponse (500)
	{
		if (_clients_map[client_socket]->is_response_successful())
			_clients_map[client_socket]->check_request(); // check if request OK
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
	int ret = close(client_socket);
	if (ret == -1)
	{
		std::cerr << C_G_RED << "Error: " << C_G_WHITE << " client socket closing failure - quitting program" << C_RES << std::endl;
		exit(EXIT_FAILURE);
	}
	std::cerr << C_G_RED << "DESTRUCTION: " << C_G_WHITE << " delete _clients_map[" << client_socket << "]" << C_RES << std::endl;
	delete _clients_map[client_socket];
}

void Server::prepare_and_send_response(int client_socket)
{
	std::cerr << C_SERVER << "[SERVER] <" << _clients_map[client_socket]->get__config().get__host() << ":" << _clients_map[client_socket]->get__config().get__port() << "> : writing on already connected socket <" << client_socket << ">" << C_RES << std::endl;
	_clients_map[client_socket]->send_response();
	if (_clients_map[client_socket]->get__remaining_bytes_to_send() <= 0)
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
		{
			if (signal_caught == true)
				throw(Exceptions::ServerException("Connexion closed by system"));
			throw(Exceptions::ServerException("Select failure"));
		}
		// Accept new connection - for each server
		std::map<int, Config>::iterator it_server = _servers_map.begin();
		for (; it_server != _servers_map.end(); it_server++)
		{
			if (FD_ISSET(it_server->first, &read_fds)) // si incoming NEW connection
				accept_new_connection(it_server->first, it_server->second);
		}
		std::map<int, Client *>::iterator it;
		for (it = _clients_map.begin(); it != _clients_map.end(); it++) // treat connection pour chaque client existant
		{
			try
			{
				if (FD_ISSET(it->first, &read_fds)) // something to read / recv()
					receive_and_process_request(it->first);
				if (FD_ISSET(it->first, &write_fds)) // something to write / send()
					prepare_and_send_response(it->first);
			}
			catch (Exceptions::ClientException & e)
			{
				std::cerr << C_ERROR << e.what() <<  C_RES << std::endl;
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
		_servers_map = init_servers_map();
		select_and_treat_connections();
	}
	catch (Exceptions::ServerException & e)
	{
		std::cerr << C_ERROR << e.what() <<  C_RES << std::endl;
		this->stop_server();
		if (signal_caught)
			return (0);
		return (1);
	}
	return (0);
}
