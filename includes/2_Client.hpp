
#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <webserv.hpp>

class RequestParser;
class Response;

class Client
{
	private:

		Config & 					_config;
		Location *					_applied_location;

		SOCKET						_socket;
		int							_status_code;

		// request
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
		int							_total_bytes_to_send;
		int							_remaining_bytes_to_send;
		std::vector<char>			_response_vector;

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
		int 			get__status_code(void) const;
		void 			set__status_code(const int code);

		int 			get_remaining_bytes_to_send(void) const;
		void 			set_remaining_bytes_to_send(const int bytes);
		int 			get_total_bytes_to_send(void) const;
		void 			set_total_bytes_to_send(const int bytes);

		Client			&operator=(const Client & src);

		int				is_response_successful(void);

		void			check_method(void);
		void			check_http_version(void);

		size_t			retrieve_request_content_length(std::string buf_str);
		int				calculate_total_bytes_expected(std::string buf_str);
		void			receive_with_content_length(void);
		void			receive_request();

		void			check_request();

		void			adjust_applied_location();
		void			apply_location();

		std::string		apply_alias(std::string);

		std::string		decode_url(std::string &);
		void			parse_parameters();
		std::string		remove_and_store_query(std::string);
		std::string		generate_autoindex(std::string rsc);
		std::string		apply_index_or_autoindex(std::string);
		void			translate_path();

		void			read_resource();

		void			generate_response();

		void			send_response();

		void 			print_response_header(void);
		void 			print_response_body(void);
		void 			print_response(void);

		// void			close(void)
		// {
		// 	::close(this->_socket);
		// }
		//
};


#endif
