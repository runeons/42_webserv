#ifndef CONFIG_HPP
# define CONFIG_HPP

# include "webserv.hpp"

# define ROOT_DIR	"./html"
# define PORT		8000

class Config
{
	private:
		std::string	_host;					// host_name
		int			_port;					// listen
		std::string	_root_dir;				// root
		// bool		_autoindex;				// autoindex
		// std::string	_index;					// default file if request directory
		// std::string _upload_store;			// make the route able to upload files + configure where it should be saved
		// std::string	_location;				// define a HTTP redirection
		// int			_client_max_body_size;
		// error_pages[num]					// setup default error_pages
		// cgi-bin
		// deny_method						// list of HTTP methods allowed for the route

	public:
		Config();
		Config(const Config & src);
		virtual ~Config();

		std::string	getHost(void) const;
		void		setHost(const std::string host);
		int			getPort(void) const;
		void		setPort(const int port);
		std::string	getRootDir(void) const;
		void		setRootDir(const std::string rootDir);

		Config		&operator=(const Config & src);
};

#endif
