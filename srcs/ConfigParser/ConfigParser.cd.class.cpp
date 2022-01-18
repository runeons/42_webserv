
#include <webserv.hpp>

int	ConfigParser::ConfigParserErrorChecking(void)
{
	std::vector<Config>::const_iterator it_c = this->_servers_config.begin();
	while (it_c != this->_servers_config.end())
	{
		int	uri_slash = 0;
		int	lerror = 0;
		std::map<std::string, Location>::const_iterator it_l = it_c->get__locations().begin();
		while (it_l != it_c->get__locations().end())
		{
			if (!strcmp(it_l->second.get__uri().c_str(), "/"))
				uri_slash++;
			if (it_l->second.get__uri().c_str()[0] != '/')
			{
				std::cout << C_G_RED << "config file error: " << C_G_WHITE << "location \'" << it_l->second.get__uri().c_str() << "\' should start with \'/\'" << std::endl;
				lerror++;
			}
			it_l++;
		}
		if (!uri_slash)
		{
			std::cout << C_G_RED << "config file error: " << C_G_WHITE << "no \'/\' location found." << std::endl;
			exit(-1);
		}
		else if (uri_slash > 1)
			std::cout << C_G_MAGENTA << "config file warning: " << C_G_WHITE << "multiple \'/\' location found." << std::endl;
		if (lerror)
			exit(-1);
		it_c++;
	}
	return (0);
}

// ConfigParser::ConfigParser(void) {} // constructor
ConfigParser::ConfigParser(std::string file)  // params constructor
{
	std::cout << C_HIDDEN << "...ConfigParser creation..." << C_RES << std::endl;
	this->_config_raw = file;
	this->_head = 0;
	this->_head_last_digest = 0;
	this->start_parsing();
	ConfigParserErrorChecking();
}

ConfigParser::~ConfigParser(void) // destructor
{
	std::cout << C_HIDDEN << "...ConfigParser destruction..." << C_RES << std::endl;
}
