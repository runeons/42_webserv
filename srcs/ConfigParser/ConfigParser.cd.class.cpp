
#include <webserv.hpp>

ConfigParser::ConfigParser(void) {} // constructor
ConfigParser::ConfigParser(std::string file)  // params constructor
{
	this->_config_raw = file;
	this->_head = 0;
	this->_head_last_digest = 0;
	this->start_parsing();
}

ConfigParser::~ConfigParser(void) // destructor
{

}
