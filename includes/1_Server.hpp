#ifndef SERVER_HPP
# define SERVER_HPP

# include <webserv.hpp>

class Config;
class Client;

class Server
{
	private:
		Config *				_config;
		std::map<int, Client *>	_clients_map;

		SOCKET					_master_socket;
		struct sockaddr_in		_address;
		fd_set					_read_fds;
		fd_set					_write_fds;
		int						_max_fd;

	public:
		Server(void);
		Server(const Config & config);
		Server(const Server & src);
		virtual ~Server();

		Config *	getConfig(void) const;
		void		setConfig(Config * config);
		SOCKET		getSocket(void) const;
		void		setSocket(const SOCKET server_socket);

		void		stop_server();
		void 		print_config(void);
		void		create_server_socket();
		void		bind_address_and_port();
		void		listen_connections();

		void		init_fd_sets();
		void		accept_new_connection(int server_socket);
		void		receive_and_process_request(int client_socket);
		void		prepare_and_send_response(int client_socket);

		void		select_and_treat_connections();
		int			launch();

		Server		&operator=(const Server & src);
};

#endif
