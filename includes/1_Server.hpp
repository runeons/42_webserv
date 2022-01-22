
#ifndef SERVER_HPP
# define SERVER_HPP

# include <webserv.hpp>

class Config;
class Client;

class Server
{
	private:
		Server(void);

		std::map<int, Client *>				_clients_map;
		std::map<int, Config>				_servers_map;
		std::vector<Config>					_config_vec;

		struct sockaddr_in					_address;
		fd_set								_read_fds;
		fd_set								_write_fds;
		int									_max_fd;

	public:
		Server(std::vector<Config> config_vec);
		Server(const Server & src);
		virtual ~Server();

		std::map<int, Config>		init_servers_map();
		int							create_server_socket();

		void		stop_server();
		void		stop_one_server(int);

		void		init_fd_sets();
		void		accept_new_connection(int server_socket, Config & config);
		void		receive_and_process_request(int client_socket);
		void		prepare_and_send_response(int client_socket);

		void 		shutdown_client_socket(int client_socket);
		void		select_and_treat_connections();
		int			launch();

};

#endif
