/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestParser.class.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 16:35:48 by tharchen          #+#    #+#             */
/*   Updated: 2021/07/25 16:04:10 by tharchen         ###   ########.fr       */
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

void	RequestParser::debug_print_line(void)
{
	std::cout << "head: " << this->_head << " \'" << this->_request_raw[this->_head] << "\'" << std::endl;
	for (size_t i = 0; this->_request_raw[i]; i++)
	{
		if (i >= this->_head_last_digest && i <= this->_head)
			std::cout << C_B_BLUE;
		if (i == this->_head)
			std::cout << C_B_RED;
		else
			std::cout << C_G_GRAY;
		if (this->_request_raw[i] == '\r')
			std::cout << "\\r";
		else if (this->_request_raw[i] == '\n')
			std::cout << "\\n";
		else if (this->_request_raw[i] == '\t')
			std::cout << "\\t";
		else
			std::cout << this->_request_raw[i];
		std::cout << C_RES;
	}
	std::cout << std::endl;
}

void	RequestParser::bc_p(void)
{
	std::cout << "backtrace: " << std::endl;
	if (g_trace != NULL)
	{
		for (int i = 1; i < g_btsize - 8; i++)
		{
			// std::cout << g_trace[i] << std::endl;
			int j = 64 + 13;
			for (;isdigit(g_trace[i][j]); j++) { }
			int k = j;
			for (;g_trace[i][j] && g_trace[i][j - 1] != 'E' && g_trace[i][j] != 'v'; j++) { }
			g_trace[i][j - 1] = '\0';
			std::cout << "    " << g_btsize - i - 8 << ": " << &g_trace[i][k] << std::endl;
		}
	}
}

int				RequestParser::eat(int to_eat)
{
	// static int stop = 0;

	if (this->_request_raw[this->_head] == '\0')
	{
		// stop = 1;
		// std::cerr << C_G_MAGENTA << "warning:" << C_G_WHITE << " end of _request_raw reached ! (head: " << this->_head << ")" << C_RES << std::endl;
		throw (LexerException("eat ending"));
	}
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
	// std::cout << "  -------------------------------------------------------------" << std::endl;
	// std::cout << "/                                                               \\" << std::endl;
	// std::cout << "   digest:" << std::endl;
	// debug_print_line();
	try
	{
		// std::cout << "substr from \'" << this->_request_raw[this->_head_last_digest] << "\' to \'" << this->_request_raw[this->_head] << "\'" << std::endl;
		target = this->_request_raw.substr(
			this->_head_last_digest,				// pos
			this->_head - this->_head_last_digest	// length
		);
	}
	catch (std::exception & e) {
		std::cout << "error: substr: " << e.what() << std::endl;
	}
	// std::cout << "\\                                                               /" << std::endl;
	// std::cout << "  -------------------------------------------------------------" << std::endl;
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
	std::cout << "    body            : " << "[" << this->get__body() << "]" << std::endl;
	// std::cout << "    body            : " << "too long" << std::endl;
	std::cout << "    headers         : " << std::endl;
	for (headers_iterator it = this->_header_fields.begin();
		it != this->_header_fields.end(); it++)
	{
		std::cout << "        [" << it->first << "] -> [" << it->second << "]" << std::endl;
	}

}
