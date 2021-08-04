/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestParser.gs.class.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 19:36:15 by tharchen          #+#    #+#             */
/*   Updated: 2021/08/01 14:35:18 by tsantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>

// GETTER _method
std::string		RequestParser::get__method(void) const
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

// GETTER _status_code
int		RequestParser::get__status(void) const
{
	return (this->_status_code);
}

// GETTER _header_fields
std::map<std::string, std::string>		RequestParser::get__header_fields(void) const
{
	return (this->_header_fields);
}

// PUBLIC GETTER header_value
std::string		RequestParser::get__header_value(std::string header_name)
{
	for (headers_iterator it = this->_header_fields.begin();
		it != this->_header_fields.end(); it++)
	{
		if (it->first == header_name)
			return (it->second);
	}
	return ("");
}