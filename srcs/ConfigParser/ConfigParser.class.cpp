/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.class.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 15:25:36 by tharchen          #+#    #+#             */
/*   Updated: 2021/08/10 12:17:08 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>

/*
** char	**g_trace = NULL;
** int		g_btsize = 0;
**
** void	ConfigParser::bc_s(void)
** {
** 	void	*array[1024];
**
** 	g_btsize = backtrace(array, 1024);
** 	if (g_trace)
** 		delete (g_trace);
** 	g_trace = backtrace_symbols(array, g_btsize);
** }
**
** void	ConfigParser::debug_print_line(void)
** {
** 	std::cout << "head: " << this->_head << " \'" << this->_config_raw[this->_head] << "\'" << std::endl;
** 	for (size_t i = 0; this->_config_raw[i]; i++)
** 	{
** 		if (i >= this->_head_last_digest && i <= this->_head)
** 			std::cout << C_B_BLUE;
** 		if (i == this->_head)
** 			std::cout << C_B_RED;
** 		else
** 			std::cout << C_G_GRAY;
** 		if (this->_config_raw[i] == '\r')
** 			std::cout << "\\r";
** 		else if (this->_config_raw[i] == '\n')
** 			std::cout << "\\n";
** 		else if (this->_config_raw[i] == '\t')
** 			std::cout << "\\t";
** 		else
** 			std::cout << this->_config_raw[i];
** 		std::cout << C_RES;
** 	}
** 	std::cout << std::endl;
** }
**
** void	ConfigParser::bc_p(void)
** {
** 	std::cout << "backtrace: " << std::endl;
** 	if (g_trace != NULL)
** 	{
** 		for (int i = 1; i < g_btsize - 8; i++)
** 		{
** 			// std::cout << g_trace[i] << std::endl;
** 			int j = 64 + 13;
** 			for (;isdigit(g_trace[i][j]); j++) { }
** 			int k = j;
** 			for (;g_trace[i][j] && g_trace[i][j - 1] != 'E' && g_trace[i][j] != 'v'; j++) { }
** 			g_trace[i][j - 1] = '\0';
** 			std::cout << "    " << g_btsize - i - 8 << ": " << &g_trace[i][k] << std::endl;
** 		}
** 	}
** }
*/

void	ConfigParser::print_center_line(int fn, int msg)
{
	size_t i = MAX((int)((int)this->_head - (int)30), 0);
	size_t len = this->_head + 30;
	dprintf(1, " %-.*s %3lu {", 80 - (deep * 4) - fn - msg, PATTERNLINE, i);
	for (; this->_config_raw[i] && i < len; i++)
	{
		if (i >= this->_head_last_digest && i <= this->_head)
			dprintf(1, C_B_BLUE);
		if (i == this->_head)
			dprintf(1, C_B_RED);
		else
			dprintf(1, C_G_GRAY);
		print_char_printf(this->_config_raw[i]);
		dprintf(1, C_RES);
	}
	dprintf(1, "} %2lu\n", i);
}

void	ConfigParser::debug_print_line(void)
{
	std::cout << "head: " << this->_head << " \'";
	print_char(this->_config_raw[this->_head]);
	std::cout << "\'" << std::endl;
	for (size_t i = 0; this->_config_raw[i]; i++)
	{
		if (i >= this->_head_last_digest && i <= this->_head)
			std::cout << C_B_BLUE;
		if (i == this->_head)
			std::cout << C_B_RED;
		else
			std::cout << C_G_GRAY;
		print_char(this->_config_raw[i]);
		std::cout << C_RES;
	}
	std::cout << std::endl;
}

int				ConfigParser::eat_debug(int to_eat)
{
	std::cout << "to_eat: \'";
	print_char(to_eat);
	std::cout << "\'" << std::endl;
	if (this->_config_raw[this->_head] == '\0')
		throw (Exceptions::LexerException("eat ending"));
	if (this->_config_raw[this->_head] == to_eat)
	{
		this->_head++;
		std::cout << "new head pos: " << this->_head << std::endl;
		debug_print_line();
		return (SUCCESS);
	}
	std::cout << "eat fail" << std::endl;
	debug_print_line();
	return (FAILURE);
}

int				ConfigParser::eat_nodebug(int to_eat)
{
	if (this->_config_raw[this->_head] == '\0')
		throw (Exceptions::LexerException("eat ending"));
	if (this->_config_raw[this->_head] == to_eat)
	{
		this->_head++;
		return (SUCCESS);
	}
	return (FAILURE);
}

int				ConfigParser::eat(int to_eat)
{
	// return (eat_debug(to_eat));
	return (eat_nodebug(to_eat));
}


void			ConfigParser::init_digest(void)
{
	this->_head_last_digest = this->_head;
}

void			ConfigParser::digest(std::string & target)
{
	try
	{
		target = this->_config_raw.substr(
			this->_head_last_digest,				// pos
			this->_head - this->_head_last_digest	// length
		);
		DIGEST_DEBUG(target.c_str());
	}
	catch (std::exception & e) {
		std::cout << "error: substr: " << e.what() << std::endl;
	}
}

void			ConfigParser::start_parsing(void)
{
	// parser entry point
	try { config(); }
	catch (std::exception & e)
	{
		std::cout << C_G_RED << "parser collapse error: " << C_G_WHITE << e.what() << C_RES << std::endl;
		exit(-1);
		// bc_p();
	}
}

void			ConfigParser::print_info(void) const
{
	std::cout << "Printing Config file Info: " << std::endl << std::endl;

	std::vector<Config>::const_iterator it_c = this->_servers_config.begin();
	while (it_c != this->_servers_config.end())
	{
		it_c->print_info();
		it_c++;
		if (it_c != this->_servers_config.end())
			std::cout << std::endl;
	}

}
