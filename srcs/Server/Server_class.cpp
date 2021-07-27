/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantoni <tsantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 18:41:53 by tsantoni          #+#    #+#             */
/*   Updated: 2021/07/26 15:15:00 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Server.hpp"

// ********************************************* server utils *********************************************

void		Server::stop_server()
{
	std::cerr << GREY << "Server shut down" <<  C_RES << std::endl;
	close(_socket); // pas besoin de protéger le close parce qu'on va quitter le programme
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

	_socket = ::socket(AF_INET, SOCK_STREAM, 0);
	::setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
	// _socket = -1;
	if (_socket == -1)
		throw Exceptions::ServerSocket();
	std::cout << GREEN << "Server socket created !" <<  C_RES << std::endl;
}

// ********************************************* ::bind() *********************************************

void		Server::bind_address_and_port()
{
	if (::bind(_socket, reinterpret_cast<const struct sockaddr *>(&_address), sizeof(_address)) == -1)
	{
		perror("bind");
		throw Exceptions::BindServer();
	}
	std::cout << GREEN << "Address and port bound !" <<  C_RES << std::endl;
}

// ********************************************* ::accept() + Client.treat_client() *********************************************

void Server::listen_and_treat_connection(void)
{
	socklen_t addrlen = sizeof(_address);

	if (::listen(_socket, 50) == -1)
		throw Exceptions::ServerListen();
	std::cout << GREEN << "Server ready to listen !" <<  C_RES << std::endl;
	while (1)
	{
		// accept() ne renvoie pas d'exception car renvoie -1 en continu
		_client->setSocket(::accept(_socket, reinterpret_cast<struct sockaddr *>(&_address), reinterpret_cast<socklen_t *>(&addrlen)));
		if (_client->getSocket() >= 0)
		{
			std::cout << GREEN_B << "Connexion received from " << _client->getSocket() << C_RES << std::endl;
			_client->treat_client();
			_client->close();
		}
	}
	return ;
}

// ********************************************* main - launch() *********************************************

int		Server::launch(void)
{
	try
	{
		print_config();
		create_server_socket();
		bind_address_and_port();
		listen_and_treat_connection();
	}
	catch (std::exception & e)
	{
		std::cerr << RED << e.what() <<  C_RES << std::endl;
		this->stop_server();
		return (1);
	}
	return (0);
}