# include "Config.hpp"

// Default constructor
Config::Config(void)
{
	std::cout << GREY << "Config creation..." << C_RES << std::endl;

	char hostname[1024];

	gethostname(hostname, 1023);
	_host = "127.0.0.1";
	_port = 8000;
	_server_name = "webby";
	_host_name = hostname;
	_root_dir = "./html";
	_max_body_size = 1000000;
	_error_pages = init_map_error_pages();
	// _locations = "";

	return ;
}

// Copy constructor
Config::Config(const Config& src)
{
	std::cout << GREY << "Config creation..." << C_RES << std::endl;
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
		_host = rhs.getHost();
		_port = rhs.getPort();
		_server_name = rhs.getServerName();
		_host_name = rhs.getHostName();
		_root_dir = rhs.getRootDir();
		_max_body_size = rhs.getMaxBodySize();
		_error_pages = rhs.getErrorPages();
		// _locations = rhs.getLocations();
	}
	return (*this);
}

// getters and setters (non static attributes)
std::string Config::getHost(void) const
{
	return (_host);
}

void Config::setHost(const std::string host)
{
	_host = host;
	return ;
}

int Config::getPort(void) const
{
	return (_port);
}

void Config::setPort(const int port)
{
	_port = port;
	return ;
}

std::string Config::getServerName(void) const
{
	return (_server_name);
}

void Config::setServerName(const std::string server_name)
{
	_server_name = server_name;
	return ;
}

std::string Config::getHostName(void) const
{
	return (_host_name);
}

void Config::setHostName(const std::string host_name)
{
	_host_name = host_name;
	return ;
}

std::string Config::getRootDir(void) const
{
	return (_root_dir);
}

void Config::setRootDir(const std::string root_dir)
{
	_root_dir = root_dir;
	return ;
}

int Config::getMaxBodySize(void) const
{
	return (_max_body_size);
}

void Config::setMaxBodySize(const int max_body_size)
{
	_max_body_size = max_body_size;
	return ;
}

std::map<int, std::string> Config::getErrorPages(void) const
{
	return (_error_pages);
}

void Config::setErrorPages(const std::map<int, std::string> error_pages)
{
	_error_pages = error_pages;
	return ;
}

// std::map<std::string, Location &> Config::getLocations(void) const
// {
// 	return (_locations);
// }
//
// void Config::setLocations(const std::map<std::string, Location &> locations)
// {
// 	_locations = locations;
// 	return ;
// }
//
