/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.class.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 15:25:36 by tharchen          #+#    #+#             */
/*   Updated: 2021/08/04 19:31:06 by tharchen         ###   ########.fr       */
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

# define MIN(X, Y) X < Y ? X : Y
# define MAX(X, Y) X > Y ? X : Y
// # define DEBUG_MSG(X) dprintf(1, "%*s[ %s%s%s ] \'"C_G_WHITE"%s"C_RES"\'\n", (deep + 1) * 4, "", C_G_YELLOW, __FUNCTION__, C_RES, X)
# define DEBUG_MSG(X) // dprintf(1, "%*s[ %s%s%s ] \'"C_G_WHITE"%s"C_RES"\'\n", (deep + 1) * 4, "", C_G_YELLOW, __FUNCTION__, C_RES, X)

# define PATTERNLINE "---------------------------------------------------------------------------------------------"

void	print_char_printf(char c);

void	ConfigParser::print_center_line(int fn, int msg)
{
	size_t i = MAX((int)((int)this->_head - (int)30), 0);
	dprintf(1, " %-.*s %2lu {", 80 - (deep * 4) - fn - msg, PATTERNLINE, i);
	for (; this->_config_raw[i] && i < this->_head + 30; i++)
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

void	print_char_printf(char c)
{
	if (c == '\r')
		dprintf(1, "\\r");
	else if (c == '\n')
		dprintf(1, "\\n");
	else if (c == '\t')
		dprintf(1, "\\t");
	else if (c == '\0')
		dprintf(1, "\\0");
	else if (c == '\v')
		dprintf(1, "\\v");
	else if (c == '\f')
		dprintf(1, "\\f");
	else if (c == '\a')
		dprintf(1, "\\a");
	else if (c == '\b')
		dprintf(1, "\\b");
	else if (c == '\e')
		dprintf(1, "\\e");
	else
		dprintf(1, "%c", c);
}

void	print_char(char c)
{
	if (c == '\r')
		std::cout << "\\r";
	else if (c == '\n')
		std::cout << "\\n";
	else if (c == '\t')
		std::cout << "\\t";
	else if (c == '\0')
		std::cout << "\\0";
	else if (c == '\v')
		std::cout << "\\v";
	else if (c == '\f')
		std::cout << "\\f";
	else if (c == '\a')
		std::cout << "\\a";
	else if (c == '\b')
		std::cout << "\\b";
	else if (c == '\e')
		std::cout << "\\e";
	else
		std::cout << c;
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
		DEBUG_MSG(target.c_str());
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
		std::cout << "error: " << e.what() << std::endl;
		// bc_p();
	}
}

void			ConfigParser::print_info_config(void)
{
	std::cout << "Printing Config Info: " << std::endl << std::endl;

	std::vector<Config>::iterator it_c = this->_servers_config.begin();
	for (; it_c != this->_servers_config.end(); it_c++)
	{
		std::cout << C_G_CYAN << "Server" << C_RES << ": " << std::endl;
		std::cout << "{" << std::endl;
		std::cout << C_G_CYAN << "    host" << C_RES << ": " << it_c->getHost() << std::endl;
		std::cout << C_G_CYAN << "    port" << C_RES << ": " << it_c->getPort() << std::endl;
		std::cout << C_G_CYAN << "    server_name" << C_RES << ": " << it_c->getServerName() << std::endl;
		std::cout << C_G_CYAN << "    host_name" << C_RES << ": " << it_c->getHostName() << std::endl;
		std::cout << C_G_CYAN << "    root_dir" << C_RES << ": " << it_c->getRootDir() << std::endl;
		std::cout << C_G_CYAN << "    max_body_size" << C_RES << ": " << it_c->getMaxBodySize() << std::endl;
		std::cout << C_G_CYAN << "    error_pages" << C_RES << ": " << std::endl;
		std::cout << "    {" << std::endl;
		std::map<int, std::string>::const_iterator it_e = it_c->getErrorPages().begin();
		for (; it_e != it_c->getErrorPages().end(); it_e++)
		{
			std::cout << C_G_CYAN << "        status_code" << C_RES << ": " << it_e->first << " -> " << it_e->second << std::endl;
		}
		std::cout << "    }" << std::endl << std::endl;
		std::map<std::string, Location>::const_iterator it_l = it_c->getLocations().begin();
		while (it_l != it_c->getLocations().end())
		{
			std::cout << C_G_CYAN << "    location" << C_RES << ": " << it_l->first << std::endl;
			std::cout << "    {" << std::endl;
			std::cout << C_G_CYAN << "        uri" << C_RES << ": " << it_l->second.getUri() << std::endl;
			std::cout << C_G_CYAN << "        root_loc" << C_RES << ": " << it_l->second.getRootLoc() << std::endl;
			std::cout << C_G_CYAN << "        index" << C_RES << ": " << it_l->second.getIndex() << std::endl;
			std::cout << C_G_CYAN << "        autoindex" << C_RES << ": " << it_l->second.getAutoindex() << std::endl;
			std::cout << C_G_CYAN << "        upload" << C_RES << ": " << it_l->second.getUpload() << std::endl;
			std::cout << C_G_CYAN << "        alias" << C_RES << ": " << std::endl;
			std::vector<std::string>::const_iterator it_a = it_l->second.getAlias().begin();
			for (; it_a != it_l->second.getAlias().end(); it_a++)
			{
				std::cout << "            " << *it_a;
				if (it_a + 1 != it_l->second.getAlias().end())
					std::cout << ",";
				std::cout << std::endl;
			}
			std::cout << C_G_CYAN << "        methods" << C_RES << ": " << std::endl;
			std::vector<std::string>::const_iterator it_m = it_l->second.getMethods().begin();
			for (; it_m != it_l->second.getMethods().end(); it_m++)
			{
				std::cout << "            " << *it_m;
				if (it_m + 1 != it_l->second.getMethods().end())
					std::cout << ",";
				std::cout << std::endl;
			}
			std::cout << "    }" << std::endl;
			it_l++;
			if (it_l != it_c->getLocations().end())
				std::cout << std::endl;
		}
		std::cout << "}" << std::endl;
		if (it_c + 1 != this->_servers_config.end())
			std::cout << std::endl;
	}

}
