/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location_basics.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantoni <tsantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 11:12:24 by tsantoni          #+#    #+#             */
/*   Updated: 2021/07/31 11:56:30 by tsantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <webserv.hpp>

// Parametric constructor
Location::Location(std::string uri, std::string root_loc, std::string index, bool autoindex, std::vector<std::string> methods, std::string upload, std::vector<std::string> alias)
{
	std::cout << GREY << "Location creation..." << C_RES << std::endl;
	_uri = uri;
	_root_loc = root_loc;
	_index = index;
	_autoindex = autoindex;
	_methods = methods;
	_upload = upload;
	_alias = alias;
	return ;
}

// Destructor
Location::~Location(void)
{
	std::cout << GREY << "Location destruction..." << C_RES << std::endl;
	return;
}

// Assignation operator
Location &	Location::operator=(const Location& rhs)
{
	std::cout << GREY << "Location Assignation operator called" << C_RES << std::endl;
	if (this != &rhs)
	{
		_uri = rhs.getUri();
		_root_loc = rhs.getRootLoc();
		_index = rhs.getIndex();
		_autoindex = rhs.getAutoindex();
		_methods = rhs.getMethods();
		_upload = rhs.getUpload();
		_alias = rhs.getAlias();
		// _cgi = rhs.getCgi();
	}
	return (*this);
}

// getters and setters (non static attributes)
std::string Location::getUri(void) const
{
	return (_uri);
}

void Location::setUri(const std::string uri)
{
	_uri = uri;
	return ;
}

std::string Location::getRootLoc(void) const
{
	return (_root_loc);
}

void Location::setRootLoc(const std::string root_loc)
{
	_root_loc = root_loc;
	return ;
}

std::string Location::getIndex(void) const
{
	return (_index);
}

void Location::setIndex(const std::string index)
{
	_index = index;
	return ;
}

bool Location::getAutoindex(void) const
{
	return (_autoindex);
}

void Location::setAutoindex(const bool autoindex)
{
	_autoindex = autoindex;
	return ;
}

std::vector<std::string> Location::getMethods(void) const
{
	return (_methods);
}

void Location::setMethods(const std::vector<std::string> methods)
{
	_methods = methods;
	return ;
}

std::string Location::getUpload(void) const
{
	return (_upload);
}

void Location::setUpload(const std::string upload)
{
	_upload = upload;
	return ;
}

std::vector<std::string> Location::getAlias(void) const
{
	return (_alias);
}

void Location::setAlias(const std::vector<std::string> alias)
{
	_alias = alias;
	return ;
}
//
// std::map<std::string, std::map<std::string, std::string> > Location::getCgi(void) const
// {
// 	return (_cgi);
// }
//
// void Location::setCgi(const std::map<std::string, std::map<std::string, std::string> > cgi)
// {
// 	_cgi = cgi;
// 	return ;
// }

