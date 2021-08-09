
# include <webserv.hpp>

// ********************************************* ::recv => request en std::string *********************************************

size_t		Client::retrieve_request_content_length(std::string buf_str)
{
	std::string	content_length_line;
	std::string	content_length_val;
	size_t		content_length_int;

	// retrieve and convert content-length to size_t
	content_length_line = buf_str.substr(buf_str.find("Content-Length", 0), buf_str.find(PAT_CRLF, buf_str.find("Content-Length", 0)) - buf_str.find("Content-Length", 0));
	content_length_val = content_length_line.substr(strlen("Content-Length: "));
	content_length_int = atol(content_length_val.c_str());
	return (content_length_int);
}

int		Client::calculate_total_bytes_expected(std::string buf_str)
{
	size_t		content_length;
	int			end_headers_pos;
	int			total_bytes_expected;
	std::string	delim = PAT_CRLF""PAT_CRLF;

	content_length = retrieve_request_content_length(buf_str);
	end_headers_pos = buf_str.find(delim);
	// si (end of headers position + delim length + content-length) == size recv, alors tout recu
	total_bytes_expected = end_headers_pos + delim.length() + content_length;
	return (total_bytes_expected);
}

void Client::receive_with_content_length(void)
{
	_bytes_read = ::recv(_socket, _chunk, MAX_RCV - 1, 0);
	if (_bytes_read == -1)
		throw Exceptions::RecvFailure();
	_chunk[_bytes_read] = '\0';

	std::string buf_str(_chunk);
	if (buf_str.find("Content-Length", 0) != std::string::npos) // si Content-Length can be found in request
	{ // I LOVE YOU
		_total_bytes_expected = calculate_total_bytes_expected(buf_str);
		_remaining_bytes_to_recv = _total_bytes_expected - _bytes_read;
		if (_total_bytes_expected == _bytes_read)
			std::cout << C_G_BLUE << "Request fully received !" << std::endl;
		else
			std::cout << C_G_BLUE << _remaining_bytes_to_recv << " remaining to read w/ recv" << std::endl;
	}
	else
	{
		std::cout << C_G_BLUE << "Content-Length not found in request" << C_RES << std::endl;
		if (_total_bytes_expected == 0) // s'il n'y a pas eu de Content-Length du tout, set _total_bytes_expected puisque envoyé à RequestParser
			_total_bytes_expected = _bytes_read;
		if (_remaining_bytes_to_recv > 0)
			_remaining_bytes_to_recv -= _bytes_read;
	}
	std::cout << GREEN << "Request of size " << C_G_GREEN << _bytes_read << C_RES << GREEN << " received :" <<  C_RES << std::endl;
}

void	print_request_chunk(int bytes_read, char chunk[MAX_RCV])
{
	// print current request chunk
	std::cout << "[";
	for (ssize_t i = 0; i < bytes_read; i++)
		std::cout << chunk[i] ;
	std::cout << "]" << std::endl;
}

void Client::receive_request(void)
{
	// fcntl(_socket, F_SETFL, O_NONBLOCK);
	try
	{
		receive_with_content_length();
		// print_request_chunk(_bytes_read, _chunk);
		_request.append(_chunk, _bytes_read);
		// std::cerr << C_G_YELLOW << "[ DEBUG print request ] " << C_RES << "[" << _request << "]" << std::endl;
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
	_request_parser = new RequestParser(_request, _total_bytes_expected + 1); // delete in generate_response :) // TOCHECK
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

void		Client::apply_location(void)
{
	// si path contient location, lier _applied location à la location
	std::string							rsc = _request_parser->get__resource();
	std::map<std::string, Location>		m = _config.getLocations();
	Location 							*l = NULL;;

	// TO PRECISE iterate through maps && search from end to beginning
	std::size_t found = rsc.find("/documents");
	if (found == 0)
		l = &m["/documents"];
	else if (rsc.front() == '/')
		l = &m["/"];
	_applied_location = l;
	if (_applied_location && 0)
	{
		std::cerr << C_G_BLUE << "[ DEBUG Uri       ] " << C_RES << _applied_location->getUri() << std::endl;
		std::cerr << C_G_BLUE << "[ DEBUG RootLoc   ] " << C_RES << _applied_location->getRootLoc() << std::endl;
		std::cerr << C_G_BLUE << "[ DEBUG Index     ] " << C_RES << _applied_location->getIndex() << std::endl;
		std::cerr << C_G_BLUE << "[ DEBUG Autoindex ] " << C_RES << _applied_location->getAutoindex() << std::endl;
		std::cerr << C_G_BLUE << "[ DEBUG Upload    ] " << C_RES << _applied_location->getUpload() << std::endl;
		std::cerr << C_G_BLUE << "[ DEBUG Redir301  ] " << C_RES << _applied_location->getRedir301() << std::endl;
		std::vector<std::string> v = _applied_location->getMethods();
		std::vector<std::string>::iterator it;
		for (it = v.begin(); it != v.end(); it++)
			std::cerr << C_G_BLUE << "[ DEBUG methods   ] " << C_RES << *it << std::endl;
		v = _applied_location->getAlias();
		for (it = v.begin(); it != v.end(); it++)
			std::cerr << C_G_BLUE << "[ DEBUG alias     ] " << C_RES << *it << std::endl;
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
		// Attention : si Location nulle ? Impossible car au moins "/", c'est ça ?
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

void Client::print_response_header(void)
{
	std::cout <<  _response->getResponseHeader() << std::endl;
}

void Client::print_response_body(void)
{
	std::cout <<  _response->getResponseHeader() << std::endl;
	std::cout <<  _response->getResponseBody() << std::endl;
}

void Client::print_response(void)
{
	print_response_header();
	print_response_body();
}

void Client::treat_client(void)
{
	receive_request();
	check_request();
	translate_path();
	read_resource();
	generate_response();
	send_response();
}
