# include "Client.hpp"

// Default constructor
Client::Client(void)
{
	std::cout << GREY << "Client creation..." << C_RES << std::endl;
	_socket = 0;
	_status_code = 0;
	_request = "";
	_full_path = "";
	_error_msg = init_map_msg();
	_error_body = init_map_body();
	_headers_response = init_map_headers();
	_request_parser = NULL;
	return ;
}

// Copy constructor
Client::Client(const Client& src)
{
	std::cout << GREY << "Client creation..." << C_RES << std::endl;
	*this = src;
	return;
}

// Destructor
Client::~Client(void)
{
	std::cout << GREY << "Client destruction..." << C_RES << std::endl;
	if (_request_parser != NULL)
		delete _request_parser;
	return;
}

// Assignation operator
Client &	Client::operator=(const Client& rhs)
{
	std::cout << GREY << "Client Assignation operator called" << C_RES << std::endl;
	if (this != &rhs)
	{
		_socket = rhs.getSocket();
	}
	return (*this);
}

// getters and setters (non static attributes)
SOCKET Client::getSocket(void) const
{
	return (_socket);
}

void Client::setSocket(const SOCKET client_socket)
{
	_socket = client_socket;
	return ;
}

std::string Client::getRequest(void) const
{
	return (_request);
}

void Client::setRequest(const std::string request)
{
	_request = request;
	return ;
}

// version SP code SP msg CRLF

std::string itos(int nb)
{
	std::stringstream ss;

	ss << nb;
	return ss.str();
}

std::string Client::generate_status_line(void)
{
	std::string sl;
	_status_code = 200;

	std::map<int, std::string>::iterator it_msg = _error_msg.find(_status_code);

	// sl = "HTTP/" + _request_parser->get__http_version() + PAT_SP + itos(_status_code) + PAT_SP + it_msg->second;
	sl = "HTTP/1.1" + _request_parser->get__http_version() + PAT_SP + itos(_status_code) + PAT_SP + it_msg->second + PAT_CRLF;
	std::cout << "status_line : " << sl << std::endl;

	return sl;
}

std::string		Client::formatted_header_response(enum e_resp_fields field)
{
	return (get_response_field_name(field) + PAT_DDOT + PAT_SP + _headers_response[field] + PAT_CRLF);
}

std::string		Client::r_header_server()
{
	_headers_response[R_SERVER] = SERVER_NAME;
	return (formatted_header_response(R_SERVER));
}

//Sun, 06 Nov 1994 08:49:37 GMT
std::string		Client::r_header_date()
{
	time_t		rawtime;
	struct tm	*timeinfo;
	char		buffer[MAX_DATE];

	time(&rawtime);
	timeinfo = gmtime(&rawtime);
	strftime(buffer, MAX_DATE, "%a, %d %h %G %X GMT", timeinfo);
	_headers_response[R_DATE] = buffer;
	return (formatted_header_response(R_DATE));
}

std::string		Client::r_header_connection()
{
	_headers_response[R_CONNECTION] = "";
	return (formatted_header_response(R_CONNECTION));
}

std::string		Client::r_header_content_length()
{
	_headers_response[R_CONTENT_LENGTH] = "";
	return (formatted_header_response(R_CONTENT_LENGTH));
}

std::string		Client::r_header_content_type()
{
	_headers_response[R_CONTENT_TYPE] = "";
	return (formatted_header_response(R_CONTENT_TYPE));
}

void		Client::generate_response_header(void)
{
	generate_status_line();
	std::cout << "server()		: " << r_header_server() << std::endl;
	std::cout << "date()			: " << r_header_date() << std::endl;
	std::cout << "connection()		: " << r_header_connection() << std::endl;
	std::cout << "content_length()	: " << r_header_content_length() << std::endl;
	std::cout << "content_type()	: " << r_header_content_type() << std::endl;

	return;
}

std::string		Client::get_response_field_name(enum e_resp_fields field)
{
	switch (field) {
		case R_DATE				: return (std::string("Date"));
		case R_SERVER			: return (std::string("Server"));
		case R_CONNECTION		: return (std::string("Connection"));
		case R_CONTENT_LENGTH	: return (std::string("Content-Length"));
		case R_CONTENT_TYPE		: return (std::string("Content-Type"));
		default					: return (std::string("None"));
	}
}

std::map<int, std::string>	Client::init_map_headers()
{
	std::map<int, std::string> m;

	m[R_DATE] = "";
	m[R_SERVER] = "";
	m[R_CONNECTION] = "";
	m[R_CONTENT_LENGTH] = "";
	m[R_CONTENT_TYPE] = "";
	return m;
}

void		Client::generate_error_body(void)
{

	return;
}

void		Client::construct_full_path(void)
{
	// _full_path = "/server_root" + _request_parser.getResource;
	return;
}

void Client::receive_request(void)
{
	char	buffer[MAX_RCV];
	int		bytes_read = 0;

	std::cout << GREY << "receive_request called" << C_RES << std::endl;
	try
	{
		bytes_read = ::recv(_socket, buffer, MAX_RCV - 1, 0);
		if (bytes_read == -1)
			throw Exceptions::RecvFailure();
		std::cout << GREEN << "Request of size " << bytes_read << " received !" <<  C_RES << std::endl;
		buffer[bytes_read] = '\0';
		_request.assign(buffer, bytes_read);
	}
	catch (Exceptions::RecvFailure & e)
	{
		std::cerr << RED << e.what() <<  C_RES << std::endl;
	}

	return ;
}

void Client::check_request(void)
{
	_request_parser = new RequestParser(_request); // create parser request
	_request_parser->print_request_info();
	return ;
}

void Client::treat_client(void)
{
	std::cout << GREEN_B << "Treating client " << _socket << C_RES << std::endl;
	receive_request();
	check_request();
	generate_response_header();
	return ;
}

std::map<int, std::string>	Client::init_map_msg()
{
	std::map<int, std::string> m;

	m[100] = "Continue";
	m[101] = "Switching Protocols";
	m[200] = "OK";
	m[201] = "Created";
	m[202] = "Accepted";
	m[203] = "Non-Authoritative Information";
	m[204] = "No Content";
	m[205] = "Reset Content";
	m[206] = "Partial Content";
	m[300] = "Multiple Choices";
	m[301] = "Moved Permanently";
	m[302] = "Moved Temporarily";
	m[303] = "See Other";
	m[304] = "Not Modified";
	m[305] = "Use Proxy";
	m[400] = "Bad Request";
	m[401] = "Unauthorized";
	m[402] = "Payment Required";
	m[403] = "Forbidden";
	m[404] = "Not Found";
	m[405] = "Method Not Allowed";
	m[406] = "None Acceptable";
	m[407] = "Proxy Authentication Required";
	m[408] = "Request Timeout";
	m[409] = "Conflict";
	m[410] = "Gone";
	m[411] = "Length Required";
	m[412] = "Unless True";
	m[500] = "Internal Server Error";
	m[501] = "Not Implemented";
	m[502] = "Bad Gateway";
	m[503] = "Service Unavailable";
	m[504] = "Gateway Timeout";

	return m;
}

std::map<int, std::string>	Client::init_map_body()
{
	std::map<int, std::string> m;

	// m[100] = "Continue";
	// m[101] = "Switching Protocols";
	// m[200] = "OK";
	// m[201] = "Created";
	// m[202] = "Accepted";
	// m[203] = "Non-Authoritative Information";
	// m[204] = "No Content";
	// m[205] = "Reset Content";
	// m[206] = "Partial Content";
	// m[300] = "Multiple Choices";
	// m[301] = "Moved Permanently";
	// m[302] = "Moved Temporarily";
	// m[303] = "See Other";
	// m[304] = "Not Modified";
	// m[305] = "Use Proxy";
	// m[400] = "Bad Request";
	// m[401] = "Unauthorized";
	// m[402] = "Payment Required";
	// m[403] = "Forbidden";
	m[404] = "<html><body><center><h1>Error 404: Not found</h1></center><p>Head back to <a href=\"/\">home page</a>.</p></body></html>";
	// m[405] = "Method Not Allowed";
	// m[406] = "None Acceptable";
	// m[407] = "Proxy Authentication Required";
	// m[408] = "Request Timeout";
	// m[409] = "Conflict";
	// m[410] = "Gone";
	// m[411] = "Length Required";
	// m[412] = "Unless True";
	// m[500] = "Internal Server Error";
	// m[501] = "Not Implemented";
	// m[502] = "Bad Gateway";
	// m[503] = "Service Unavailable";
	// m[504] = "Gateway Timeout";

	return m;
}
