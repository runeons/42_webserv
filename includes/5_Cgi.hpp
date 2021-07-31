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
		// Config &							_config;

		std::map<std::string, std::string>	_env_map;
		char **								_env_arr;

	public:
		Cgi(RequestParser & request);
		virtual ~Cgi();

		std::map<std::string, std::string>	getEnvMap(void) const;
		void								setEnvMap(const std::map<std::string, std::string> env_map);
		char **								getEnvArr(void) const;
		// void								setEnvArr(const char ** env_arr);
		RequestParser &						getRequest(void) const;
		void								setRequest(const RequestParser & request);
		// Config &							getConfig(void) const;
		// void								setConfig(const Config & config);
		Cgi									&operator=(const Cgi & src);

		void	setup_metavariables(void);
		void	transform_to_envp(void);
		void	exec_script(void);
		void	launch(void);

		std::map<std::string, std::string>	init_map_env();
};


#endif
