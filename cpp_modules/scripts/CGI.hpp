#ifndef CGI_HPP
# define CGI_HPP

# include "webserv.hpp"

class CGI
{
	private:
		std::map<std::string, std::string>	_env_map;
		char **								_env_arr;
		Request &							_request;
		Config &							_config;

	public:
		CGI();
		CGI(const CGI & src);
		virtual ~CGI();

		std::map<std::string, std::string>	getEnvMap(void) const;
		void								setEnvMap(const std::map<std::string, std::string> env_map);
		char **								getEnvArr(void) const;
		void								setEnvArr(const char ** env_arr);
		Request &							getRequest(void) const;
		void								setRequest(const Request & request);
		Config &							getConfig(void) const;
		void								setConfig(const Config & config);


		CGI									&operator=(const CGI & src);
};


#endif
