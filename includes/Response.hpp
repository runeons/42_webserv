#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include "webserv.hpp"

# define SERVER_NAME "webserv"

typedef enum		e_resp_fields
{
	R_DATE,
	R_SERVER,
	R_CONNECTION,
	R_CONTENT_LENGTH,
	R_CONTENT_TYPE
}					t_resp_fields;

class Response
{
	private:
		Response();
		int							_status_code;
		std::string					_page_content;
		std::string					_full_path;
		std::string					_response;
		std::string					_response_header;
		std::string					_response_body;
		std::string					_response_bin;
		std::string					_response_header_bin;
		std::string					_response_body_bin;
		std::map<int, std::string>	_headers_response;
		std::map<int, std::string>	_error_msg;
		std::map<int, std::string>	_error_content;

	public:
		// Response_basics
		Response(int status_code, std::string page_content);
		Response(const Response & src);
		virtual ~Response();

		int							getStatusCode(void) const;
		void						setStatusCode(const int status_code);
		std::string					getFullPath(void) const;
		void						setFullPath(const std::string full_path);
		std::string					getResponse(void) const;
		void						setResponse(const std::string response);
		std::string					getResponseHeader(void) const;
		void						setResponseHeader(const std::string response_header);
		std::string					getResponseBody(void) const;
		void						setResponseBody(const std::string response_body);
		std::string					getResponseBin(void) const;
		void						setResponseBin(const std::string response_bin);
		std::string					getResponseHeaderBin(void) const;
		void						setResponseHeaderBin(const std::string response_header_bin);
		std::string					getResponseBodyBin(void) const;
		void						setResponseBodyBin(const std::string response_body_bin);
		std::map<int, std::string>	getErrorMsg(void) const;
		void						setErrorMsg(const std::map<int, std::string> error_msg);
		std::map<int, std::string>	getErrorBody(void) const;
		void						setErrorBody(const std::map<int, std::string> error_body);
		std::map<int, std::string>	getHeadersResponse(void) const;
		void						setHeadersResponse(const std::map<int, std::string> headers_response);
		std::string					getPageContent(void) const;
		void						setPageContent(const std::string page_content);

		Response					&operator=(const Response & src);

		// Response_init_maps
		std::map<int, std::string>	init_map_msg();
		std::map<int, std::string>	init_map_body();
		std::map<int, std::string>	init_map_headers();
		std::string		get_response_field_name(enum e_resp_fields field);


		// Response_headers
		std::string 	generate_status_line();
		std::string		formatted_header_response(enum e_resp_fields field);
		std::string		r_header_server();
		std::string		r_header_date();
		std::string		r_header_connection();
		std::string		r_header_content_length();
		std::string		r_header_content_type();
		void			generate_response_header();

		// Response_class
		void	generate_error_content();
		void	GET_create_body();
		void	concatenate_response();
		void	generate();
};

#endif
