/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestParser.cd.class.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 19:36:15 by tharchen          #+#    #+#             */
/*   Updated: 2021/07/25 18:55:19 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>

RequestParser::RequestParser(void) {} // constructor
RequestParser::RequestParser(std::string request_raw, ssize_t bytes_read) // param constructor
{
	this->_request_raw = request_raw;
	this->_bytes_read = bytes_read;
	this->_body_size = 0;
	this->_head = 0;
	this->_head_last_digest = 0;

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
