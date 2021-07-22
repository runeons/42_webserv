#ifndef SERVER_HPP
# define SERVER_HPP

// # include "webserv.hpp"
# include <iostream>
# include <string>
# include "color.hpp"
# include "Config.hpp"

class Config;

class Server
{
	private:
		Config *			_config;
		SOCKET				_server_socket;
		SOCKET				_client_socket;
		struct sockaddr_in	_address;

	public:
		Server();
		Server(const Server & src);
		virtual ~Server();

		Config *	getConfig(void) const;
		void		setConfig(Config * config);
		SOCKET		getServerSocket(void) const;
		void		setServerSocket(const SOCKET server_socket);
		SOCKET		getClientSocket(void) const;
		void		setClientSocket(const SOCKET client_socket);

		void		create_server_socket();
		void		bind_address_and_port();
		void		stop_server();
		void		listen();
		int			launch();
		void 		print_config(void);

		Server		&operator=(const Server & src);
};

#endif
