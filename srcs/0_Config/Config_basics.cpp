/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config_basics.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantoni <tsantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 11:12:18 by tsantoni          #+#    #+#             */
/*   Updated: 2021/08/09 12:06:29 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <webserv.hpp>

// Default constructor
Config::Config(void)
{
	// std::cout << GREY << "Config creation..." << C_RES << std::endl;

	this->clear();
	// char hostname[1024];
	//
	// gethostname(hostname, 1023);
	// _host = "127.0.0.1";
	// _port = 8000;
	// _server_name = "webby";
	// _host_name = hostname;
	// _root_dir = "./html";
	// _max_body_size = 1000000;
	// _error_pages = init_map_error_pages();
	// _locations = init_map_locations();

	return ;
}

// Copy constructor
Config::Config(const Config & src)
{
	// std::cout << GREY << "Config creation..." << C_RES << std::endl;
	*this = src;
	return;
}

// Destructor
Config::~Config(void)
{
	// std::cout << GREY << "Config destruction..." << C_RES << std::endl;
	return;
}

void	Config::clear(void)
{
	this->_host = "";
	this->_port = 0;
	this->_server_name = "";
	this->_host_name = "";
	this->_root_dir = "";
	this->_max_body_size = 0;
	this->_error_pages.clear();
	this->_locations.clear();
}

// Assignation operator
Config &	Config::operator=(const Config & rhs)
{
	// std::cout << GREY << "Config Assignation operator called" << C_RES << std::endl;
	if (this != &rhs)
	{
		_host = rhs.get__host();
		_port = rhs.get__port();
		_server_name = rhs.get__server_name();
		_host_name = rhs.get__host_name();
		_root_dir = rhs.get__root_dir();
		_max_body_size = rhs.get__max_body_size();
		_error_pages = rhs.get__error_pages();
		_locations = rhs.get__locations();
	}
	return (*this);
}

// getters and setters (non static attributes)
const std::string &							Config::get__host(void) const
{
	return (_host);
}

void 										Config::set__host(const std::string host)
{
	_host = host;
}


const int &									Config::get__port(void) const
{
	return (_port);
}

void 										Config::set__port(const int port)
{
	_port = port;
}


const std::string &							Config::get__server_name(void) const
{
	return (_server_name);
}

void 										Config::set__server_name(const std::string server_name)
{
	_server_name = server_name;
}


const std::string &							Config::get__host_name(void) const
{
	return (_host_name);
}

void 										Config::set__host_name(const std::string host_name)
{
	_host_name = host_name;
}


const std::string &							Config::get__root_dir(void) const
{
	return (_root_dir);
}

void 										Config::set__root_dir(const std::string root_dir)
{
	_root_dir = root_dir;
}


const int &									Config::get__max_body_size(void) const
{
	return (_max_body_size);
}

void 										Config::set__max_body_size(const int max_body_size)
{
	_max_body_size = max_body_size;
}


const std::map<int, std::string> &			Config::get__error_pages(void) const
{
	return (_error_pages);
}

void 										Config::set__error_pages(const std::map<int, std::string> error_pages)
{
	_error_pages = error_pages;
}


const std::map<std::string, Location> &		Config::get__locations(void) const
{
	return (_locations);
}

void 										Config::set__locations(const std::map<std::string, Location> locations)
{
	_locations = locations;
}


