# include "Client.hpp"

// Default constructor
Client::Client(void)
{
	std::cout << GREY << "Client creation..." << C_RES << std::endl;
	_socket = 0;
	_request = "";
	_full_path = "";
	_error_msg = create_map_msg();
	_error_body = create_map_body();
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

void		Client::generate_response_header(void)
{

	return;
}

void		Client::generate_error_body(int code)
{
	(void)code;
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
	return ;
}

std::map<int, std::string>	Client::create_map_msg()
{
	std::map<int, std::string> m;

	// m[100] = "Continue";
	// m[101] = "Switching Protocols";
	m[200] = "OK";
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
	m[404] = "Not Found";
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

std::map<int, std::string>	Client::create_map_body()
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
