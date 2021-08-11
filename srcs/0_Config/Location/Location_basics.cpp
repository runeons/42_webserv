
# include <webserv.hpp>

Location::Location(void)
{
	// std::cout << GREY << "Location creation..." << C_RES << std::endl;
	this->clear();
}

// Parametric constructor
Location::Location(std::string uri, std::string root_loc, std::string alias, std::string index, bool autoindex, std::vector<std::string> methods, std::string upload, std::string redir_301)
{
	// std::cout << GREY << "Location creation..." << C_RES << std::endl;
	_uri = uri;
	_root_loc = root_loc;
	_alias = alias;
	_index = index;
	_autoindex = autoindex;
	_methods = methods;
	_upload = upload;
	_redir_301 = redir_301;
	return ;
}

Location::Location(const Location & src)
{
	_uri = src.get__uri();
	_root_loc = src.get__root_loc();
	_alias = src.get__alias();
	_index = src.get__index();
	_autoindex = src.get__autoindex();
	_methods = src.get__methods();
	_upload = src.get__upload();
	_redir_301 = src.get__redir301();
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
	this->_alias = "";
	this->_root_loc = "";
	this->_index = "";
	this->_autoindex = false;
	this->_methods.clear();
	this->_upload = "";
	this->_redir_301 = "";
}


// Assignation operator
Location &	Location::operator=(const Location & rhs)
{
	std::cout << GREY << "Location Assignation operator called" << C_RES << std::endl;
	if (this != &rhs)
	{
		_uri = rhs.get__uri();
		_root_loc = rhs.get__root_loc();
		_root_loc = rhs.get__alias();
		_index = rhs.get__index();
		_autoindex = rhs.get__autoindex();
		_methods = rhs.get__methods();
		_upload = rhs.get__upload();
		_redir_301 = rhs.get__redir301();
		// _cgi = rhs.getCgi();
	}
	return (*this);
}

// getters and setters (non static attributes)
const std::string &					Location::get__uri(void) 		const { return (_uri);			}
const std::string &					Location::get__root_loc(void) 	const { return (_root_loc);		}
const std::string &					Location::get__alias(void) 		const { return (_alias);		}
const std::string &					Location::get__index(void) 		const { return (_index);		}
const bool &						Location::get__autoindex(void) 	const { return (_autoindex);	}
const std::vector<std::string> & 	Location::get__methods(void) 	const { return (_methods);		}
const std::string &					Location::get__upload(void) 	const { return (_upload);		}
const std::string &					Location::get__redir301(void) 	const { return (_redir_301);	}

void Location::set__uri			(const std::string uri)					{ _uri		 = uri;			}
void Location::set__root_loc	(const std::string root_loc)			{ _root_loc	 = root_loc;	}
void Location::set__alias		(const std::string alias)				{ _alias	 = alias;		}
void Location::set__index		(const std::string index)				{ _index	 = index;		}
void Location::set__autoindex	(const bool autoindex)					{ _autoindex = autoindex;	}
void Location::set__methods		(const std::vector<std::string> methods){ _methods	 = methods;		}
void Location::set__upload		(const std::string upload)				{ _upload	 = upload;		}
void Location::set__redir301	(const std::string redir_301)			{ _redir_301 = redir_301;	}

//
// std::map<std::string, std::map<std::string, std::string> > Location::getCgi(void) const
// {
// 	return (_cgi);
// }
//
// void Location::setCgi(const std::map<std::string, std::map<std::string, std::string> > cgi)
// {
// 	_cgi = cgi;
// }

