
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
		std::map<std::string, Location>		_locations;
	public:
		Config();
		Config(const Config & src);
		virtual ~Config();
		void	clear(void);
		void	print_info(void) const;

		const std::string &						get__host(void) const;
		void									set__host(const std::string host);

		const int &								get__port(void) const;
		void									set__port(const int port);

		const std::string &						get__server_name(void) const;
		void									set__server_name(const std::string server_name);

		const std::string &						get__host_name(void) const;
		void									set__host_name(const std::string host_name);

		const std::string &						get__root_dir(void) const;
		void									set__root_dir(const std::string root_dir);

		const int &								get__max_body_size(void) const;
		void									set__max_body_size(const int max_body_size);

		const std::map<int, std::string> &		get__error_pages(void) const;
		void									set__error_pages(const std::map<int, std::string> error_pages);

		const std::map<std::string, Location> &	get__locations(void) const;
		void									set__locations(const std::map<std::string, Location> locations);

		Config									&operator=(const Config & src);

		// std::map<int, std::string>			init_map_error_pages();
		// std::map<std::string, Location>	init_map_locations();

};


#endif
