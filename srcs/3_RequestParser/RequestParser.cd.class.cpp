
#include <webserv.hpp>

RequestParser::RequestParser(void) {} // constructor
RequestParser::RequestParser(std::string request_raw, ssize_t bytes_read) // param constructor
{
	std::cout << C_HIDDEN << "...RequestParser creation..." << C_RES << std::endl;

	_request_raw = request_raw;
	_bytes_read = bytes_read;
	_body_size = 0;
	_head = 0;
	_head_last_digest = 0;
	_methods_implemented = this->init_methods_implemented();
	_methods_unimplemented = this->init_methods_unimplemented();
	_status_code = 200;

	_error.msg = "";
	_error.head = -1;

	this->start_parsing();
	this->check_request_attributs();
	// std::cout << "_request_raw: " << std::endl;
	// std::cout << this->_request_raw << std::endl;
}

RequestParser::RequestParser(RequestParser const &src)  // constructor by copy
{
	*this = src;
}

RequestParser::~RequestParser(void) // destructor
{
	std::cout << C_HIDDEN << "...RequestParser destruction..." << C_RES << std::endl;

}
