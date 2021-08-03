/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantoni <tsantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 18:41:53 by tsantoni          #+#    #+#             */
/*   Updated: 2021/08/03 14:07:54 by tsantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (::listen(_master_socket, MAX_CLIENTS) == -1)
		throw Exceptions::ServerListen();
	std::cout << GREEN << "Server waiting for connections..." <<  C_RES << std::endl;
}

int read_from_client (int filedes)
{
	char	buffer[CHUNK];
	int		nbytes;

	nbytes = read(filedes, buffer, CHUNK);
	if (nbytes < 0)
	{
		perror("___read___");
		exit (EXIT_FAILURE);
	}
	else if (nbytes == 0) // End-of-file
		return -1;
	else // Data read
	{
		std::cerr << C_G_RED << "[ DEBUG read from existing client ] " << C_RES << "[" << buffer << "]" << std::endl;
		return 0;
	}
}

void Server::treat_incoming_new_connection_for_reading(int socket)
{
	socklen_t	addrlen = sizeof(_address);

	std::cerr << GREEN << "treat_incoming_" << C_G_GREEN << "new" << C_RES << GREEN << "_connection_for_reading on master socket " << C_G_GREEN << socket << C_RES << std::endl;
	Client *cl = new Client(*_config); // dans lequel j'envoie Config
	_clients.push_back(cl);
	cl->setSocket(::accept(_master_socket, reinterpret_cast<struct sockaddr *>(&_address), reinterpret_cast<socklen_t *>(&addrlen)));
	if (cl->getSocket() < 0)
	{
		perror("___accept___");
		exit(EXIT_FAILURE);
	}
	_sockets_used.push_back(cl->getSocket());
	std::cout << YELLOW << "New connection accepted from fd " << cl->getSocket() << " to " << inet_ntoa(_address.sin_addr) << ":" << ntohs(_address.sin_port) << " - " << cl->getSocket() << " added to _sockets_used vector" << C_RES << std::endl;
	// adds socket to active fd set
	FD_SET (cl->getSocket(), &_active_fds);
	cl->client_receive_request();
}

void Server::treat_incoming_existing_connection_for_reading(int socket)
{
	if (read_from_client(socket) < 0)
	{
		std::cerr << GREEN << "treat_incoming_" << C_G_GREEN << "existing_connection" << C_RES << GREEN << "_for_reading on already-connected socket " << C_G_GREEN << socket << C_RES << GREEN << " ...closing socket" << C_RES << std::endl;
		close(socket);
		FD_CLR(socket, &_active_fds);
	}
}

void Server::treat_incoming_connection_for_writing(int socket)
{
	Client * cl = NULL;
	std::vector<int>::iterator it = _sockets_used.begin();
	std::vector<int>::iterator itend = _sockets_used.end();
	for (; it != itend; it++)
	{
		if (*it == socket)
		{
			std::cerr << GREEN << "treat_incoming_connection_for_" << C_G_GREEN << "writing" << C_RES << GREEN << " on socket " << C_G_GREEN << socket << C_RES << std::endl;
			std::vector<Client *>::iterator it_cl = _clients.begin();
			std::vector<Client *>::iterator itend_cl = _clients.end();
			for (; it_cl != itend_cl; it_cl++)
			{
				if ((*it_cl)->getSocket() == socket)
					cl = *it_cl;
			}
			cl->client_send_response();
			_sockets_used.erase(it);
			close(socket);
			break;
		}
	}
}

void Server::select_and_treat_connections(void)
{
	int			nb_fd_ready = 0;
	//
	// while (0)
	// {
	// 	FD_ZERO(&_active_fds);
	// 	FD_SET(_master_socket, &_active_fds);
	// 	// accept() ne renvoie pas d'exception car renvoie -1 en continu
	// 	_client->setSocket(::accept(_master_socket, reinterpret_cast<struct sockaddr *>(&_address), reinterpret_cast<socklen_t *>(&addrlen)));
	// 	if (_client->getSocket() >= 0)
	// 	{
	// 		std::cout << GREEN_B << "Connexion received from " << _client->getSocket() << C_RES << std::endl;
	// 		_client->treat_client();
	// 		_client->close();
	// 	}
	// }
	while (1) // rework example GNU READ ONLY
	{
		FD_ZERO(&_active_fds);
		FD_SET(_master_socket, &_active_fds);
		// Block until input arrives on one or more active sockets
		_read_fds = _active_fds;
		nb_fd_ready = select(FD_SETSIZE, &_read_fds , NULL , NULL , NULL);
		if (nb_fd_ready < 0)
		{
			perror("___select___");
			exit (EXIT_FAILURE);
		}
		// Service all the sockets with input pending
		for (int i = 0; i < FD_SETSIZE; i++)
		{
			if (FD_ISSET(i, &_read_fds)) // incoming connection
			{
				if (i == _master_socket) // Connection request on original socket
					treat_incoming_new_connection_for_reading(i);
				else // Data arriving on an already-connected socket
					treat_incoming_existing_connection_for_reading(i);
			}
			else if (FD_ISSET(i, &_write_fds))
				treat_incoming_connection_for_writing(i);
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