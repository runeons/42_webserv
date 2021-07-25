/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestParser.cd.class.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 19:36:15 by tharchen          #+#    #+#             */
/*   Updated: 2021/07/24 23:38:04 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>

RequestParser::RequestParser(void) {} // constructor
RequestParser::RequestParser(std::string request_raw) // param constructor
{
	this->_request_raw = request_raw;
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
