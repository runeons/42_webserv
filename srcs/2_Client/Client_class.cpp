/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client_class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantoni <tsantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 18:41:33 by tsantoni          #+#    #+#             */
/*   Updated: 2021/08/01 12:41:09 by tsantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <webserv.hpp>

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

void	Client::check_method(void)
{
	for (v_string_iterator it = this->_request_parser->_methods_implemented.begin();
		it != this->_request_parser->_methods_implemented.end(); it++)
	{
		if (this->_request_parser->get__method() == *it)
			return ;
	}
	throw (HTTP_ErrorStatusException(501)); // Not Implemented
}
void	Client::check_http_version(void)
{
	if (this->_request_parser->get__http_version() != "1.1")
		throw (HTTP_ErrorStatusException(505)); // HTTP Version Not Supported
}

void	Client::check_request(void)
{
	_request_parser = new RequestParser(_request, _bytes_read); // delete in generate_response :)
	_request_parser->print_request_info();
	_status_code = _request_parser->get__status();
	if (_status_code == 200)
	{
		try { check_method(); }
		catch (HTTP_ErrorStatusException & e) {
			_status_code = e.get__status();
		}
		try { check_http_version(); }
		catch (HTTP_ErrorStatusException & e) {
			_status_code = e.get__status();
		}
	}
	return ;
}

// ********************************************* parse path *********************************************

void	Client::parse_parameters(void)
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

void		Client::apply_location(void)
{
	// si path contient location, lier _applied location à la location
	std::string							rsc = _request_parser->get__resource();
	std::map<std::string, Location *>	m = _config.getLocations();
	Location 							*l = NULL;;

	// TO PRECISE iterate through maps && search from end to beginning
	std::size_t found = rsc.find("/documents");
	if (found == 0)
		l = m["/documents"];
	else if (rsc.front() == '/')
		l = m["/"];
	_applied_location = l;
	if (_applied_location && 0)
	{
		std::cerr << C_G_RED << "[ DEBUG Uri       ] " << C_RES << _applied_location->getUri() << std::endl;
		std::cerr << C_G_RED << "[ DEBUG RootLoc   ] " << C_RES << _applied_location->getRootLoc() << std::endl;
		std::cerr << C_G_RED << "[ DEBUG Index     ] " << C_RES << _applied_location->getIndex() << std::endl;
		std::cerr << C_G_RED << "[ DEBUG Autoindex ] " << C_RES << _applied_location->getAutoindex() << std::endl;
		std::cerr << C_G_RED << "[ DEBUG Upload    ] " << C_RES << _applied_location->getUpload() << std::endl;
	}
}

std::string	Client::generate_autoindex(std::string rsc)
{
	std::string cmd = "scripts/bin/tree \"" + rsc.substr(0, rsc.size() - 1) + "\" -H '.' -L 1 --noreport --charset utf-8";
	std::string res = exec_cmd(cmd.c_str(), PATH_AUTOINDEX);
	return res;
}

std::string		Client::decode_url(std::string s)
{
	std::string	ret;
	char		ch;
	int			ii;
	int			len = s.length();

	for (int i = 0; i < len; i++)
	{
		if (s[i] != '%')
		{
			if (s[i] == '+')
				ret += ' ';
			else
				ret += s[i];
		}
		else
		{
			sscanf(s.substr(i + 1, 2).c_str(), "%x", &ii);
			// std::cerr << C_G_RED << "[ DEBUG ii ] " << C_RES << ii << std::endl;
			ch = static_cast<char>(ii);
			// std::cerr << C_G_RED << "[ DEBUG ch ] " << C_RES << ch << std::endl;
			ret += ch;
			// std::cerr << C_G_RED << "[ DEBUG ret ] " << C_RES << ret << std::endl;
			i = i + 2;
		}
	}
	return ret;
}

std::string		Client::apply_alias(std::string s)
{
	// it through all locations in _config
	// it through all alias vector in _config
	// if found : apply
	return s;
}

void		Client::translate_path(void)
{
	std::string rsc = _request_parser->get__resource();


	// std::cerr << C_G_RED << "[ DEBUG RSC  ] " << C_RES << rsc << std::endl;
	_page_content = ""; // vraiment utile ??
	rsc = apply_alias(rsc);
	/*
		si path contient alias, remplacer par location uri - grace a map d'alias-uri_location
	*/
	apply_location();
	rsc = decode_url(rsc);
	// Theo remaster - // remplir query_string
	if (rsc.find("?") < rsc.length())
	{
		_query_string = rsc.substr(rsc.find("?") + 1);
		rsc.erase(rsc.find("?"));
	}
	rsc = "html" + rsc;
	// if directory : set up translated_path as index, unless don't exists and autoindex is on : generate_autoindex
	if (rsc.back() == '/')
	{
		struct stat buffer;
		std::string index_path = rsc + _applied_location->getIndex();
		if (stat(rsc.c_str(), &buffer) == -1) // si dir n'existe pas
		 ; // ne change rien au translated_path
		else if (stat(index_path.c_str(), &buffer) == -1 && _applied_location->getAutoindex() == 1) // if index.html not found + auto
			_page_content = generate_autoindex(rsc);// rsc += _applied_location->getIndex();
		else // if (ret == 0) ou -1 et autoindex off
			rsc += _applied_location->getIndex();
	}
	_translated_path = rsc;
	// std::cerr << C_G_RED << "[ DEBUG PATH ] " << C_RES << _translated_path << std::endl;
	if (!_query_string.empty())
		parse_parameters();
	return;
}

// ********************************************* read resource *********************************************

void Client::read_resource(void)
{
	std::ifstream ifs(_translated_path);
	char c;

	// std::cerr << C_G_RED << "[ DEBUG PAGECONTENT ] " << C_RES << _page_content << std::endl;
	if (_page_content.length() > 0) // s'il a deja ete genere par l'autoindex
		;
	else if (!ifs)
		_status_code = 404;
	else
	{
		while (ifs >> std::noskipws >> c)
			_page_content += c;
	}
	std::cerr << BROWN << "status code: " << _status_code << C_RES << std::endl;
	if (ifs)
		ifs.close();
	return ;
}

// ********************************************* generate response *********************************************

void Client::generate_response(void)
{
		// attention : si Location nulle ? Impossible car au moins "/", c'est ça ?
	_response = new Response(_config, *_applied_location, _status_code, _page_content, _translated_path, *_request_parser);
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
	translate_path();
	read_resource();
	generate_response();
	send_response();

	std::cout <<  _response->getResponseHeader() << std::endl;
	// std::cout <<  _response->getResponseBody() << std::endl;

	return ;
}
