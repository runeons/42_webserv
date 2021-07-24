/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response_basics.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantoni <tsantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 18:41:43 by tsantoni          #+#    #+#             */
/*   Updated: 2021/07/24 18:41:44 by tsantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Response.hpp"

// Default constructor
Response::Response(int status_code, std::string page_content, std::string full_path) : _status_code(status_code), _page_content(page_content), _full_path(full_path)
{
	std::cout << GREY << "Response creation..." << C_RES << std::endl;
	// _full_path = "";
	_type_mime = "";
	_charset = "";

	_response = "";
	_response_header = "";
	_response_body = "";
	_headers_response = init_map_headers();
	_error_msg = init_map_msg();
	_error_content = init_map_body();
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
		this->_status_code = rhs.getStatusCode();
		this->_page_content = rhs.getPageContent();
		this->_full_path = rhs.getFullPath();
		this->_response = rhs.getResponse();
		this->_response_body = rhs.getResponseBody();
		this->_response_header = rhs.getResponseHeader();
		this->_headers_response = rhs.getHeadersResponse();
		this->_error_msg = rhs.getErrorMsg();
		this->_error_content = rhs.getErrorBody();
	}
	return (*this);
}

// getters and setters (non static attributes)
int Response::getStatusCode(void) const
{
	return (this->_status_code);
}

void Response::setStatusCode(const int status_code)
{
	this->_status_code = status_code;
	return ;
}

std::string Response::getFullPath(void) const
{
	return (this->_full_path);
}

void Response::setFullPath(const std::string full_path)
{
	this->_full_path = full_path;
	return ;
}

std::string Response::getResponse(void) const
{
	return (this->_response);
}

void Response::setResponse(const std::string response)
{
	this->_response = response;
	return ;
}

std::string Response::getResponseHeader(void) const
{
	return (this->_response_header);
}

void Response::setResponseHeader(const std::string response_header)
{
	this->_response_header = response_header;
	return ;
}

std::string Response::getResponseBody(void) const
{
	return (this->_response_body);
}

void Response::setResponseBody(const std::string response_body)
{
	this->_response_body = response_body;
	return ;
}

std::map<int, std::string> Response::getErrorMsg(void) const
{
	return (this->_error_msg);
}

void Response::setErrorMsg(const std::map<int, std::string> error_msg)
{
	this->_error_msg = error_msg;
	return ;
}

std::map<int, std::string> Response::getErrorBody(void) const
{
	return (this->_error_content);
}

void Response::setErrorBody(const std::map<int, std::string> error_body)
{
	this->_error_content = error_body;
	return ;
}

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
