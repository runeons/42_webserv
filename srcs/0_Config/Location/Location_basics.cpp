
# include <webserv.hpp>

Location::Location(void)
{
	// std::cout << GREY << "Location creation..." << C_RES << std::endl;
	this->clear();
}

// Parametric constructor
Location::Location(std::string uri, std::string root_loc, std::string index, bool autoindex, std::vector<std::string> methods, std::string upload, std::vector<std::string> alias, std::string redir_301)
{
	// std::cout << GREY << "Location creation..." << C_RES << std::endl;
	_uri = uri;
	_root_loc = root_loc;
	_index = index;
	_autoindex = autoindex;
	_methods = methods;
	_upload = upload;
	_redir_301 = redir_301;
	_alias = alias;
	return ;
}

Location::Location(const Location & src)
{
	_uri = src.getUri();
	_root_loc = src.getRootLoc();
	_index = src.getIndex();
	_autoindex = src.getAutoindex();
	_methods = src.getMethods();
	_upload = src.getUpload();
	_alias = src.getAlias();
}

// Destructor
Location::~Location(void)
{
	// std::cout << GREY << "Location destruction..." << C_RES << std::endl;
	return;
}

void	Location::clear(void)
{
	this->_uri = "";
	this->_root_loc = "";
	this->_index = "";
	this->_autoindex = false;
	this->_methods.clear();
	this->_upload = "";
	this->_alias.clear();
}


// Assignation operator
Location &	Location::operator=(const Location& rhs)
{
	std::cout << GREY << "Location Assignation operator called" << C_RES << std::endl;
	if (this != &rhs)
	{
		_uri = rhs.getUri();
		_root_loc = rhs.getRootLoc();
		_index = rhs.getIndex();
		_autoindex = rhs.getAutoindex();
		_methods = rhs.getMethods();
		_upload = rhs.getUpload();
		_redir_301 = rhs.getRedir301();
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

std::string Location::getIndex(void) const
{
	return (_index);
}

void Location::setIndex(const std::string index)
{
	_index = index;
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

const std::vector<std::string> & Location::getMethods(void) const
{
	return (_methods);
}

void Location::setMethods(const std::vector<std::string> methods)
{
	_methods = methods;
	return ;
}

std::string Location::getUpload(void) const
{
	return (_upload);
}

void Location::setUpload(const std::string upload)
{
	_upload = upload;
	return ;
}

std::string Location::getRedir301(void) const
{
	return (_redir_301);
}

void Location::setRedir301(const std::string redir_301)
{
	_redir_301 = redir_301;
	return ;
}

const std::vector<std::string> & Location::getAlias(void) const
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

