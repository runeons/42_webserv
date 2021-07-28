# include "Location.hpp"

// Default constructor
Location::Location(void)
{
	std::cout << GREY << "Location creation..." << C_RES << std::endl;
	return ;
}

// Copy constructor
Location::Location(const Location& src)
{
	std::cout << GREY << "Location creation..." << C_RES << std::endl;
	*this = src;
	return;
}

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
		this->_uri = rhs.getUri();
		this->_root_loc = rhs.getRootLoc();
		this->_autoindex = rhs.getAutoindex();
		this->_methods = rhs.getMethods();
		this->_upload = rhs.getUpload();
		this->_alias = rhs.getAlias();
		this->_cgi = rhs.getCgi();
	}
	return (*this);
}

// getters and setters (non static attributes)
std::string Location::getUri(void) const
{
	return (this->_uri);
}

void Location::setUri(const std::string uri)
{
	this->_uri = uri;
	return ;
}

std::string Location::getRootLoc(void) const
{
	return (this->_root_loc);
}

void Location::setRootLoc(const std::string root_loc)
{
	this->_root_loc = root_loc;
	return ;
}

bool Location::getAutoindex(void) const
{
	return (this->_autoindex);
}

void Location::setAutoindex(const bool autoindex)
{
	this->_autoindex = autoindex;
	return ;
}

std::vector<std::string> Location::getMethods(void) const
{
	return (this->_methods);
}

void Location::setMethods(const std::vector<std::string> methods)
{
	this->_methods = methods;
	return ;
}

std::map<bool, std::string> Location::getUpload(void) const
{
	return (this->_upload);
}

void Location::setUpload(const std::map<bool, std::string> upload)
{
	this->_upload = upload;
	return ;
}

std::vector<std::string> Location::getAlias(void) const
{
	return (this->_alias);
}

void Location::setAlias(const std::vector<std::string> alias)
{
	this->_alias = alias;
	return ;
}

std::map<std::string, std::map<std::string, std::string> > Location::getCgi(void) const
{
	return (this->_cgi);
}

void Location::setCgi(const std::map<std::string, std::map<std::string, std::string> > cgi)
{
	this->_cgi = cgi;
	return ;
}

