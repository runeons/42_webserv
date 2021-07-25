/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_basics.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantoni <tsantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 18:41:53 by tsantoni          #+#    #+#             */
/*   Updated: 2021/07/25 15:32:09 by tsantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Server.hpp"


/*
struct sockaddr_in {
    sa_family_t    sin_family; // famille d'adresses : AF_INET
    uint16_t       sin_port;   // port dans l'ordre d'octets réseau
    struct in_addr sin_addr;   // adresse Internet, adresse IP de l'hôte
};

// Adresse Internet
struct in_addr {
    uint32_t       s_addr;     // Adresse dans l'ordre d'octets réseau
};
*/


// Default constructor
Server::Server(void)
{
	std::cout << GREY << "Server creation..." << C_RES << std::endl;
	_config = new Config;
	_client = new Client;
	_address.sin_family = AF_INET;
	_address.sin_addr.s_addr = INADDR_ANY;
	try
	{
		if (inet_aton("127.0.0.1", &_address.sin_addr) <= 0)
			throw Exceptions::InvalidAddress();
		std::cout << GREEN << "Address set !" <<  C_RES << std::endl;
	}
	catch (Exceptions::InvalidAddress & e)
	{
		std::cerr << RED << e.what() <<  C_RES << std::endl;
	}
	_address.sin_port = htons(_config->getPort());
	_socket = 0;
	return ;
}

// Copy constructor
Server::Server(const Server& src)
{
	std::cout << GREY << "Server creation..." << C_RES << std::endl;
	*this = src;
	return;
}

// Destructor
Server::~Server(void)
{
	delete _config;
	delete _client;
	std::cout << GREY << "Server destruction..." << C_RES << std::endl;
	return;
}

// Assignation operator
Server &	Server::operator=(const Server& rhs)
{
	std::cout << GREY << "Server Assignation operator called" << C_RES << std::endl;
	if (this != &rhs)
	{
		_config = rhs.getConfig();
		_socket = rhs.getSocket();
	}
	return (*this);
}

// getters and setters (non static attributes)
Config * Server::getConfig(void) const
{
	return (_config);
}

void Server::setConfig(Config * config)
{
	_config = config;
	return ;
}

Client * Server::getClient(void) const
{
	return (_client);
}

void Server::setClient(Client * client)
{
	_client = client;
	return ;
}

SOCKET Server::getSocket(void) const
{
	return (_socket);
}

void Server::setSocket(const SOCKET server_socket)
{
	_socket = server_socket;
	return ;
}
