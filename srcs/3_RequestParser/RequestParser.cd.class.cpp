
#include <webserv.hpp>

RequestParser::RequestParser(void) {} // constructor
RequestParser::RequestParser(std::string request_raw, ssize_t bytes_read) // param constructor
{
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
	// std::cout << "_request_raw: " << std::endl;
	// std::cout << this->_request_raw << std::endl;
}

RequestParser::RequestParser(RequestParser const &src)  // constructor by copy
{
	*this = src;
}

RequestParser::~RequestParser(void) // destructor
{

}
