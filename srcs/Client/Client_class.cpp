/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client_class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantoni <tsantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 18:41:33 by tsantoni          #+#    #+#             */
/*   Updated: 2021/07/26 09:29:05 by tsantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Client.hpp"

// ********************************************* ::recv => request en std::string *********************************************

void Client::receive_request(void)
{
	char	buffer[MAX_RCV];

	try
	{
		_bytes_read = ::recv(_socket, buffer, MAX_RCV - 1, 0);
		if (_bytes_read == -1)
			throw Exceptions::RecvFailure();
		std::cout << GREEN << "Request of size " << _bytes_read << " received :" <<  C_RES << std::endl;
		buffer[_bytes_read] = '\0';
		_request.assign(buffer, _bytes_read);
	}
	catch (Exceptions::RecvFailure & e)
	{
		std::cerr << RED << e.what() <<  C_RES << std::endl;
	}

	return ;
}

// ********************************************* parse + check request *********************************************

void Client::check_request(void)
{
	_request_parser = new RequestParser(_request); // create parser request
	_request_parser->print_request_info();
	return ;
}

// ********************************************* parse path *********************************************

void		Client::parse_parameters(void)
{
	std::string p = _query_string;
	int sep = 0;
	int eq = 0;

	while (sep > -1)
	{
		sep = p.find("&");
		eq = p.find("=");
		_parameters[p.substr(0, eq)] = p.substr(eq + 1, sep - (eq + 1));
		p.erase(0, sep + 1);
	}
}

void		Client::construct_full_path(void)
{
	std::string rsc = _request_parser->get__resource();

	/*
		TO DO : remplacer les caractères spéciaux
			- ex : %20 " "
			- ex : %C3%A7 "ç"
	*/
	if (rsc.find("?") < rsc.length())
	{
		_query_string = rsc.substr(rsc.find("?") + 1);
		rsc.erase(rsc.find("?"));
	}
	rsc = "./html" + rsc;
	if (rsc.back() == '/')
		rsc += "index.html";
	_full_path = rsc;
	if (!_query_string.empty())
		parse_parameters();
	return;
}

// ********************************************* read resource *********************************************

void Client::read_resource(void)
{
	std::ifstream ifs(_full_path);
	char c;

	_page_content = "";
	if (!ifs)
	{
		std::cerr << BROWN << "Error (404) : file doesn't exist" <<  C_RES << std::endl;
		_status_code = 404;
	}
	else
	{
		while (ifs >> std::noskipws >> c)
			_page_content += c;
		_status_code = 200;
		std::cerr << BROWN << "200: OK" <<  C_RES << std::endl;
	}
	if (ifs)
		ifs.close();
	return ;
}

// ********************************************* generate response *********************************************

void Client::generate_response(void)
{
	_response = new Response(_status_code, _page_content, _full_path);
	_response->generate();
	if (_request_parser != NULL)
		delete _request_parser;
}

// ********************************************* ::send response *********************************************

void Client::send_response(void)
{
	int	bytes_sent = 0;
	int len = (_response->getResponse().length() + 1);

	char buffer[len];
	memcpy(buffer, _response->getResponse().c_str(), len);
	try
	{
		bytes_sent = ::send(_socket, buffer, len, 0);
		if (bytes_sent == -1)
			throw Exceptions::SendFailure();
		std::cout << GREEN << "Response of size " << bytes_sent << " sent :" <<  C_RES << std::endl;
	}
	catch (Exceptions::SendFailure & e)
	{
		std::cerr << RED << e.what() <<  C_RES << std::endl;
	}
}

// ********************************************* main - treat client *********************************************

void Client::treat_client(void)
{
	receive_request();
	check_request();
	construct_full_path();
	read_resource();
	generate_response();
	send_response();

	std::cout <<  _response->getResponseHeader() << std::endl;
	// std::cout <<  _response->getResponseBody() << std::endl;

	return ;
}
