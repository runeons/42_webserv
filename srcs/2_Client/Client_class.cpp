
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
//
//  content_length | \r\n\r\n |
//  ---------------------------
// |             O |        O | continue to recv (until _remaining_bytes_to_recv == 0)
// |             O |        X |
// |             X |        O |
// |             X |        X |
// |               |          |

void Client::receive_with_content_length(void)
{
	_bytes_read = ::recv(_socket, _chunk, MAX_RCV - 1, 0);
	// _bytes_read = -1;
	if (_bytes_read == -1)
	{
		_status_code = 500;
		// throw (Exceptions::ClientException("Client failed to receive request"));
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
		// std::cout << C_CLIENT << "[CLIENT] <" << _socket << "> [REQUEST]    : " << "without Content-Length" << C_RES << std::endl;
		if (_total_bytes_expected == 0) // s'il n'y a pas eu de Content-Length du tout, set _total_bytes_expected puisque envoyé à RequestParser
			_total_bytes_expected = _bytes_read;
		if (_remaining_bytes_to_recv > 0)
			_remaining_bytes_to_recv -= _bytes_read;
	}
	std::cout << C_CLIENT << "[CLIENT] <" << _socket << "> [REQUEST]    : " << _bytes_read << " bytes received - " << _remaining_bytes_to_recv << " remaining" << C_RES << std::endl;
	_request.append(_chunk, _bytes_read);
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
	receive_with_content_length();
	// print_request_chunk(_bytes_read, _chunk);
	// _request.append(_chunk, _bytes_read);
	// std::cerr << C_G_YELLOW << "[ DEBUG print request ] " << C_RES << "[" << _request << "]" << std::endl;
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
	_applied_location->print_info();
}

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
			if (it->first == rsc)
			{
				_applied_location = const_cast<Location *>(&it->second);
				return ;
			}
			it++;
		}
		std::string sub = rsc.substr(0, rsc.size() - 1);
		size_t	pos_last_slash = sub.rfind('/');
		if (pos_last_slash == std::string::npos) // TODO exception - should be handled in RequestParser anyway ??
		{
			std::cerr << C_G_RED << "apply_location: " << C_G_WHITE << " location not found" << C_RES << std::endl;
			_status_code = 404;
		}
		rsc.erase(pos_last_slash + 1);
	}
}

// ********************************************* translate path *********************************************

std::string		Client::apply_alias(std::string s)
{
	// Si cette location a un alias, je vais remplacer le debut de l'URL "/URI/" par "/alias/", tout simplement
	// TO CHECK : alias OU root ? Un seul des deux possibles dans la config ?
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
			// std::cerr << C_DEBUG << "[ DEBUG ii ] " << C_RES << ii << std::endl;
			ch = static_cast<char>(ii);
			// std::cerr << C_DEBUG << "[ DEBUG ch ] " << C_RES << ch << std::endl;
			ret += ch;
			// std::cerr << C_DEBUG << "[ DEBUG ret ] " << C_RES << ret << std::endl;
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
	std::string res = exec_cmd(cmd.c_str(), PATH_AUTOINDEX);
	if (res == "")
		_status_code = 500;
	return res;
}

// if directory : set up translated_path as index, unless doesn't exist and autoindex is on : generate_autoindex
std::string		Client::apply_index_or_autoindex(std::string rsc)
{
	struct stat buffer;
	std::string index_path = rsc + _applied_location->get__index();
	if (stat(rsc.c_str(), &buffer) == -1) // si dir n'existe pas
	 ; // ne change rien au translated_path
	else if (stat(index_path.c_str(), &buffer) == -1 && _applied_location->get__autoindex() == 1) // if index.html not found + auto
		_page_content = generate_autoindex(rsc);
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
	rsc = decode_url(rsc); // TO CHECK avant ? gérer les accents dans les alias et fichiers de conf ? Too much I think
	rsc = remove_and_store_query(rsc);
	rsc = _applied_location->get__root_loc() + rsc;
	if (rsc.back() == '/')
		rsc = apply_index_or_autoindex(rsc);
	_translated_path = rsc;
	if (!_query_string.empty())
		parse_parameters();
	// _request.set__resource(rsc);
	return;
}

// ********************************************* read resource *********************************************

void Client::read_resource(void)
{
	std::ifstream ifs(_translated_path);
	char c;

	if (_page_content.length() > 0) // s'il a deja ete genere par l'autoindex
		;
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
	// Attention : si Location nulle ? Impossible car au moins "/", c'est ça ? TOCHECK
	_response = new Response(_config, *_applied_location, _status_code, _page_content, _translated_path, *_request_parser);
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
	// bytes_sent = -1;
	if (bytes_sent == -1)
		throw (Exceptions::ClientException("Client failed to send response"));
	_response_vector.erase(_response_vector.begin(), _response_vector.begin() + bytes_sent);
	_remaining_bytes_to_send -= bytes_sent;
	std::cout << C_CLIENT << "[CLIENT] <" << _socket << "> [RESPONSE]   : " << bytes_sent << " / " << _total_bytes_to_send << " bytes sent - " << _remaining_bytes_to_send << " remaining" << C_RES << std::endl;
	// std::cerr << C_G_YELLOW << "[ DEBUG RESPONSE SENT ] " << C_RES << "" << std::endl;
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

