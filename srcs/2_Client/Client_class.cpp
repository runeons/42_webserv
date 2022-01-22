
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

void Client::receive_request(void)
{
	_bytes_read = ::recv(_socket, _chunk, MAX_RCV - 1, 0);
	if (_bytes_read <= 0) // 0 aussi car grace a select, si on rentre ici c'est qu'il y a qqch a envoyer
	{
		_status_code = 500;
		return ;
	}
	_chunk[_bytes_read] = '\0';

	std::string buf_str(_chunk);
	if (buf_str.find("Content-Length", 0) != std::string::npos) // si Content-Length can be found in request
	{ // I LOVE YOU
		_total_bytes_expected = calculate_total_bytes_expected(buf_str);
		_remaining_bytes_to_recv = _total_bytes_expected - _bytes_read;
		if (_remaining_bytes_to_recv == 0)
			std::cout << C_CLIENT << "[CLIENT] <" << _socket << "> [REQUEST]    : " << "chunked request fully received" << C_RES << std::endl;
		else
			std::cout << C_CLIENT << "[CLIENT] <" << _socket << "> [REQUEST]    : " << "chunked request received : " << _bytes_read << " bytes - remaining : " << _remaining_bytes_to_recv << " bytes" << C_RES << std::endl;
	}
	else
	{
		if (_total_bytes_expected == 0) // s'il n'y a pas eu de Content-Length du tout, set _total_bytes_expected puisque envoyé à RequestParser
			_total_bytes_expected = _bytes_read;
    else if (_total_bytes_expected > 0)
      _total_bytes_expected += _bytes_read;
		if (_remaining_bytes_to_recv > 0)
			_remaining_bytes_to_recv -= _bytes_read;
	}
	std::cout << C_CLIENT << "[CLIENT] <" << _socket << "> [REQUEST]    : " << _bytes_read << " bytes received - " << _remaining_bytes_to_recv << " remaining" << C_RES << std::endl;
	_request.append(_chunk, _bytes_read);
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

void	Client::check_body_size(void)
{
	if (this->_request_parser->get__body_size() > static_cast<size_t>(this->_config.get__max_body_size()))
		throw (Exceptions::HTTP_ErrorStatusException(413)); // HTTP Version Not Supported
}

void	Client::check_request(void)
{
  // std::cout << C_G_RED << _request.substr(0, _total_bytes_expected) << C_RES << std::endl;
  // std::cout << C_G_GREEN << _request << C_RES << std::endl;

	_request_parser = new RequestParser(_request, _total_bytes_expected + 1);
	_request_parser->print_request_info();
	_status_code = _request_parser->get__status();
	if (is_response_successful())
	{
		try { check_method(); }
		catch (Exceptions::HTTP_ErrorStatusException & e) {
			_status_code = e.get__status();
		}
		try { check_http_version(); }
		catch (Exceptions::HTTP_ErrorStatusException & e) {
			_status_code = e.get__status();
		}
		try { check_body_size(); }
		catch (Exceptions::HTTP_ErrorStatusException & e) {
			_status_code = e.get__status();
		}
	}
	return ;
}

// ********************************************* apply location *********************************************

void		Client::adjust_applied_location(void)
{
	if (_applied_location->get__root_loc() == "")
		_applied_location->set__root_loc(_config.get__root_dir());
	if (_applied_location->get__methods().empty())
	{
		std::vector<std::string> m;
		m.push_back("GET");
		m.push_back("POST");
		m.push_back("DELETE");
		_applied_location->set__methods(m);
	}
	if (_applied_location->get__upload() != "" && _applied_location->get__upload().at(_applied_location->get__upload().size() - 1) != '/')
		_applied_location->set__upload(_applied_location->get__upload() + "/");
	_applied_location->print_info();
}

void		Client::apply_location(void)
{
	std::string rsc;
	if (_request_parser == NULL)
	{
		rsc = "/"; // applique une loc par defaut si la requete n'a pas pu etre lue
	}
	else
		rsc = _request_parser->get__resource();

	std::map<std::string, Location>::const_iterator it;
	std::map<std::string, Location> m = _config.get__locations();

	while (rsc.size() >= 1)
	{
		it = _config.get__locations().begin();
		while (it != _config.get__locations().end())
		{
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
		{
			std::cerr << C_G_RED << "Error: " << C_G_WHITE << " location not found" << C_RES << std::endl;
			if (is_response_successful()) // pour eviter de changer le status_code si bad request ou precedent
				_status_code = 404;
		}
		rsc.erase(pos_last_slash + 1);
	}
}

// ********************************************* translate path *********************************************

std::string		Client::apply_alias(std::string s)
{
	// Si cette location a un alias, je vais remplacer le debut de l'URL "/URI/" par "/alias/", tout simplement
	if (_applied_location->get__alias().size())
	{
		s.erase(0, _applied_location->get__uri().size());
		s = _applied_location->get__alias() + s;
	}
	return s;
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
			ch = static_cast<char>(ii);
			ret += ch;
			i = i + 2;
		}
	}
	return ret;
}

std::string		Client::remove_and_store_query(std::string s)
{
	if (s.find("?") < s.length())
	{
		_query_string = s.substr(s.find("?") + 1);
		s.erase(s.find("?"));
	}
	return s;
}

std::string	Client::generate_autoindex(std::string rsc)
{
	std::string cmd = "scripts/bin/tree \"" + rsc.substr(0, rsc.size() - 1) + "\" -H '.' -L 1 --noreport --charset utf-8";
	// std::string cmd = "scripts/bin/tree_linux \"" + rsc.substr(0, rsc.size() - 1) + "\" -H '.' -L 1 --noreport --charset utf-8";
	std::string res = exec_cmd(cmd.c_str(), PATH_AUTOINDEX);
	if (res == "")
		_status_code = 500;
	return res;
}

void			insert_html(std::string & s, std::string str_before, std::string to_insert)
{
	size_t pos = s.find(str_before);
	if (pos != std::string::npos)
		s.insert(pos + str_before.length(), to_insert);
}

void			erase_html(std::string & s, std::string to_erase)
{
	size_t pos = s.find(to_erase);
	if (pos != std::string::npos)
		s.erase(pos, to_erase.length());
}

// if directory : set up translated_path as index, unless doesn't exist and autoindex is on : generate_autoindex
std::string		Client::apply_index_or_autoindex(std::string rsc)
{
	struct stat buffer;
	std::string index_path = rsc + _applied_location->get__index();
	if (stat(rsc.c_str(), &buffer) == -1) // si dir n'existe pas
	 ; // ne change rien au translated_path
	else if (stat(index_path.c_str(), &buffer) == -1 && _applied_location->get__autoindex() == 1) // if index.html not found + auto
	{
		_page_content = generate_autoindex(rsc);

		insert_html(_page_content, std::string("<head>\n "), std::string("<link rel=\"icon\" href=\"/images/favicon.ico\" />\n <link rel<link href=\"https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css\" rel=\"stylesheet\" integrity=\"sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC\" crossorigin=\"anonymous\">\n"));
		insert_html(_page_content, std::string("<body>\n"), std::string("<nav class=\"navbar navbar-expand-lg navbar-dark bg-dark\"><div class=\"container-fluid\"><a class=\"navbar-brand\" href=\"/\">Home</a><button class=\"navbar-toggler\" type=\"button\" data-bs-toggle=\"collapse\" data-bs-target=\"#navbarNav\" aria-controls=\"navbarNav\" aria-expanded=\"false\" aria-label=\"Toggle navigation\"><span class=\"navbar-toggler-icon\"></span></button></div></nav>"));
		insert_html(_page_content, std::string("Tokoro\n\t</p>\n"), std::string("\t<script src=\"https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/js/bootstrap.bundle.min.js\" integrity=\"sha384-MrcW6ZMFYlzcLA8Nl+NtUVF0sA7MsXsP1UyJoMp4YLEuNSfAP+JcXn/tWtIaxVXM\" crossorigin=\"anonymous\"></script>"));
		erase_html(_page_content, std::string("\n  P { font-weight: normal; font-family : ariel, monospace, sans-serif; color: black; background-color: transparent;}\n  B { font-weight: normal; color: black; background-color: transparent;}\n  A:visited { font-weight : normal; text-decoration : none; background-color : transparent; margin : 0px 0px 0px 0px; padding : 0px 0px 0px 0px; display: inline; }\n  A:link    { font-weight : normal; text-decoration : none; margin : 0px 0px 0px 0px; padding : 0px 0px 0px 0px; display: inline; }\n  A:hover   { color : #000000; font-weight : normal; text-decoration : underline; background-color : yellow; margin : 0px 0px 0px 0px; padding : 0px 0px 0px 0px; display: inline; }\n  A:active  { color : #000000; font-weight: normal; background-color : transparent; margin : 0px 0px 0px 0px; padding : 0px 0px 0px 0px; display: inline; }\n  .VERSION { font-size: small; font-family : arial, sans-serif; }\n  .NORM  { color: black;  background-color: transparent;}\n  .FIFO  { color: purple; background-color: transparent;}\n  .CHAR  { color: yellow; background-color: transparent;}\n  .DIR   { color: blue;   background-color: transparent;}\n  .BLOCK { color: yellow; background-color: transparent;}\n  .LINK  { color: aqua;   background-color: transparent;}\n  .SOCK  { color: fuchsia;background-color: transparent;}\n  .EXEC  { color: green;  background-color: transparent;}"));
		erase_html(_page_content, "\n  <!-- ");
		erase_html(_page_content, "\n  -->");
	}
	else // if (ret == 0) ou -1 et autoindex off
		rsc += _applied_location->get__index();
	return rsc;
}

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

void		Client::translate_path(void)
{
	std::string rsc = _request_parser->get__resource();

	rsc = apply_alias(rsc);
	rsc = decode_url(rsc);
	rsc = remove_and_store_query(rsc);
	rsc = _applied_location->get__root_loc() + rsc;
	if (rsc[rsc.size() - 1] == '/')
		rsc = apply_index_or_autoindex(rsc);
	_translated_path = rsc;
	if (!_query_string.empty())
		parse_parameters();
	return;
}

// ********************************************* read resource *********************************************

void Client::read_resource(void)
{
	std::ifstream ifs(_translated_path.c_str());
	char c;

	if (_page_content.length() > 0) // s'il a deja ete genere par l'autoindex
		;
	else if (!isfile_exist(_translated_path))
		_status_code = 404; // si can't find resource
	else if (!user_perm_to_read(_translated_path))
		_status_code = 403;
	else if (!ifs)
		_status_code = 404; // si can't find resource
	else
	{
		while (ifs >> std::noskipws >> c)
			_page_content += c;
	}
	if (ifs)
		ifs.close();
	return ;
}

// ********************************************* generate response *********************************************

void Client::generate_response(void)
{
	_response = new Response(_config, *_applied_location, _status_code, _page_content, _translated_path, *_request_parser, _query_string);
	_response->generate();
	_total_bytes_to_send = _response->getResponse().length() + 1;
	// copy response in _response_vector vector
	_response_vector.resize(_total_bytes_to_send);
	memcpy(&_response_vector[0], _response->getResponse().c_str(), _total_bytes_to_send);

	// print_response_header();
	// print_response_body();
}

// ********************************************* ::send response *********************************************

void Client::send_response(void)
{
	int	bytes_sent = 0;
	if (_remaining_bytes_to_send == 0)
		_remaining_bytes_to_send = _total_bytes_to_send;
	bytes_sent = ::send(_socket, &_response_vector[0], _response_vector.size(), 0);
	if (bytes_sent <= 0) // 0 aussi car grace a select, si on rentre ici c'est qu'il y a qqch a envoyer
		throw (Exceptions::ClientException("Client failed to send response"));
	_response_vector.erase(_response_vector.begin(), _response_vector.begin() + bytes_sent);
	_remaining_bytes_to_send -= bytes_sent;
	std::cout << C_CLIENT << "[CLIENT] <" << _socket << "> [RESPONSE] \033[01m" << std::setw(3) << ((_total_bytes_to_send - _remaining_bytes_to_send) * 100) / _total_bytes_to_send << "%" << C_RES << C_CLIENT << " : " << bytes_sent << " / " << _total_bytes_to_send << " bytes sent - " << _remaining_bytes_to_send << " remaining" << C_RES << std::endl;
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
