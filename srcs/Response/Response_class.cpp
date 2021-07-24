# include "Response.hpp"

// ********************************************* set page content if error *********************************************

void	Response::generate_error_content(void)
{
	if (_status_code != 200)
		_page_content = _error_content[_status_code];
	// std::cout << _page_content << std::endl;
}

// ********************************************* create body *********************************************

void	Response::GET_create_body(void)
{
	_response_body = _page_content;
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
	generate_error_content();
	GET_create_body(); // from page_content
	generate_response_header(); // from status_code, page_content and full_path
	concatenate_response();
}

