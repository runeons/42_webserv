/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestParser.class.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 16:35:48 by tharchen          #+#    #+#             */
/*   Updated: 2021/07/24 18:02:00 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>

char	**g_trace = NULL;
int		g_btsize = 0;

void	RequestParser::bc_s(void)
{
	void	*array[1024];

	g_btsize = backtrace(array, 1024);
	if (g_trace)
		delete (g_trace);
	g_trace = backtrace_symbols(array, g_btsize);
}

void	RequestParser::bc_p(void)
{
	std::cout << "backtrace: " << std::endl;
	if (g_trace != NULL)
	{
		for (int i = 1; i < g_btsize - 4; i++)
		{
			// std::cout << g_trace[i] << std::endl;
			int j = 64 + 13;
			for (;isdigit(g_trace[i][j]); j++) { }
			int k = j;
			for (;g_trace[i][j] && g_trace[i][j - 1] != 'E' && g_trace[i][j] != 'v'; j++) { }
			g_trace[i][j - 1] = '\0';
			std::cout << "    " << g_btsize - i - 4 << ": " << &g_trace[i][k] << std::endl;
		}
	}
}

int				RequestParser::eat(int to_eat)
{
	if (this->_request_raw[this->_head] == to_eat)
	{
		this->_head++;
		return (SUCCESS);
	}
	return (FAILURE);
}

void			RequestParser::init_digest(void)
{
	this->_head_last_digest = this->_head;
}

void			RequestParser::digest(std::string & target)
{
	try
	{
		target = this->_request_raw.substr(
			this->_head_last_digest,				// pos
			this->_head - this->_head_last_digest	// length
		);
	}
	catch (std::exception & e) {
		std::cout << "error: substr: " << e.what() << std::endl;
	}
}

void			RequestParser::start_parsing(void)
{
	// parser entry point
	try { HTTP_message(); }
	catch (std::exception & e)
	{
		std::cout << "error: " << e.what() << std::endl;
		bc_p();
	}
}

void			RequestParser::print_request_info(void)
{
	std::cout << "request info:" << std::endl;
	std::cout << "    method          : " << this->get__method() << std::endl;
	std::cout << "    path            : " << "[" << this->get__resource() << "]" << std::endl;
	std::cout << "    http_version    : " << this->get__http_version() << std::endl;
	std::cout << "    body            : " << "NOT IMPLEMENTED YET (sorry bb)" << std::endl;
	std::cout << "    headers         : " << std::endl;
	for (headers_iterator it = this->_header_fields.begin();
		it != this->_header_fields.end(); it++)
	{
		std::cout << "        [" << it->first << "] -> [" << it->second << "]" << std::endl;
	}

}
