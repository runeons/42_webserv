
# include <webserv.hpp>

// ********************************************* ::recv => request en std::string *********************************************

void Client::receive_first(void)
{
	_bytes_read = ::recv(_socket, _chunk, MAX_RCV - 1, 0);
	// std::cerr << C_G_YELLOW << "[ DEBUG br ] " << C_RES << " [" << _bytes_read << "]" << std::endl;
	if (_bytes_read == -1)
		throw Exceptions::RecvFailure();
	_chunk[_bytes_read] = '\0';

}

void Client::receive_with_content_length(void)
{
	_bytes_read = ::recv(_socket, _chunk, MAX_RCV - 1, 0);
	if (_bytes_read == -1)
		throw Exceptions::RecvFailure();
	_chunk[_bytes_read] = '\0';

	std::string buf_str(_chunk);
	// std::cerr << C_G_RED << "[ DEBUG buf ] " << C_RES << " [" << buf_str << "]" << std::endl;
	// si Content-Length can be found in request
	if (buf_str.find("Content-Length", 0) != std::string::npos)
	{
		// convert content-length to int
		std::string cl = buf_str.substr(buf_str.find("Content-Length", 0), buf_str.find(PAT_CRLF, buf_str.find("Content-Length", 0)) - buf_str.find("Content-Length", 0));
		std::cerr << C_G_RED << "[ DEBUG content-length  ] " << C_RES << " [" << cl << "]" << std::endl;
		std::string cl_val = cl.substr(strlen("Content-Length: "));
		// std::cerr << C_G_RED << "[ DEBUG clv ] " << C_RES << " [" << cl_val << "]" << std::endl;
		size_t cl_int = atol(cl_val.c_str());
		std::cerr << C_G_RED << "[ DEBUG content-length int ] " << C_RES << " [" << cl_int << "]" << std::endl;
		// find end of headers position
		std::string delim = PAT_CRLF""PAT_CRLF;
		int end_headers = buf_str.find(delim);
		std::cerr << C_G_RED << "[ DEBUG PAT_CRLF ] " << C_RES << end_headers << std::endl;
		// si (end of headers position + delim length + content-length) == size recv, alors tout recu
		int total_bytes_expected = end_headers + delim.length() + cl_int;
		std::cerr << C_G_RED << "[ DEBUG total_bytes_expected ] " << C_RES << total_bytes_expected << std::endl;
		int	remaining_bytes_to_recv = total_bytes_expected - _bytes_read;
		if (total_bytes_expected == _bytes_read)
			std::cout << C_G_BLUE << "Request fully received !" << std::endl;
		else
		{
			std::cout << C_G_BLUE << remaining_bytes_to_recv << " remaining to read w/ recv" << std::endl;
			// char tmp[remaining_bytes_to_recv];
			// int	bytes_read2 = ::recv(_socket, tmp, remaining_bytes_to_recv - 1, 0);
			// std::cout << "tmp : " << tmp << std::endl;
			// std::cout << "bytes_read2 : " << bytes_read2 << std::endl;
			// for (int i = _bytes_read; i < (_bytes_read + bytes_read2 - 1); i++)
			// {
			// 	_chunk[i] = tmp[i - _bytes_read];
			// 	/* code */
			// }
			// _bytes_read += bytes_read2;
			// _chunk[_bytes_read] = '\0';

		}
	}
	// std::cerr << C_G_YELLOW << "[ DEBUG br ] " << C_RES << " [" << _bytes_read << "]" << std::endl;

}

void Client::receive_request(void)
{
	// fcntl(_socket, F_SETFL, O_NONBLOCK);
	try
	{
		// receive_first();
		receive_with_content_length();
		// std::cerr << C_G_YELLOW << "[ DEBUG br ] " << C_RES << " [" << _bytes_read << "]" << std::endl;
		std::cout << GREEN << "Request of size " << C_G_GREEN << _bytes_read << C_RES << GREEN << " received :" <<  C_RES << std::endl;
		// print request
		// std::cout << "[";
		// for (ssize_t i = 0; i < _bytes_read; i++)
		// 	std::cout << _chunk[i] ;
		// std::cout << "]" << std::endl;
		_request.assign(_chunk, _bytes_read);
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
	throw (Exceptions::HTTP_ErrorStatusException(501)); // Not Implemented
}
void	Client::check_http_version(void)
{
	if (this->_request_parser->get__http_version() != "1.1")
		throw (Exceptions::HTTP_ErrorStatusException(505)); // HTTP Version Not Supported
}

void	Client::check_request(void)
{
	_request_parser = new RequestParser(_request, _bytes_read); // delete in generate_response :)
	_request_parser->print_request_info();
	_status_code = _request_parser->get__status();
	if (_status_code == 200)
	{
		try { check_method(); }
		catch (Exceptions::HTTP_ErrorStatusException & e) {
			_status_code = e.get__status();
		}
		try { check_http_version(); }
		catch (Exceptions::HTTP_ErrorStatusException & e) {
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

std::string	Client::generate_autoindex(std::string rsc)
{
	std::string cmd = "scripts/bin/tree \"" + rsc.substr(0, rsc.size() - 1) + "\" -H '.' -L 1 --noreport --charset utf-8";
	std::string res = exec_cmd(cmd.c_str(), PATH_AUTOINDEX);
	return res;
}

std::string		Client::decode_url(std::string & s)
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

// void		Client::apply_location(void)
// {
// 	// si path contient location, lier _applied location à la location
// 	std::string							rsc = _request_parser->get__resource();
// 	std::map<std::string, Location>		m = _config.get__locations();
// 	Location 							*l = NULL;;
//
// 	// TO PRECISE iterate through maps && search from end to beginning
// 	std::size_t found = rsc.find("/documents");
// 	if (found == 0)
// 		l = &m["/documents"];
// 	else if (rsc.front() == '/')
// 		l = &m["/"];
// 	_applied_location = l;
// 	if (_applied_location && 0)
// 		_applied_location->print_info();
// }

// target: /documents/photos/435/lolo.jpeg
//
// location:
// 	uri  : /
// 	root : X
// 	alias: X
// location:
// 	uri  : /photos
// 	root : X
// 	alias: X
// location:
// 	uri  : /document/photos/
// 	root : /tmp
// 	alias: X
// location:
// 	uri  : /document/photos/
// 	root : X
// 	alias: /photos/
// location:
// 	uri  : /images
// 	root : X
// 	alias: X

void		Client::apply_location(void)
{
	std::string	rsc = _request_parser->get__resource();

	std::map<std::string, Location>::const_iterator it;
	std::map<std::string, Location> m = _config.get__locations();


	while (rsc.size() >= 1)
	{
		it = _config.get__locations().begin();

		while (it != _config.get__locations().end())
		{
			// std::cout << "compare: \"" << it->first << "\" with \"" << rsc << "\"" << std::endl;
			if (it->first == rsc)
			{
				_applied_location = const_cast<Location *>(&it->second);
				return ;
			}
			it++;
		}
		std::string sub = rsc.substr(0, rsc.size() - 1);
		size_t	pos_last_slash = sub.rfind('/');
		if (pos_last_slash == std::string::npos)
			break ; // TODO exception
		// std::cout << C_G_RED << "pos_last_slash : " << pos_last_slash << C_RES << std::endl;
		if (rsc == "/")
			_applied_location = &m["/"];
		rsc.erase(pos_last_slash + 1);
		// std::cout << "rsc after erase: \"" << rsc << "\"" << std::endl;
	}
	std::cerr << C_G_RED << "apply_location: " << C_G_WHITE << " location not found" << C_RES << std::endl;
	exit(FAILURE);
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
		std::string index_path = rsc + _applied_location->get__index();
		if (stat(rsc.c_str(), &buffer) == -1) // si dir n'existe pas
		 ; // ne change rien au translated_path
		else if (stat(index_path.c_str(), &buffer) == -1 && _applied_location->get__autoindex() == 1) // if index.html not found + auto
			_page_content = generate_autoindex(rsc);// rsc += _applied_location->get__index();
		else // if (ret == 0) ou -1 et autoindex off
			rsc += _applied_location->get__index();
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
		std::cout << GREEN << "Response of size " << C_G_GREEN << bytes_sent << C_RES << GREEN << " sent :" <<  C_RES << std::endl;
	}
	catch (Exceptions::SendFailure & e)
	{
		std::cerr << RED << e.what() <<  C_RES << std::endl;
	}
}

// ********************************************* main - treat client *********************************************

void Client::client_receive_request(void)
{
	receive_request();
	check_request();
}

void Client::client_send_response(void)
{
	apply_location();
	_applied_location->print_info();
	translate_path();
	read_resource();
	generate_response();
	send_response();

	// std::cout <<  _response->get__responseHeader() << std::endl;
	// std::cout <<  _response->get__responseBody() << std::endl;
}

void Client::treat_client(void)
{
	client_receive_request();
	client_send_response();

}
