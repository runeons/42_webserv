/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantoni <tsantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 18:42:35 by tsantoni          #+#    #+#             */
/*   Updated: 2021/07/24 18:42:36 by tsantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "webserv.hpp"

class RequestParser;
class Response;

class Client
{
	private:
		SOCKET						_socket;
		int							_status_code;

		// requete
		std::string					_request; // full request
		RequestParser				*_request_parser;

		std::string					_full_path;

		// response
		Response					*_response;
		std::string					_page_content;


	public:
		Client();
		Client(const Client & src);
		virtual ~Client();

		SOCKET			getSocket(void) const;
		void			setSocket(const SOCKET client_socket);
		std::string		getRequest(void) const;
		void			setRequest(const std::string request);

		void			treat_client();
		void			receive_request();
		void			check_request();
		void			construct_full_path();
		void			read_resource();
		void			generate_response();
		void			send_response();

		Client		&operator=(const Client & src);
};


#endif
