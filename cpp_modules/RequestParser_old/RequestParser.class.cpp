/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestParser.class.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 19:36:15 by tharchen          #+#    #+#             */
/*   Updated: 2021/07/22 23:36:38 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>

// PROTECTED MEMBERS FUNCTION : PROMF

/* ************************************************************************** */
/* ************************************************************************** */

// PRIVATE MEMBERS FUNCTION : PRIMF

static std::string		stolo(std::string s)
{
	for (int i = 0; s[i]; i++)
	{
		if (s[i] >= 'A' && s[i] <= 'Z')
			s[i] += 32;
	}
	return (s);
}

std::string		RequestParser::get_method_name(void)
{
	switch (this->_method) {
		case METHOD_NONE		: return (std::string("NONE"));
		case METHOD_GET			: return (std::string("GET"));
		case METHOD_POST		: return (std::string("POST"));
		case METHOD_DELETE		: return (std::string("DELETE"));
		case METHOD_COPY		: return (std::string("COPY"));
		case METHOD_OPTIONS		: return (std::string("OPTIONS"));
		case METHOD_HEAD		: return (std::string("HEAD"));
		case METHOD_LINK		: return (std::string("LINK"));
		case METHOD_MOVE		: return (std::string("MOVE"));
		case METHOD_PUT			: return (std::string("PUT"));
		case METHOD_PATCH		: return (std::string("PATCH"));
		case METHOD_TRACE		: return (std::string("TRACE"));
		case METHOD_UNLINK		: return (std::string("UNLINK"));
		case METHOD_WRAPPED		: return (std::string("WRAPPED"));
		default					: return (std::string("_NO_MATCH_"));
	}
}

void			RequestParser::print_request_info(void)
{
	std::cout << "request info:" << std::endl;
	std::cout << "    method          : " << this->get_method_name() << std::endl;
	std::cout << "    path            : " << "[" << this->_resource << "]" << std::endl;
	std::cout << "    http_version    : " << this->_http_version << std::endl;
	std::cout << "    body            : " << "NOT IMPLEMENTED YET (sorry bb)" << std::endl;
	std::cout << "    headers         : " << std::endl;
	for (headers_iterator it = this->_header_fields.begin();
		it != this->_header_fields.end(); it++)
	{
		std::cout << "        [" << it->first << "] -> [" << it->second << "]" << std::endl;
	}

}

int				RequestParser::eat(std::string to_eat)
{
	// std::cout << "[ " << __FUNCTION__ << " string ] ";
	if (this->_request_raw.compare(this->_head, to_eat.length(), to_eat) == 0)
	{
		// std::cout << "eatten: \'" << to_eat << "\'" << std::endl;
		this->_head += to_eat.length();
		return (SUCCESS);
	}
	else
	{
		// std::cout << "\'" << to_eat << "\' not found !" << std::endl;
		return (FAILURE);
	}
}

int				RequestParser::eat_no_casesensitive(std::string to_eat)
{
	// std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ] --- head on: [" << SSTRABS(this->_request_raw[this->_head]) << STRABS(this->_request_raw[this->_head]) << "] (" << this->_head << ") ";
	std::string tmp;
	try
	{
		// printf("[ "C_G_RED"DEBUG"C_RES" ] %lu - %lu < %lu\n", this->_request_raw.length(), this->_head, to_eat.length());
		if (this->_request_raw.length() - this->_head < to_eat.length())
		{
			// std::cout << "\'" << to_eat << "\' not found !" << std::endl;
			return (FAILURE);
		}
		tmp = stolo(this->_request_raw.substr(this->_head, to_eat.length()));
	}
	catch (std::exception & e)
	{
		// std::cout << "error: " << e.what() << std::endl;
	}
	if (this->_request_raw.compare(this->_head, tmp.length(), tmp) == 0)
	{
		// std::cout << "eatten: \'" << to_eat << "\'" << std::endl;
		this->_head += to_eat.length();
		return (SUCCESS);
	}
	else
	{
		// std::cout << "\'" << to_eat << "\' not found !" << std::endl;
		return (FAILURE);
	}
}

int				RequestParser::eat(int to_eat)
{
	// std::cout << "[ " << __FUNCTION__ << " char ] ";
	if (this->_request_raw[this->_head] == to_eat)
	{
		// std::cout << "eatten: \'" << static_cast<char>(to_eat) << "\'" << std::endl;
		this->_head++;
		return (SUCCESS);
	}
	else
	{
		// std::cout << "\'" << static_cast<char>(to_eat) << "\' not found !" << std::endl;
		return (FAILURE);
	}
}

int				RequestParser::eatall(void)
{
	// debug();
	// std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	this->_head = this->_request_raw.find(PAT_CRLF""PAT_CRLF, this->_head, 4);
	// this->_head = this->_request_raw.length() - 1;
	return (SUCCESS);
}

std::string		RequestParser::digest(void)
{
	// debug();
	// std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	std::string ret;
	try { ret = this->_request_raw.substr(this->_head_last_digest, this->_head - this->_head_last_digest); }
	catch (std::exception & e) { std::cout << "error: " << e.what() << std::endl; }
	this->_head_last_digest = this->_head;
	return (ret);
}

/* ************************************************************************** */
/* ************************************************************************** */

// PUBLIC MEMBERS FUNCTION : PUMF

/* ************************************************************************** */
/* ************************************************************************** */
