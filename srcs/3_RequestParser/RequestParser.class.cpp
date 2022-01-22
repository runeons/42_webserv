
#include <webserv.hpp>

void	RequestParser::print_center_line(int fn, int msg)
{
	ssize_t i = MAX((int)((int)this->_head - (int)30), 0);
	dprintf(1, " %-.*s %3lu {", 80 - (deep * 4) - fn - msg, PATTERNLINE, i);
	for (; this->_request_raw[i] && i < this->_head + 30; i++)
	{
		if (i >= this->_head_last_digest && i <= this->_head)
			dprintf(1, C_B_BLUE);
		if (i == this->_head)
			dprintf(1, C_B_RED);
		else
			dprintf(1, C_G_GRAY);
		print_char_printf(this->_request_raw[i]);
		dprintf(1, C_RES);
	}
	dprintf(1, "} %2lu\n", i);
}

void	RequestParser::debug_print_line(void)
{
	std::cout << "head: " << this->_head << " \'";
	print_char(this->_request_raw[this->_head]);
	std::cout << "\'" << std::endl;
	for (ssize_t i = 0; this->_request_raw[i]; i++)
	{
		if (i >= this->_head_last_digest && i <= this->_head)
			std::cout << C_B_BLUE;
		if (i == this->_head)
			std::cout << C_B_RED;
		else
			std::cout << C_G_GRAY;
		print_char(this->_request_raw[i]);
		std::cout << C_RES;
	}
	std::cout << std::endl;
}

int				RequestParser::eat(int to_eat)
{
	if (this->_head >= static_cast<ssize_t>(this->_bytes_read))
		throw (Exceptions::LexerException("eat ending"));
	else if (this->_request_raw[this->_head] == to_eat)
	{
		this->_head++;
		return (SUCCESS);
	}
	return (FAILURE);
}

void			RequestParser::init_digest(void)
{
	this->_head_last_digest = this->_head;
}

void			RequestParser::digest(std::string & target)
{
	try
	{
		target = this->_request_raw.substr(
			this->_head_last_digest,				// pos
			this->_head - this->_head_last_digest	// length
		);
		DIGEST_DEBUG(target.c_str());
	}
	catch (std::exception & e) {
		std::cout << "error: substr: " << e.what() << std::endl;
	}
}

void			RequestParser::start_parsing(void)
{
	// parser entry point
	try { HTTP_message(); }
	catch (std::exception & e)
	{
		this->_status_code = 400;
		std::cout << C_G_RED << "error: " << C_G_WHITE << _error.msg << C_RES << std::endl;
		this->_head = _error.head;
		this->print_center_line((int)strlen((char *)__FUNCTION__), (int)strlen(""));
	}
}

void			RequestParser::print_request_info(void)
{
	std::cerr	<< C_REQUEST << "[REQUEST] : "
				<< "["
				<< this->get__method()
				<< " "
				<< this->get__resource()
				<< " HTTP/"
				<< this->get__http_version()
				<< "]"
				<< C_RES;
	if (this->_body_size > 0)
		std::cerr << C_REQUEST << " - body size : " << this->_body_size << C_RES << std::endl;
	else
		std::cerr << C_REQUEST << " - no body" << C_RES << std::endl;
}

void			RequestParser::check_request_attributs(void)
{
	// check method
	if (_method != "GET" && _method != "POST" && _method != "DELETE")
		_status_code = 501; // Not implemented

	// check http version
	else if (_http_version != "1.1")
		_status_code = 505; // HTTP version not supported

	// check uri length
	else if (_resource.length() == 0)
		_status_code = 411; // length required

	else if (_resource.length() > MAX_URI_LENGTH)
		_status_code = 414; // URI Too Long
}
