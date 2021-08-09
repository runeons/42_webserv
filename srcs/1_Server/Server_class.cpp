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
				<< "[Host : " <<  _config->getHost() << "] "
				<< "[Port : " <<  _config->getPort() << "] "
				<< "[Dir  : " <<  _config->getRootDir() << "]"
				<< C_RES << std::endl;
	return ;
}

// ********************************************* ::socket() + ::setsockopt() *********************************************

void		Server::create_server_socket()
{
	int option = 1;

	_master_socket = ::socket(AF_INET, SOCK_STREAM, 0);
	if (::setsockopt(_master_socket, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option)) < 0)
	{
		perror("___setsockopt___");
		throw Exceptions::BindServer(); // change exception
	}
	// _master_socket = -1;
	if (_master_socket == -1)
		throw Exceptions::ServerSocket();
	std::cout << GREEN << "Server socket created !" <<  C_RES << std::endl;
}

// ********************************************* ::bind() *********************************************

void		Server::bind_address_and_port()
{
	if (::bind(_master_socket, reinterpret_cast<const struct sockaddr *>(&_address), sizeof(_address)) == -1)
	{
		perror("___bind___");
		throw Exceptions::BindServer();
	}
	std::cout << GREEN << "Address " << inet_ntoa(_address.sin_addr) << " and port " << _config->getPort() << " bound !" <<  C_RES << std::endl;
}

// ********************************************* ::accept() + Client.treat_client() *********************************************

void Server::listen_connections(void)
{
	// MAX CLIENTS = plutot MAX PENDING CONNECTIONS ?
	// fcntl(_master_socket, F_SETFL, O_NONBLOCK);
	if (::listen(_master_socket, MAX_CLIENTS) == -1)
		throw Exceptions::ServerListen();
	std::cout << GREEN << "Server waiting for connections..." <<  C_RES << std::endl;
}

void Server::accept_new_connection(int server_socket)
{
	std::cerr << GREEN << "accepting_" << C_G_GREEN << "new" << C_RES << GREEN << "_connection on server_socket " << C_G_GREEN << server_socket << C_RES << std::endl;
	Client *cl = new Client(*_config); // dans lequel j'envoie Config
	int client_socket = ::accept(_master_socket, NULL, NULL);
	if (client_socket < 0)
	{
		perror("___accept___");
		exit(EXIT_FAILURE);
	}
	cl->setSocket(client_socket);
	fcntl(client_socket, F_SETFL, O_NONBLOCK);
	_clients_map[client_socket] = cl;
	std::cout << YELLOW << "New connection accepted from fd " << C_G_YELLOW << client_socket << C_RES << YELLOW << " to " << inet_ntoa(_address.sin_addr) << ":" << ntohs(_address.sin_port) << C_RES << std::endl;
	FD_SET(client_socket, &_read_fds);
	if (_max_fd < client_socket)
		_max_fd = client_socket;
	std::cout << C_G_YELLOW << client_socket << C_RES << YELLOW << " added to _clients_map and _read_fds" << C_RES << std::endl;
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
	std::cerr << GREEN << "receive_and_process_request" << C_G_GREEN << " (existing_connection)" << C_RES << GREEN << " : reading on already-connected socket " << C_G_GREEN << client_socket << C_RES << std::endl;

	_clients_map[client_socket]->receive_request(); // recv
	std::cerr << YELLOW << "remaining_bytes_to_recv on socket " << C_G_YELLOW << client_socket << " : " << _clients_map[client_socket]->get_remaining_bytes_to_recv() << C_RES << std::endl;
	if (_clients_map[client_socket]->get_remaining_bytes_to_recv() == 0)
	{
		_clients_map[client_socket]->check_request(); // check if request OK
		// gerer les erreurs / exceptions
		_clients_map[client_socket]->translate_path();
		_clients_map[client_socket]->read_resource();
		_clients_map[client_socket]->generate_response();
		FD_SET(client_socket, &_write_fds);
		if (_max_fd < client_socket)
			_max_fd = client_socket;
	}
}

void Server::prepare_and_send_response(int client_socket)
{
	std::cerr << GREEN << "prepare_and_send_response " << C_G_GREEN << " (writing)" << C_RES << GREEN << " on socket " << C_G_GREEN << client_socket << C_RES << std::endl;
	_clients_map[client_socket]->send_response();
	// std::cerr << C_G_RED << "[ DEBUG _total_bytes_to_send     ] " << C_RES << _clients_map[client_socket]->get_total_bytes_to_send() << std::endl;
	// std::cerr << C_G_RED << "[ DEBUG _remaining_bytes_to_send ] " << C_RES << _clients_map[client_socket]->get_remaining_bytes_to_send() << std::endl;
	if (_clients_map[client_socket]->get_remaining_bytes_to_send() <= 0)
	{
		FD_CLR(client_socket, &_read_fds);
		FD_CLR(client_socket, &_write_fds);
		if (_max_fd == client_socket)
		_max_fd--;
		close(client_socket);
	}
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
			perror("___select___");
			exit (EXIT_FAILURE);
		}
		// Accept new connection - Server loop
		if (FD_ISSET(_master_socket, &read_fds)) // si incoming NEW connection
			accept_new_connection(_master_socket);
		std::map<int, Client *>::iterator it;
		for (it = _clients_map.begin(); it != _clients_map.end(); it++) //client_loop - pour chaque client existant
		{
			if (FD_ISSET(it->first, &read_fds)) // read() possible
				receive_and_process_request(it->first);
			if (FD_ISSET(it->first, &write_fds)) // write() possible
				prepare_and_send_response(it->first);
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
	catch (std::exception & e)
	{
		std::cerr << RED << e.what() <<  C_RES << std::endl;
		this->stop_server();
		return (1);
	}
	return (0);
}