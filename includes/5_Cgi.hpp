
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
		std::string							_script_name;
		// Config &							_config;
		std::string							_full_buf;

		std::map<std::string, std::string>	_env_map;
		std::map<std::string, std::string>	_map_http;
		char **								_env_arr;

	public:
		Cgi(RequestParser & request, std::string script_name);
		virtual ~Cgi();

		std::map<std::string, std::string>	getEnvMap(void) const;
		void								setEnvMap(const std::map<std::string, std::string> env_map);
		char **								getEnvArr(void) const;
		RequestParser &						getRequest(void) const;
		void								setRequest(const RequestParser & request);
		std::string							getFullBuf(void) const;
		void								setFullBuf(const std::string full_buf);

		// Config &							getConfig(void) const;
		// void								setConfig(const Config & config);
		Cgi									&operator=(const Cgi & src);

		void	setup_metavariables(void);
		void	transform_to_envp(void);
		void	exec_script(void);
		void	launch(void);

		std::map<std::string, std::string>	init_map_env();
		std::map<std::string, std::string>	init_map_http();
};


#endif
