#ifndef LOCATION_HPP
# define LOCATION_HPP

# include <webserv.hpp>

class Location
{
	private:
		std::string					_uri;
		std::string					_alias;
		std::string					_root_loc;
		std::string					_index;
		bool						_autoindex;
		std::vector<std::string>	_methods;
		std::string					_upload;
		std::string					_redir_301;
		// std::map<std::string, std::map<std::string, std::string> >	_cgi;

	public:
		Location(void);
		Location(const Location & src);
		Location(	std::string					uri,
					std::string					root_loc,
					std::string					alias,
					std::string					index,
					bool						autoindex,
					std::vector<std::string>	methods,
					std::string					upload,
					std::string					redir_301);
		virtual ~Location();
		void	clear(void);
		void	print_info(void) const;

		const std::string				&	get__uri(void) const;
		void								set__uri(const std::string uri);

		const std::string				&	get__root_loc(void) const;
		void								set__root_loc(const std::string root_loc);

		const std::string				&	get__alias(void) const;
		void								set__alias(const std::string alias);

		const std::string				&	get__index(void) const;
		void								set__index(const std::string index);

		const bool						&	get__autoindex(void) const;
		void								set__autoindex(const bool autoindex);

		const std::vector<std::string>	&	get__methods(void) const;
		void								set__methods(const std::vector<std::string> methods);

		const std::string				&	get__upload(void) const;
		void								set__upload(const std::string upload);

		const std::string				&	get__redir301(void) const;
		void								set__redir301(const std::string redir_301);

		// std::map<std::string, std::map<std::string, std::string> >	getCgi(void) const;
		// void														setCgi(const std::map<std::string, std::map<std::string, std::string> > cgi);

		Location													&operator=(const Location & src);
};


#endif
