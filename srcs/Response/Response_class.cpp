# include "Response.hpp"

// ********************************************* set page content if error *********************************************

void	Response::generate_error_content(void)
{
	if (_status_code != 200)
		_page_content = _error_content[_status_code];
}

// ********************************************* create body *********************************************

void	Response::GET_create_body(void)
{
	_response_body = _page_content;
	// _response_body_bin = string_to_binary(_response_body);
	// std::cout << "_response_body_bin : " << _response_body_bin << std::endl;
	// std::cout << RED_B << " binary_to_string(_response_body_bin) : " << binary_to_string(_response_body_bin) << std::endl << C_RES;
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
	// _response_bin = string_to_binary(_response);
}

// ********************************************* main - generate *********************************************

void	Response::generate(void)
{
	generate_error_content();
	GET_create_body(); // from page_content
	generate_response_header(); // from status_code, page_content and full_path
	concatenate_response();
}

