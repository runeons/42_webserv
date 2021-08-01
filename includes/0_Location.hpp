#ifndef LOCATION_HPP
# define LOCATION_HPP

# include <webserv.hpp>

class Location
{
	private:
		std::string								_uri;
		std::string								_root_loc;
		std::string								_index;
		bool									_autoindex;
		std::vector<std::string>				_methods;
		std::string								_upload;
		std::vector<std::string>				_alias;
		std::string								_redir_301;
		// std::map<std::string, std::map<std::string, std::string> >	_cgi;
		Location();
		Location(const Location & src);

	public:
		Location(std::string uri, std::string root_loc, std::string index, bool autoindex,
			std::vector<std::string> methods, std::string upload, std::vector<std::string> alias, std::string redir_301); // tmp constructor
		virtual ~Location();

		std::string													getUri(void) const;
		void														setUri(const std::string uri);
		std::string													getRootLoc(void) const;
		void														setRootLoc(const std::string root_loc);
		std::string													getIndex(void) const;
		void														setIndex(const std::string index);
		bool														getAutoindex(void) const;
		void														setAutoindex(const bool autoindex);
		std::vector<std::string>									getMethods(void) const;
		void														setMethods(const std::vector<std::string> methods);
		std::string													getUpload(void) const;
		void														setUpload(const std::string upload);
		std::string													getRedir301(void) const;
		void														setRedir301(const std::string redir_301);
		std::vector<std::string>									getAlias(void) const;
		void														setAlias(const std::vector<std::string> alias);
		// std::map<std::string, std::map<std::string, std::string> >	getCgi(void) const;
		// void														setCgi(const std::map<std::string, std::map<std::string, std::string> > cgi);

		Location													&operator=(const Location & src);
};


#endif
