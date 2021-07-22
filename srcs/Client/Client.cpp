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
	_response = "";
	_response_bin = "";
	_response_body = "";
	_response_body_bin = "";
	_response_header = "";
	_response_header_bin = "";
	_page_content = "";
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

std::string itos(int nb)
{
	std::stringstream ss;

	ss << nb;
	return ss.str();
}

std::string Client::generate_status_line(void)
{
	std::map<int, std::string>::iterator it_msg = _error_msg.find(_status_code);

	// sl = "HTTP/" + _request_parser->get__http_version() + PAT_SP + itos(_status_code) + PAT_SP + it_msg->second + PAT_CRLF;
	return ("HTTP/1.1" + _request_parser->get__http_version() + PAT_SP + itos(_status_code) + PAT_SP + it_msg->second + PAT_CRLF);
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
	_headers_response[R_CONNECTION] = "close"; // à vérifier
	return (formatted_header_response(R_CONNECTION));
}

std::string		Client::r_header_content_length()
{
	if (_response_body.length())
		_headers_response[R_CONTENT_LENGTH] = itos(_response_body.length());
	else
		_headers_response[R_CONTENT_LENGTH] = "None";
	return (formatted_header_response(R_CONTENT_LENGTH));
}

std::string		Client::r_header_content_type()
{
	_headers_response[R_CONTENT_TYPE] = "text/html; charset=utf-8";
	return (formatted_header_response(R_CONTENT_TYPE));
}

void		Client::generate_response_header(void)
{
	_response_header = generate_status_line();
	_response_header += r_header_server();
	_response_header += r_header_date();
	_response_header += r_header_connection();
	_response_header += r_header_content_length();
	_response_header += r_header_content_type();

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
	// _full_path = ROOT_DIR + _request_parser.getResource;
	return;
}

void Client::receive_request(void)
{
	char	buffer[MAX_RCV];
	int		bytes_read = 0;

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

std::string int_to_binary(int n)
{
    std::string r;

    while (n != 0)
	{
        r += ( n % 2 == 0 ? "0" : "1" );
        n /= 2;
    }
	reverse(r.begin(), r.end());
	while (r.length() < 8)
		r = "0" + r;
    return r;
}

std::string string_to_binary(std::string s)
{
	std::ostringstream oss;

	if (!oss)
		std::cerr << RED << "Error oss : can't open ofstream" <<  C_RES << std::endl; // EXCEPTION A CREER
	for (size_t i = 0; i < s.length(); ++i)
	{
		oss << int_to_binary(s[i]);

		// if (i % 6 == 0 && i != 0) // controle le format d'impression
			// oss << std::endl;
	}
	return oss.str();

}

std::string binary_to_string(std::string s)
{
	std::string ret;
	std::ostringstream oss;
	char	parsed = 0;
	int		j = 0;

	if (!oss)
		std::cerr << RED << "Error oss : can't open ofstream" <<  C_RES << std::endl; // EXCEPTION A CREER
	for (size_t i = 0; i < s.length(); ++i)
	{
		parsed = 0;
		j = 0;
		for (int j = 0; j < 8; j++)
		{
			if (s[j] == '1') {
				parsed |= 1 << (7 - j);
			}
		}
		oss << parsed;
		s.erase(0, 8);
		i = 0;
	}
	return oss.str();
}


void Client::read_resource(void)
{
	_full_path = "./html/forty-two";

	std::ifstream ifs(_full_path);
	std::ostringstream oss;

	if (!ifs)
	{
		std::cerr << RED << "Error (404) : file does'nt exist" <<  C_RES << std::endl;
		_status_code = 404;
		_page_content = _error_body[404];
	}
	else if (!oss) // EXCEPTION A CREER
	{
		std::cerr << RED << "Error : can't open ofstream" <<  C_RES << std::endl;
		_status_code = 500; // quel status_code ?
	}
	else
	{
		std::cerr << GREEN_B << "OK : file found" <<  C_RES << std::endl;
		_status_code = 200;
		oss << ifs.rdbuf();
		_page_content = oss.str();
	}
	if (ifs)
		ifs.close();

	return ;
}

void	Client::get_create_body(void)
{
	_response_body = _page_content;
	_response_body_bin = string_to_binary(_response_body);
	// std::cout << "_response_body_bin : " << _response_body_bin << std::endl;
	// std::cout << RED_B << " binary_to_string(_response_body_bin) : " << binary_to_string(_response_body_bin) << std::endl << C_RES;

}

void	Client::generate_response_bin()
{
	_response = _response_header + PAT_CRLF + _response_body;
	_response_bin = string_to_binary(_response);

}


void Client::treat_client(void)
{
	std::cout << GREEN_B << "Treating client " << _socket << C_RES << std::endl;
	receive_request();
	check_request();
	read_resource();
	get_create_body(); // depending on METHOD
	generate_response_header();
	generate_response_bin();

	// for GET
	std::cout << _response << std::endl;

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
	m[302] = "Found";
	m[303] = "See Other";
	m[304] = "Not Modified";
	m[305] = "Use Proxy";
	m[307] = "Temporary Redirect";
	m[400] = "Bad Request";
	m[401] = "Unauthorized";
	m[402] = "Payment Required";
	m[403] = "Forbidden";
	m[404] = "Not Found";
	m[405] = "Method Not Allowed";
	m[406] = "Not Acceptable";
	m[407] = "Proxy Authentication Required";
	m[408] = "Request Timeout";
	m[409] = "Conflict";
	m[410] = "Gone";
	m[411] = "Length Required";
	m[412] = "Precondition Failed";
	m[413] = "Payload Too Large";
	m[414] = "URI Too Long";
	m[415] = "Unsupported Media Type";
	m[416] = "Range Not Satisfiable";
	m[417] = "Expectation Failed";
	m[418] = "I'm a teapot";
	m[426] = "Upgrade Required";
	m[500] = "Internal Server Error";
	m[501] = "Not Implemented";
	m[502] = "Bad Gateway";
	m[503] = "Service Unavailable";
	m[504] = "Gateway Timeout";
	m[505] = "HTTP Version Not Supported";

	return m;
}

std::map<int, std::string>	Client::init_map_body()
{
	std::map<int, std::string> m;

	m[404] = "<html><body><center><h1>Error 404: Not found</h1></center><p>Head back to <a href=\"/\">home page</a>.</p></body></html>";

	return m;
}
