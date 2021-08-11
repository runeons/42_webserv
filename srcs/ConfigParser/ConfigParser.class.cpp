
#include <webserv.hpp>

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
