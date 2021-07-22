#ifndef CONFIG_HPP
# define CONFIG_HPP

# include "webserv.hpp"

class Config
{
	private:
		std::string	_host;
		int			_port;
		std::string	_root_dir;

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
