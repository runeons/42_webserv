/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantoni <tsantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 18:42:35 by tsantoni          #+#    #+#             */
/*   Updated: 2021/07/26 15:24:47 by tharchen         ###   ########.fr       */
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
		ssize_t						_bytes_read;

		std::string					_full_path;

		std::string					_query_string;
		std::map<std::string, std::string>	_parameters;


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

		Client		&operator=(const Client & src);

		void			check_method(void);
		void			check_http_version(void);

		void			receive_request();
		void			check_request();
		void			parse_parameters();
		void			construct_full_path();
		void			read_resource();
		void			generate_response();
		void			send_response();
		void			treat_client();
		void			close(void)
		{
			::close(this->_socket);
		}

};


#endif
