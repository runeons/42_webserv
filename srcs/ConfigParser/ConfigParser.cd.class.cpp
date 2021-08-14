
#include <webserv.hpp>

// ConfigParser::ConfigParser(void) {} // constructor
ConfigParser::ConfigParser(std::string file)  // params constructor
{
	std::cout << GREY << "ConfigParser creation..." << C_RES << std::endl;
	this->_config_raw = file;
	this->_head = 0;
	this->_head_last_digest = 0;
	this->start_parsing();
}

ConfigParser::~ConfigParser(void) // destructor
{
	std::cout << GREY << "ConfigParser destruction..." << C_RES << std::endl;
}
