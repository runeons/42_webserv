
# include <webserv.hpp>

// Parameter constructor
Cgi::Cgi(RequestParser & request, Config & config, Location & applied_location, int type, std::string query_string) : _request(request), _config(config), _applied_location(applied_location), _type(type)
{
	std::cout << C_HIDDEN << "Cgi creation..." << C_RES << std::endl;
	_query_string = query_string;
	_map_http = init_map_http();
	_env_map = init_map_env();
	_env_arr = NULL;
	if (type == CGI_UPLOAD)
		_bin = "/usr/bin/php-cgi7.4";
	if (type == CGI_EXTENSION)
		_bin = "/usr/bin/perl";
	return ;
}

// Destructor
Cgi::~Cgi(void)
{
	std::cout << C_HIDDEN << "Cgi destruction..." << C_RES << std::endl;
	delete_env_arr();
	return;
}

// Assignation operator
Cgi &	Cgi::operator=(const Cgi& rhs)
{
	std::cout << C_HIDDEN << "Cgi Assignation operator called" << C_RES << std::endl;
	if (this != &rhs)
	{
		_env_map = rhs.get__env_map();
		_map_http = rhs.get__map_http();
		_env_arr = rhs.get__env_arr();
		_request = rhs.get__request();
		_config = rhs.get__config();
		_applied_location = rhs.get__applied_location();
		// _bin = rhs.get__bin();
		// _query_string = rhs.get__query_string();
		// _type = rhs.get__type();
	}
	return (*this);
}

// getters and setters (non static attributes)
std::map<std::string, std::string> Cgi::get__env_map(void) const
{
	return (_env_map);
}

void Cgi::set__env_map(const std::map<std::string, std::string> env_map)
{
	_env_map = env_map;
	return ;
}
std::map<std::string, std::string> Cgi::get__map_http(void) const
{
	return (_map_http);
}

void Cgi::set__map_http(const std::map<std::string, std::string> map_http)
{
	_map_http = map_http;
	return ;
}

std::string Cgi::get__full_buf(void) const
{
	return (_full_buf);
}

void Cgi::set__full_buf(const std::string full_buf)
{
	_full_buf = full_buf;
	return ;
}

char ** Cgi::get__env_arr(void) const
{
	return (_env_arr);
}

RequestParser & Cgi::get__request(void) const
{
	return (_request);
}

void Cgi::set__request(const RequestParser & request)
{
	_request = request;
	return ;
}

Config & Cgi::get__config(void) const
{
	return (_config);
}

void Cgi::set__config(const Config & config)
{
	_config = config;
	return ;
}

Location & Cgi::get__applied_location(void) const
{
	return (_applied_location);
}

void Cgi::set__applied_location(const Location & applied_location)
{
	_applied_location = applied_location;
	return ;
}
