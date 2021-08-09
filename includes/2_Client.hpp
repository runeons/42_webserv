/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_Client.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantoni <tsantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 18:42:35 by tsantoni          #+#    #+#             */
/*   Updated: 2021/08/09 17:39:19 by tsantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <webserv.hpp>
# define PATH_AUTOINDEX "autoindex_res"

class RequestParser;
class Response;

class Client
{
	private:

		Config & 					_config;
		Location *					_applied_location;

		SOCKET						_socket;
		int							_status_code;

		// requete
		std::string					_request; // full request
		RequestParser				*_request_parser;
		ssize_t						_bytes_read;
		char						_chunk[MAX_RCV];
		int							_total_bytes_expected;
		int							_remaining_bytes_to_recv;

		std::string					_translated_path;

		std::string					_query_string;
		std::map<std::string, std::string>	_parameters;


		// response
		Response					*_response;
		std::string					_page_content;

		Client();
		Client(const Client & src);

	public:
		Client(Config & config);
		virtual ~Client();

		SOCKET			getSocket(void) const;
		void			setSocket(const SOCKET client_socket);
		std::string		getRequest(void) const;
		void			setRequest(const std::string request);
		Location *		getAppliedLocation(void) const;
		void			setAppliedLocation(Location * applied_location);
		int 			get_remaining_bytes_to_recv(void) const;
		void 			set_remaining_bytes_to_recv(const int bytes);
		int 			get_total_bytes_expected(void) const;
		void 			set_total_bytes_expected(const int bytes);

		Client		&operator=(const Client & src);

		void			check_method(void);
		void			check_http_version(void);

		void			receive_first(void);
		size_t			retrieve_request_content_length(std::string buf_str);
		int				calculate_total_bytes_expected(std::string buf_str);
		void			receive_with_content_length(void);
		void			receive_request();
		void			check_request();
		void			parse_parameters();
		std::string		apply_alias(std::string);
		void			apply_location();
		std::string		decode_url(std::string);
		void			translate_path();
		std::string		generate_autoindex(std::string rsc);
		void			read_resource();
		void			generate_response();
		void			send_response();
		void			client_receive_request();
		void			client_send_response();
		void			treat_client();
		void			close(void)
		{
			::close(this->_socket);
		}

};


#endif
