/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client_basics.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantoni <tsantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 18:41:33 by tsantoni          #+#    #+#             */
/*   Updated: 2021/07/28 11:21:35 by tsantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Client.hpp"

// Parametric constructor
Client::Client(Config & config) : _config(config)
{
	std::cout << GREY << "Client creation..." << C_RES << std::endl;

	_socket = 0;
	_status_code = 0;
	_bytes_read = 0;
	_request = "";
	_full_path = "";
	_response = NULL;
	_request_parser = NULL;
	_page_content = "";
	_query_string = "";
	// _parameters_map = ();
	return ;
}

// Destructor
Client::~Client(void)
{
	std::cout << GREY << "Client destruction..." << C_RES << std::endl;
	if (_response != NULL)
		delete _response;
	return;
}

// Assignation operator
Client &	Client::operator=(const Client& rhs)
{
	std::cout << GREY << "Client Assignation operator called" << C_RES << std::endl;
	if (this != &rhs)
	{
		_socket = rhs.getSocket();
	}
	return (*this);
}

// getters and setters (non static attributes)
SOCKET Client::getSocket(void) const
{
	return (_socket);
}

void Client::setSocket(const SOCKET client_socket)
{
	_socket = client_socket;
	return ;
}

std::string Client::getRequest(void) const
{
	return (_request);
}

void Client::setRequest(const std::string request)
{
	_request = request;
	return ;
}
