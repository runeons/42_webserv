
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

		SOCKET			get__socket(void) const;
		void			set__socket(const SOCKET client_socket);
		std::string		get__request(void) const;
		void			set__request(const std::string request);
		Location *		get__applied_location(void) const;
		void			set__applied_location(Location * applied_location);
		int 			get__remaining_bytes_to_recv(void) const;
		void 			set__remaining_bytes_to_recv(const int bytes);
		int 			get__total_bytes_expected(void) const;
		void 			set__total_bytes_expected(const int bytes);
		int 			get__status_code(void) const;
		void 			set__status_code(const int code);
		Config & 		get__config(void) const;
		void 			set__config(const Config & config);
		int 			get__remaining_bytes_to_send(void) const;
		void 			set__remaining_bytes_to_send(const int bytes);
		int 			get__total_bytes_to_send(void) const;
		void 			set__total_bytes_to_send(const int bytes);

		Client			&operator=(const Client & src);

		int				is_response_successful(void);

		void			check_method(void);
		void			check_http_version(void);
		void			check_body_size(void);

		size_t			retrieve_request_content_length(std::string buf_str);
		int				calculate_total_bytes_expected(std::string buf_str);
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

};


#endif
