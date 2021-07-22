#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "webserv.hpp"

class RequestParser;

# define SERVER_NAME "webserv"


typedef enum		e_resp_fields
{
	R_DATE,
	R_SERVER,
	R_CONNECTION,
	R_CONTENT_LENGTH,
	R_CONTENT_TYPE
}					t_resp_fields;


class Client
{
	private:
		SOCKET						_socket;
		int							_status_code;

		// errors
		std::map<int, std::string>	_error_msg;
		std::map<int, std::string>	_error_body;

		// requete
		std::string					_request; // full request
		RequestParser				*_request_parser;

		// reponse
		std::string					_full_path;
		std::map<int, std::string>	_headers_response;


	public:
		Client();
		Client(const Client & src);
		virtual ~Client();

		SOCKET		getSocket(void) const;
		void		setSocket(const SOCKET client_socket);
		std::string	getRequest(void) const;
		void		setRequest(const std::string request);

		void		treat_client(void);
		void		receive_request(void);
		void		check_request(void);

		std::string	get_response_field_name(enum e_resp_fields field);
		std::string generate_status_line(void);
		void		generate_response_header(void);

		void		generate_error_body(void);
		void		construct_full_path(void);

		std::map<int, std::string>	init_map_msg();
		std::map<int, std::string>	init_map_body();
		std::map<int, std::string>	init_map_headers();

		std::string		formatted_header_response(enum e_resp_fields field);
		std::string		r_header_server();
		std::string		r_header_date();
		std::string		r_header_connection();
		std::string		r_header_content_length();
		std::string		r_header_content_type();


		Client		&operator=(const Client & src);
};


#endif
