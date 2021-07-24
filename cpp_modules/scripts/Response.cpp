# include "Response.hpp"

// Default constructor
Response::Response(void)
{
	std::cout << GREY << "Response creation..." << C_RES << std::endl;
	return ;
}

// Copy constructor
Response::Response(const Response& src)
{
	std::cout << GREY << "Response creation..." << C_RES << std::endl;
	*this = src;
	return;
}

// Destructor
Response::~Response(void)
{
	std::cout << GREY << "Response destruction..." << C_RES << std::endl;
	return;
}

// Assignation operator
Response &	Response::operator=(const Response& rhs)
{
	std::cout << GREY << "Response Assignation operator called" << C_RES << std::endl;
	if (this != &rhs)
	{
		this->_headers_response = rhs.getHeadersResponse();
		this->_page_content = rhs.getPageContent();
	}
	return (*this);
}

// getters and setters (non static attributes)
std::map<int, std::string> Response::getHeadersResponse(void) const
{
	return (this->_headers_response);
}

void Response::setHeadersResponse(const std::map<int, std::string> headers_response)
{
	this->_headers_response = headers_response;
	return ;
}

std::string Response::getPageContent(void) const
{
	return (this->_page_content);
}

void Response::setPageContent(const std::string page_content)
{
	this->_page_content = page_content;
	return ;
}

