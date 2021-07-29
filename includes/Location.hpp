#ifndef LOCATION_HPP
# define LOCATION_HPP

# include <webserv.hpp>

class Location
{
	private:
		std::string													_uri;
		std::string													_root_loc;
		bool														_autoindex;
		std::vector<std::string>									_methods;
		std::vector<std::string>									_upload;
		std::vector<std::string>									_alias;
		// std::map<std::string, std::map<std::string, std::string> >	_cgi;
		Location();
		Location(const Location & src);

	public:
		Location(std::string uri, std::string root_loc, bool autoindex,
			std::vector<std::string> methods, std::vector<std::string> upload, std::vector<std::string> alias); // tmp constructor
		virtual ~Location();

		std::string													getUri(void) const;
		void														setUri(const std::string uri);
		std::string													getRootLoc(void) const;
		void														setRootLoc(const std::string root_loc);
		bool														getAutoindex(void) const;
		void														setAutoindex(const bool autoindex);
		std::vector<std::string>									getMethods(void) const;
		void														setMethods(const std::vector<std::string> methods);
		std::vector<std::string>									getUpload(void) const;
		void														setUpload(const std::vector<std::string> upload);
		std::vector<std::string>									getAlias(void) const;
		void														setAlias(const std::vector<std::string> alias);
		// std::map<std::string, std::map<std::string, std::string> >	getCgi(void) const;
		// void														setCgi(const std::map<std::string, std::map<std::string, std::string> > cgi);

		Location													&operator=(const Location & src);
};


#endif
