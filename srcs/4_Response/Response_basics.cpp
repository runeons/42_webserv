
# include <webserv.hpp>

// Parametric constructor
Response::Response(Config & config, Location & applied_location, int status_code, std::string page_content, std::string translated_path, RequestParser & request) : _config(config), _applied_location(applied_location), _request(request)
{
	std::cout << GREY << "Response creation..." << C_RES << std::endl;
	// from parameters
	_status_code = status_code;
	_page_content = page_content;
	_translated_path = translated_path;

	// init
	_type_mime = "";
	_charset = "";
	_response = "";
	_response_header = "";
	_response_body = "";
	_headers_response = init_map_headers();
	_error_msg = init_map_msg();
	_error_content = init_map_body();
	return ;
}

// Destructor
Response::~Response(void)
{
	std::cout << GREY << "Response destruction..." << C_RES << std::endl;
	return;
}

// Assignation operator
Response &	Response::operator=(const Response& rhs)
{
	std::cout << GREY << "Response Assignation operator called" << C_RES << std::endl;
	if (this != &rhs)
	{
		_status_code = rhs.getStatusCode();
		_page_content = rhs.getPageContent();
		_translated_path = rhs.getFullPath();
		_response = rhs.getResponse();
		_response_body = rhs.getResponseBody();
		_response_header = rhs.getResponseHeader();
		_headers_response = rhs.getHeadersResponse();
		_error_msg = rhs.getErrorMsg();
		_error_content = rhs.getErrorBody();
	}
	return (*this);
}

// getters and setters (non static attributes)
int Response::getStatusCode(void) const
{
	return (_status_code);
}

void Response::setStatusCode(const int status_code)
{
	_status_code = status_code;
	return ;
}

std::string Response::getFullPath(void) const
{
	return (_translated_path);
}

void Response::setFullPath(const std::string translated_path)
{
	_translated_path = translated_path;
	return ;
}

std::string Response::getResponse(void) const
{
	return (_response);
}

void Response::setResponse(const std::string response)
{
	_response = response;
	return ;
}

std::string Response::getResponseHeader(void) const
{
	return (_response_header);
}

void Response::setResponseHeader(const std::string response_header)
{
	_response_header = response_header;
	return ;
}

std::string Response::getResponseBody(void) const
{
	return (_response_body);
}

void Response::setResponseBody(const std::string response_body)
{
	_response_body = response_body;
	return ;
}

std::map<int, std::string> Response::getErrorMsg(void) const
{
	return (_error_msg);
}

void Response::setErrorMsg(const std::map<int, std::string> error_msg)
{
	_error_msg = error_msg;
	return ;
}

std::map<int, std::string> Response::getErrorBody(void) const
{
	return (_error_content);
}

void Response::setErrorBody(const std::map<int, std::string> error_body)
{
	_error_content = error_body;
	return ;
}

std::map<int, std::string> Response::getHeadersResponse(void) const
{
	return (_headers_response);
}

void Response::setHeadersResponse(const std::map<int, std::string> headers_response)
{
	_headers_response = headers_response;
	return ;
}

std::string Response::getPageContent(void) const
{
	return (_page_content);
}

void Response::setPageContent(const std::string page_content)
{
	_page_content = page_content;
	return ;
}

int Response::is_response_successful(void)
{
	if (_status_code == 200 || _status_code == 202 || _status_code == 204)
		return (1);
	return (0);
}
