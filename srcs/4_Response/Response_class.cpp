
# include <webserv.hpp>

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

void	Response::check_if_redir_301(void)
{
	if (_applied_location.get__redir301().size())
	{
		_status_code = 301;
	}
}

// ********************************************* create body *********************************************

void	Response::GET_create_body(void)
{
	_response_body = _page_content;
}

void	Response::GET_handle(void)
{
	GET_create_body();
}
// ********************************************* create body *********************************************

void	Response::POST_create_body(void)
{
	_response_body = _page_content;
}

void	Response::POST_create_body_cgi(void)
{
	std::cout << C_G_YELLOW << "Let's start with upload cgi !" << C_RES << std::endl;
	Cgi *cgi = new Cgi(_request, "." + _request.get__resource());
	cgi->launch();
	_response_body = cgi->getFullBuf();
	delete cgi;
	std::cout << C_G_YELLOW << "We are finished with upload cgi !" << C_RES << std::endl;
}

void	Response::POST_handle(void)
{
	POST_create_body();
	// check POST types
	std::string request_content_type = _request.get__header_value("Content-Type");
	if (request_content_type.find("multipart/form-data;", 0) == 0)
	{
		if (_applied_location.get__upload() == "")
			_status_code = 405;
		else
			POST_create_body_cgi();
	}
}

// ********************************************* fill response body if error *********************************************

void	Response::fill_body_if_error(void)
{
	if (_status_code != 200)
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
	// if (_status_code == 301)
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
	check_if_method_allowed();
	check_if_redir_301();
	if (_status_code == 200)
	{
		if (_request.get__method() == "GET")
			GET_handle(); // from page_content
		else if (_request.get__method() == "POST")
			POST_handle(); // from page_content
	}
	fill_body_if_error();
	generate_response_header(); // from status_code, page_content and translated_path
	concatenate_response();
	// std::cerr << C_G_RED << "[ DEBUG RESPONSE GENERATED ] " << C_RES << "" << std::endl;
}
