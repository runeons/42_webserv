/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestParser.gs.class.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 19:36:15 by tharchen          #+#    #+#             */
/*   Updated: 2021/07/22 14:29:03 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>

// GETTER _method
enum e_methods	RequestParser::get__method(void) const
{
	return (this->_method);
}

// GETTER _resource
std::string		RequestParser::get__resource(void) const
{
	return (this->_resource);
}

// GETTER _http_version
std::string		RequestParser::get__http_version(void) const
{
	return (this->_http_version);
}

// GETTER _body
std::string		RequestParser::get__body(void) const
{
	return (this->_body);
}
