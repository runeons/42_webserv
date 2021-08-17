
#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include <webserv.hpp>

// discord server_name : "Ca lie avec le header HTTP Host Si tu match avec au moins un serveur name tu choisis un block serveur different"
# define SERVER_NAME "webserv"
# define PATH_CMD_RES "cmd_res"
# define DIR_ERROR_PAGES "./html/error_pages/"

typedef enum		e_resp_fields
{
	R_DATE,
	R_SERVER,
	R_CONNECTION,
	R_CONTENT_LENGTH,
	R_CONTENT_TYPE,
	R_LOCATION
}					t_resp_fields;

class Response
{
	private:
		Response();
		Response(const Response & src);

		Config &					_config;
		Location &					_applied_location;

		int							_status_code;
		std::string					_page_content;
		std::string					_translated_path;
		std::string					_type_mime;
		std::string					_charset;

		RequestParser &				_request;

		std::string					_response;
		std::string					_response_header;
		std::string					_response_body;
		std::map<int, std::string>	_headers_response;
		std::map<int, std::string>	_error_msg;
		std::map<int, std::string>	_error_content;

	public:
		// Response_basics
		Response(Config & config, Location & applied_location, int status_code, std::string page_content, std::string translated_path, RequestParser & request);
		virtual ~Response();

		int							getStatusCode(void) const;
		void						setStatusCode(const int status_code);
		std::string					getFullPath(void) const;
		void						setFullPath(const std::string translated_path);
		std::string					getResponse(void) const;
		void						setResponse(const std::string response);
		std::string					getResponseHeader(void) const;
		void						setResponseHeader(const std::string response_header);
		std::string					getResponseBody(void) const;
		void						setResponseBody(const std::string response_body);
		std::map<int, std::string>	getErrorMsg(void) const;
		void						setErrorMsg(const std::map<int, std::string> error_msg);
		std::map<int, std::string>	getErrorBody(void) const;
		void						setErrorBody(const std::map<int, std::string> error_body);
		std::map<int, std::string>	getHeadersResponse(void) const;
		void						setHeadersResponse(const std::map<int, std::string> headers_response);
		std::string					getPageContent(void) const;
		void						setPageContent(const std::string page_content);

		Response					&operator=(const Response & src);

		// Utils
		int							is_response_successful(void);
		std::string					return_status_line();
		void						print_status_line();

		// Response_init_maps
		std::map<int, std::string>	init_map_msg();
		std::map<int, std::string>	init_map_body();
		std::map<int, std::string>	init_map_headers();
		std::string		get_response_field_name(enum e_resp_fields field);
		std::string 	generate_error_page_content(int code);


		// Response_headers
		std::string 	generate_status_line();
		std::string		formatted_header_response(enum e_resp_fields field);
		std::string		r_header_server();
		std::string		r_header_date();
		std::string		r_header_connection();
		std::string		r_header_content_length();
		std::string		r_header_content_type();
		std::string		r_header_location();
		std::string		get_mime_type(std::string extension);
		void			generate_response_header();

		// Response_class
		void		set_default_html_type_mime_charset();
		void		parse_type_mime_charset_cmd_result(std::string res);
		void		retrieve_type_mime_charset();
		void		check_if_method_allowed();
		int			is_actually_directory(std::string path);
		void		check_if_redir_301();
		void		fill_body_if_error();
		void		DELETE_create_body();
		void		DELETE_handle();
		void		GET_create_body();
		void		GET_handle();
		void		POST_create_body();
		void		POST_create_body_cgi();
		void		POST_handle();
		void		concatenate_response();
		void		generate();
};

#endif
