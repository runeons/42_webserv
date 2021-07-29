# include <webserv.hpp>

// Default constructor
// Location::Location(void)
// {
// 	std::cout << GREY << "Location creation..." << C_RES << std::endl;
// 	return ;
// }
//
// Parametric constructor
Location::Location(std::string uri, std::string root_loc, bool autoindex, std::vector<std::string> methods, std::vector<std::string> upload, std::vector<std::string> alias)
{
	std::cout << GREY << "Location creation..." << C_RES << std::endl;
	_uri = uri;
	_root_loc = root_loc;
	_autoindex = autoindex;
	_methods = methods;
	_upload = upload;
	_alias = alias;
	return ;
}

// Copy constructor
// Location::Location(const Location& src)
// {
// 	std::cout << GREY << "Location creation..." << C_RES << std::endl;
// 	*this = src;
// 	return;
// }

// Destructor
Location::~Location(void)
{
	std::cout << GREY << "Location destruction..." << C_RES << std::endl;
	return;
}

// Assignation operator
Location &	Location::operator=(const Location& rhs)
{
	std::cout << GREY << "Location Assignation operator called" << C_RES << std::endl;
	if (this != &rhs)
	{
		_uri = rhs.getUri();
		_root_loc = rhs.getRootLoc();
		_autoindex = rhs.getAutoindex();
		_methods = rhs.getMethods();
		_upload = rhs.getUpload();
		_alias = rhs.getAlias();
		// _cgi = rhs.getCgi();
	}
	return (*this);
}

// getters and setters (non static attributes)
std::string Location::getUri(void) const
{
	return (_uri);
}

void Location::setUri(const std::string uri)
{
	_uri = uri;
	return ;
}

std::string Location::getRootLoc(void) const
{
	return (_root_loc);
}

void Location::setRootLoc(const std::string root_loc)
{
	_root_loc = root_loc;
	return ;
}

bool Location::getAutoindex(void) const
{
	return (_autoindex);
}

void Location::setAutoindex(const bool autoindex)
{
	_autoindex = autoindex;
	return ;
}

std::vector<std::string> Location::getMethods(void) const
{
	return (_methods);
}

void Location::setMethods(const std::vector<std::string> methods)
{
	_methods = methods;
	return ;
}

std::vector<std::string> Location::getUpload(void) const
{
	return (_upload);
}

void Location::setUpload(const std::vector<std::string> upload)
{
	_upload = upload;
	return ;
}

std::vector<std::string> Location::getAlias(void) const
{
	return (_alias);
}

void Location::setAlias(const std::vector<std::string> alias)
{
	_alias = alias;
	return ;
}
//
// std::map<std::string, std::map<std::string, std::string> > Location::getCgi(void) const
// {
// 	return (_cgi);
// }
//
// void Location::setCgi(const std::map<std::string, std::map<std::string, std::string> > cgi)
// {
// 	_cgi = cgi;
// 	return ;
// }

