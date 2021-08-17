
#ifndef CGI_HPP
# define CGI_HPP

# include <webserv.hpp>

# define BUFS 4096

class RequestParser;
class Config;

class Cgi
{
	private:
		Cgi();
		Cgi(const Cgi & src);

		RequestParser &						_request;
		Config &							_config;
		Location &							_applied_location;
		std::string							_bin;
		std::string							_full_buf;
		std::string							_query_string;
		int									_type;

		std::map<std::string, std::string>	_env_map;
		std::map<std::string, std::string>	_map_http;
		char **								_env_arr;

	public:
		Cgi(RequestParser & request, Config & config, Location & applied_location, int type, std::string query_string);
		virtual ~Cgi();

		std::map<std::string, std::string>	get__env_map(void) const;
		void								set__env_map(const std::map<std::string, std::string> env_map);
		std::map<std::string, std::string>	get__map_http(void) const;
		void								set__map_http(const std::map<std::string, std::string> map_http);
		char **								get__env_arr(void) const;
		RequestParser &						get__request(void) const;
		void								set__request(const RequestParser & request);
		std::string							get__full_buf(void) const;
		void								set__full_buf(const std::string full_buf);
		Config &							get__config(void) const;
		void								set__config(const Config & config);
		Location &							get__applied_location(void) const;
		void								set__applied_location(const Location & applied_location);
		Cgi									&operator=(const Cgi & src);

		void	setup_metavariables(void);
		void	delete_env_arr(void);
		void	transform_to_envp(void);
		void	exec_script(void);
		void	launch(void);

		std::map<std::string, std::string>	init_map_env();
		std::map<std::string, std::string>	init_map_http();
};


#endif
