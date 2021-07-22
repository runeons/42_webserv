# include "Config.hpp"

// Default constructor
Config::Config(void) : _host(""), _port(8000), _root_dir("./server_root")
{
	char hostname[1024];

	std::cout << GREY << "Config creation..." << C_RES << std::endl;
	gethostname(hostname, 1023);
	this->_host = hostname;

	return ;
}

// Copy constructor
Config::Config(const Config& src)
{
	std::cout << GREY << "Config copy creation..." << C_RES << std::endl;
	*this = src;
	return;
}

// Destructor
Config::~Config(void)
{
	std::cout << GREY << "Config destruction..." << C_RES << std::endl;
	return;
}

// Assignation operator
Config &	Config::operator=(const Config& rhs)
{
	std::cout << GREY << "Config Assignation operator called" << C_RES << std::endl;
	if (this != &rhs)
	{
		this->_host = rhs.getHost();
		this->_port = rhs.getPort();
		this->_root_dir = rhs.getRootDir();
	}
	return (*this);
}

// getters and setters (non static attributes)
std::string Config::getHost(void) const
{
	return (this->_host);
}

void Config::setHost(const std::string host)
{
	this->_host = host;
	return ;
}

int Config::getPort(void) const
{
	return (this->_port);
}

void Config::setPort(const int port)
{
	this->_port = port;
	return ;
}

std::string Config::getRootDir(void) const
{
	return (this->_root_dir);
}

void Config::setRootDir(const std::string rootDir)
{
	this->_root_dir = rootDir;
	return ;
}


