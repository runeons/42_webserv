/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestParser.cd.class.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 19:36:15 by tharchen          #+#    #+#             */
/*   Updated: 2021/07/22 12:11:22 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../webserv.hpp"

RequestParser::RequestParser(void) {} // constructor
RequestParser::RequestParser(std::string request_raw) // param constructor
{
	this->_request_raw = request_raw;
	this->_head = 0;
	this->_head_last_digest = 0;

	this->_method = METHOD_NONE;
	this->request();
}

RequestParser::RequestParser(RequestParser const &src)  // constructor by copy
{
	*this = src;
}

RequestParser::~RequestParser(void) // destructor
{

}
