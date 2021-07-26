# include "CGI.hpp"

// Default constructor
CGI::CGI(void)
{
	std::cout << GREY << "CGI creation..." << C_RES << std::endl;
	return ;
}

// Copy constructor
CGI::CGI(const CGI& src)
{
	std::cout << GREY << "CGI creation..." << C_RES << std::endl;
	*this = src;
	return;
}

// Destructor
CGI::~CGI(void)
{
	std::cout << GREY << "CGI destruction..." << C_RES << std::endl;
	return;
}

// Assignation operator
CGI &	CGI::operator=(const CGI& rhs)
{
	std::cout << GREY << "CGI Assignation operator called" << C_RES << std::endl;
	if (this != &rhs)
	{
		this->_env_map = rhs.getEnvMap();
		this->_env_arr = rhs.getEnvArr();
		this->_request = rhs.getRequest();
		this->_config = rhs.getConfig();
	}
	return (*this);
}

// getters and setters (non static attributes)
std::map<std::string, std::string> CGI::getEnvMap(void) const
{
	return (this->_env_map);
}

void CGI::setEnvMap(const std::map<std::string, std::string> env_map)
{
	this->_env_map = env_map;
	return ;
}

char ** CGI::getEnvArr(void) const
{
	return (this->_env_arr);
}

void CGI::setEnvArr(const char ** env_arr)
{
	this->_env_arr = env_arr;
	return ;
}

Request & CGI::getRequest(void) const
{
	return (this->_request);
}

void CGI::setRequest(const Request & request)
{
	this->_request = request;
	return ;
}

Config & CGI::getConfig(void) const
{
	return (this->_config);
}

void CGI::setConfig(const Config & config)
{
	this->_config = config;
	return ;
}

