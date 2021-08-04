/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_Server.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantoni <tsantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 18:42:48 by tsantoni          #+#    #+#             */
/*   Updated: 2021/08/04 20:23:37 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <webserv.hpp>

class Config;
class Client;

class Server
{
	private:
		Config *			_config;
		Client *			_client;
		SOCKET				_socket;
		struct sockaddr_in	_address;

	public:
		Server(void);
		Server(const Config & config);
		Server(const Server & src);
		virtual ~Server();

		Config *	getConfig(void) const;
		void		setConfig(Config * config);
		Client *	getClient(void) const;
		void		setClient(Client * client);
		SOCKET		getSocket(void) const;
		void		setSocket(const SOCKET server_socket);

		void		stop_server();
		void 		print_config(void);
		void		create_server_socket();
		void		bind_address_and_port();
		void		listen_and_treat_connection();
		int			launch();

		Server		&operator=(const Server & src);
};

#endif
