/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi_basics.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantoni <tsantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 11:12:04 by tsantoni          #+#    #+#             */
/*   Updated: 2021/08/10 10:55:10 by tsantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <webserv.hpp>

// Parameter constructor
Cgi::Cgi(RequestParser & request, std::string script_name) : _request(request), _script_name(script_name)
{
	std::cout << GREY << "Cgi creation..." << C_RES << std::endl;
	_env_map = init_map_env();
	_env_arr = NULL;
	return ;
}

// Destructor
Cgi::~Cgi(void)
{
	std::cout << GREY << "Cgi destruction..." << C_RES << std::endl;
	return;
}

// Assignation operator
Cgi &	Cgi::operator=(const Cgi& rhs)
{
	std::cout << GREY << "Cgi Assignation operator called" << C_RES << std::endl;
	if (this != &rhs)
	{
		_env_map = rhs.getEnvMap();
		_env_arr = rhs.getEnvArr();
		_request = rhs.getRequest();
		// _config = rhs.getConfig();
	}
	return (*this);
}

// getters and setters (non static attributes)
std::map<std::string, std::string> Cgi::getEnvMap(void) const
{
	return (_env_map);
}

void Cgi::setEnvMap(const std::map<std::string, std::string> env_map)
{
	_env_map = env_map;
	return ;
}

std::string Cgi::getFullBuf(void) const
{
	return (_full_buf);
}

void Cgi::setFullBuf(const std::string full_buf)
{
	_full_buf = full_buf;
	return ;
}

char ** Cgi::getEnvArr(void) const
{
	return (_env_arr);
}

RequestParser & Cgi::getRequest(void) const
{
	return (_request);
}

void Cgi::setRequest(const RequestParser & request)
{
	_request = request;
	return ;
}

// Config & Cgi::getConfig(void) const
// {
// 	return (_config);
// }
//
// void Cgi::setConfig(const Config & config)
// {
// 	_config = config;
// 	return ;
// }
