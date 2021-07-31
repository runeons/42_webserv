#ifndef CONFIG_HPP
# define CONFIG_HPP

# include <webserv.hpp>

// # define ROOT_DIR	"./html"
// # define PORT		8000

class Location;

class Config
{
	private:
		std::string							_host;
		int									_port;
		std::string							_server_name;
		std::string							_host_name;
		std::string							_root_dir;
		int									_max_body_size;
		std::map<int, std::string>			_error_pages;
		// Location *							_loc;
		std::map<std::string, Location *>	_locations;
	public:
		Config();
		Config(const Config & src);
		virtual ~Config();

		std::string							getHost(void) const;
		void								setHost(const std::string host);
		int									getPort(void) const;
		void								setPort(const int port);
		std::string							getServerName(void) const;
		void								setServerName(const std::string server_name);
		std::string							getHostName(void) const;
		void								setHostName(const std::string host_name);
		std::string							getRootDir(void) const;
		void								setRootDir(const std::string root_dir);
		int									getMaxBodySize(void) const;
		void								setMaxBodySize(const int max_body_size);
		std::map<int, std::string>			getErrorPages(void) const;
		void								setErrorPages(const std::map<int, std::string> error_pages);
		std::map<std::string, Location *>	getLocations(void) const;
		void								setLocations(const std::map<std::string, Location *> locations);
		Config								&operator=(const Config & src);

		std::map<int, std::string>			init_map_error_pages();
		std::map<std::string, Location *>	init_map_locations();

};


#endif
