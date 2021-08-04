/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_Server.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantoni <tsantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 18:42:48 by tsantoni          #+#    #+#             */
/*   Updated: 2021/08/04 20:32:55 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <webserv.hpp>

# define MAX_CLIENTS 50
# define CHUNK 512

class Config;
class Client;

class Server
{
	private:
		Config *				_config;
		// Client *				_client;
		std::vector<Client *>	_clients;
		SOCKET					_master_socket;
		struct sockaddr_in		_address;
		fd_set					_read_fds;
		fd_set					_write_fds;
		fd_set					_active_fds;
		std::vector<int>		_sockets_used;

	public:
		Server(void);
		Server(const Config & config);
		Server(const Server & src);
		virtual ~Server();

		Config *	getConfig(void) const;
		void		setConfig(Config * config);
		// Client *	getClient(void) const;
		// void		setClient(Client * client);
		SOCKET		getSocket(void) const;
		void		setSocket(const SOCKET server_socket);
		// Client *	get_client_from_socket(int socket);

		void		stop_server();
		void 		print_config(void);
		void		create_server_socket();
		void		bind_address_and_port();
		void		listen_connections();

		void		treat_incoming_new_connection_for_reading(int);
		void		treat_incoming_existing_connection_for_reading(int);
		void		treat_incoming_connection_for_writing(int);
		void		select_and_treat_connections();
		int			launch();

		Server		&operator=(const Server & src);
};

#endif
