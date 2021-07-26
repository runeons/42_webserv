# include "Cgi.hpp"

// Default constructor
// Cgi::Cgi(void)
// {
// 	std::cout << GREY << "Cgi creation..." << C_RES << std::endl;
// 	return ;
// }

// Parameter constructor
Cgi::Cgi(RequestParser & request) : _request(request)
{
	std::cout << GREY << "Cgi creation..." << C_RES << std::endl;
	// env_map =
	_env_arr = NULL;
	return ;
}
//
// // Copy constructor
// Cgi::Cgi(const Cgi& src)
// {
// 	std::cout << GREY << "Cgi creation..." << C_RES << std::endl;
// 	*this = src;
// 	return;
// }

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
		this->_env_map = rhs.getEnvMap();
		this->_env_arr = rhs.getEnvArr();
		this->_request = rhs.getRequest();
		// this->_config = rhs.getConfig();
	}
	return (*this);
}

// getters and setters (non static attributes)
std::map<std::string, std::string> Cgi::getEnvMap(void) const
{
	return (this->_env_map);
}

void Cgi::setEnvMap(const std::map<std::string, std::string> env_map)
{
	this->_env_map = env_map;
	return ;
}

char ** Cgi::getEnvArr(void) const
{
	return (this->_env_arr);
}

// void Cgi::setEnvArr(const char ** env_arr)
// {
// 	this->_env_arr = env_arr;
// 	return ;
// }
//
RequestParser & Cgi::getRequest(void) const
{
	return (this->_request);
}

void Cgi::setRequest(const RequestParser & request)
{
	this->_request = request;
	return ;
}

// Config & Cgi::getConfig(void) const
// {
// 	return (this->_config);
// }
//
// void Cgi::setConfig(const Config & config)
// {
// 	this->_config = config;
// 	return ;
// }
