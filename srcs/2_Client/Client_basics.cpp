/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client_basics.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantoni <tsantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 18:41:33 by tsantoni          #+#    #+#             */
/*   Updated: 2021/08/09 19:48:46 by tsantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <webserv.hpp>

// Parametric constructor
Client::Client(Config & config) : _config(config)
{
	std::cout << GREY << "Client creation..." << C_RES << std::endl;

	_socket = 0;
	_status_code = 0;
	_bytes_read = 0;
	_request = "";
	_translated_path = "";
	_response = NULL;
	_request_parser = NULL;
	_page_content = "";
	_query_string = "";
	_applied_location = NULL;
	_remaining_bytes_to_recv = 0;
	_total_bytes_expected = 0;
	_remaining_bytes_to_send = 0;
	_total_bytes_to_send = 0;
	memset(_chunk, 0, MAX_RCV);	//clear the variable

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

int Client::get_remaining_bytes_to_recv(void) const
{
	return (_remaining_bytes_to_recv);
}

void Client::set_remaining_bytes_to_recv(const int bytes)
{
	_remaining_bytes_to_recv = bytes;
	return ;
}

int Client::get_total_bytes_expected(void) const
{
	return (_total_bytes_expected);
}

void Client::set_total_bytes_expected(const int bytes)
{
	_total_bytes_expected = bytes;
	return ;
}

int Client::get_remaining_bytes_to_send(void) const
{
	return (_remaining_bytes_to_send);
}

void Client::set_remaining_bytes_to_send(const int bytes)
{
	_remaining_bytes_to_send = bytes;
	return ;
}

int Client::get_total_bytes_to_send(void) const
{
	return (_total_bytes_to_send);
}

void Client::set_total_bytes_to_send(const int bytes)
{
	_total_bytes_to_send = bytes;
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

Location * Client::getAppliedLocation(void) const
{
	return (_applied_location);
}

void Client::setAppliedLocation(Location * applied_location)
{
	_applied_location = applied_location;
	return ;
}
