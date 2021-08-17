
# include <webserv.hpp>

// ********************************************* retrieve type_mime and charset *********************************************

void		Response::parse_type_mime_charset_cmd_result(std::string str)
{
	unsigned first = str.find(":") + 2;
	unsigned last = str.find(";");

	if (last > str.length() || _translated_path.back() == '/') // si "cannot open file" || directory
	{
		_type_mime = "text/html";
		_charset = "utf-8";
		return ;
	}
	_type_mime = str.substr(first, last - first);
	first = str.find("=") + 1;
	last = str.find("\n");
	_charset = str.substr(first, last - first);
	if (_charset == "binary" && _type_mime == "inode/x-empty") // si empty file
	{
		_type_mime = "text/html";
		_charset = "utf-8";
		return ;
	}
}

void		Response::retrieve_type_mime_charset(void)
{
	std::string cmd;
	std::string res;

	cmd = "file --mime " + _translated_path;
	res = exec_cmd(cmd.c_str(), PATH_CMD_RES);
	parse_type_mime_charset_cmd_result(res);
}

// ********************************************* check if method allowed *********************************************

void	Response::check_if_method_allowed(void)
{
	std::vector<std::string> v_methods = _applied_location.get__methods();
	std::vector<std::string>::iterator it;

	for (it = v_methods.begin(); it != v_methods.end(); it++)
	{
		if (*it == _request.get__method())
			return ;
	}
	_status_code = 405;
}

// ********************************************* check if return 301 *********************************************

int	Response::is_actually_directory(std::string path)
{
	if (path.back() != '/' && _type_mime == "inode/directory") // si c'est un dir sans slash final
		return (1);
	return (0);
}

void	Response::check_if_redir_301(void)
{
	if (_applied_location.get__redir301().size())
		_status_code = 301;
}

// ********************************************* GET create body *********************************************

void	Response::GET_create_body(void)
{
	_response_body = _page_content;
}

void	Response::GET_handle(void)
{
	if (is_actually_directory(_translated_path))
	{
		_applied_location.set__redir301(_request.get__resource() + "/");
		_status_code = 301;
	}
	// std::cerr << C_DEBUG << "[ DEBUG error code ] " << _status_code << C_RES << std::endl;
	GET_create_body();
}

// ********************************************* DELETE create body *********************************************

void	Response::DELETE_create_body(void)
{
	_response_body = "<html>\
	<body>\
	<h1>File deleted.</h1>\
	</body>\
	</html>";
}

void	Response::DELETE_handle(void)
{
	if (is_actually_directory(_translated_path))
		_status_code = 409;
	if (is_response_successful())
	{
		if (user_perm_to_write(_translated_path))
		{
			// std::cerr << C_DEBUG << "[ DEBUG ] " << C_RES << "Permitted to delete (S_IWUSR)" << std::endl;
			if (::remove(_translated_path.c_str()) == -1)
				_status_code = 403;
		}
		else
			_status_code = 403;
	}
	DELETE_create_body();
}

// ********************************************* POST create body *********************************************

void	Response::POST_create_body(void)
{
	_response_body = _page_content;
}

void	Response::POST_create_body_cgi(void)
{
	std::cout << C_OTHER << "Let's start with upload cgi !" << C_RES << std::endl;
	Cgi *cgi = new Cgi(_request, _config, "." + _request.get__resource());
	cgi->launch();
	_response_body = cgi->get__full_buf();
	delete cgi;
	std::cout << C_OTHER << "We are finished with upload cgi !" << C_RES << std::endl;
}

void	Response::POST_handle(void)
{
	POST_create_body();
	std::string request_content_type = _request.get__header_value("Content-Type");
	if (request_content_type.find("multipart/form-data;", 0) == 0)
	{
		if (_applied_location.get__upload() == "")
			_status_code = 403; // TOCHECK ou 405
		else
			POST_create_body_cgi();
	}
}

// ********************************************* fill response body if error *********************************************

void	Response::fill_body_if_error(void)
{
	if (!is_response_successful())
		_response_body = _error_content[_status_code];
}

// ********************************************* generate response headers *********************************************

void		Response::generate_response_header(void)
{
	_response_header = generate_status_line();
	_response_header += r_header_server();
	_response_header += r_header_date();
	_response_header += r_header_connection();
	_response_header += r_header_content_length();
	_response_header += r_header_content_type();
	_response_header += r_header_location();
	return ;
}

// ********************************************* concatenate response *********************************************

void	Response::concatenate_response()
{
	_response = _response_header + PAT_CRLF + _response_body;
}

// ********************************************* main - generate *********************************************

void	Response::generate(void)
{
	// if (_applied_location) // should always be the case with previous checks
		check_if_method_allowed();
	retrieve_type_mime_charset();
	check_if_redir_301();
	// if (is_response_successful())
	// {
		if (_request.get__method() == "GET")
			GET_handle(); // from page_content
		else if (_request.get__method() == "POST")
			POST_handle(); // from page_content
		else if (_request.get__method() == "DELETE")
			DELETE_handle();
	// }
	fill_body_if_error();
	generate_response_header(); // from status_code, page_content and translated_path
	print_status_line();
	concatenate_response();
	// std::cerr << C_DEBUG << "[ DEBUG RESPONSE GENERATED ] " << C_RES << "" << std::endl;
}
