# include "Response.hpp"

// ********************************************* set page content if error *********************************************

void	Response::generate_error_content(void)
{
	if (_status_code != 200)
		_page_content = _error_content[404]; // _status_code
}

// ********************************************* create body *********************************************

void	Response::GET_create_body(void)
{
	_response_body = _page_content;
	_response_body_bin = string_to_binary(_response_body);
	// std::cout << "_response_body_bin : " << _response_body_bin << std::endl;
	// std::cout << RED_B << " binary_to_string(_response_body_bin) : " << binary_to_string(_response_body_bin) << std::endl << C_RES;
}

// ********************************************* concatenate response *********************************************

void	Response::concatenate_response()
{
	_response = _response_header + PAT_CRLF + _response_body;
	_response_bin = string_to_binary(_response);

}

// ********************************************* main - generate *********************************************

void	Response::generate(void)
{
	generate_error_content();
	GET_create_body();
	generate_response_header();
	concatenate_response();
}

