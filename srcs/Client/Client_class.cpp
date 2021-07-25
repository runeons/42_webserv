/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client_class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantoni <tsantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 18:41:33 by tsantoni          #+#    #+#             */
/*   Updated: 2021/07/25 16:01:37 by tsantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Client.hpp"

// ********************************************* ::recv => request en std::string *********************************************

void Client::receive_request(void)
{
	char	buffer[MAX_RCV];
	int		bytes_read = 0;

	try
	{
		bytes_read = ::recv(_socket, buffer, MAX_RCV - 1, 0);
		if (bytes_read == -1)
			throw Exceptions::RecvFailure();
		std::cout << GREEN << "Request of size " << bytes_read << " received !" <<  C_RES << std::endl;
		buffer[bytes_read] = '\0';
		_request.assign(buffer, bytes_read);
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
	// _request_parser->print_request_info();

	return ;
}

// ********************************************* parse path *********************************************

void		Client::construct_full_path(void)
{

	// _full_path = "./html/six";

	// /*
	// taking into account RequestParser

	std::cout << C_B_RED << "full_path before changing it : " << _full_path << C_RES << std::endl;
	if (_request_parser->get__resource() == "/")
		_full_path = "./html/index.html";
	else
		_full_path =  "./html" + _request_parser->get__resource();
	std::cout << C_B_RED << "full_path after changing it : " << _full_path << C_RES << std::endl;
	// */

	/*
	// pseudo-code path parsing + concatenating
	- remplacer les caractères spéciaux
		- ex : %20 " "
		- ex : %C3%A7 "ç"
	- enlever tous les arguments de query (après le ?)
		- ex : ?ordre=1
		- les parser / mettre de côté => dans une map pour etre utilises en variables d'environnement plus tard
	- si finit par / => concat avec index.html
	- concatener ROOT_DIR et new_path
	*/
	return;
}

// ********************************************* read resource *********************************************

void Client::read_resource(void)
{
	std::ifstream ifs(_full_path);
	char c;

	if (!ifs)
	{
		std::cerr << BROWN << "Error (404) : file doesn't exist" <<  C_RES << std::endl;
		_status_code = 404;
	}
	else
	{
		std::cerr << GREEN_B << "OK : file found" <<  C_RES << std::endl;
		while (ifs >> std::noskipws >> c)
			_page_content += c;
		_status_code = 200;

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

	std::cout << "len: " << len << std::endl;
	char buffer[len];
	memcpy(buffer, _response->getResponse().c_str(), len);
	try
	{
		bytes_sent = ::send(_socket, buffer, len, 0);
		if (bytes_sent == -1)
			throw Exceptions::SendFailure();
		std::cout << GREEN << "Response of size " << bytes_sent << " sent !" <<  C_RES << std::endl;
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

	std::cout <<  _response->getResponse() << std::endl;

	return ;
}
