/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.cd.class.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 15:22:50 by tharchen          #+#    #+#             */
/*   Updated: 2021/08/03 14:12:35 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>

ConfigParser::ConfigParser(void) {} // constructor
ConfigParser::ConfigParser(std::string file)  // params constructor
{
	this->_config_raw = file;
	this->_head = 0;
	this->_head_last_digest = 0;
	this->start_parsing();
}

ConfigParser::~ConfigParser(void) // destructor
{

}
