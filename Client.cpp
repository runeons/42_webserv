# include "Client.hpp"

// Default constructor
Client::Client(void)
{
	std::cout << GREY << "Client creation..." << C_RES << std::endl;
	_socket = 0;
	_request = "";
	_method = "";
	_ressource = "";
	_version = "";
	_full_path = "";
	_error_msg = create_map_error_msg();
	_error_body = create_map_error_body();
	return ;
}

std::map<int, std::string>	Client::create_map_error_msg()
{
	std::map<int, std::string> m;

	m[200] = "OK";
	m[404] = "OK";
	return m;
}

std::map<int, std::string>	Client::create_map_error_body()
{
	std::map<int, std::string> m;

	m[200] = "OK";
	m[404] = "OK";
	return m;
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

void Client::treat_client(void)
{
	std::cout << GREEN_B << "Treating client " << _socket << C_RES << std::endl;
	receive_request();
	check_request();
	return ;
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
		std::cout << _request << std::endl;
	}
	catch (Exceptions::RecvFailure & e)
	{
		std::cerr << RED << e.what() <<  C_RES << std::endl;
	}

	return ;
}

void Client::check_request(void)
{
	std::cout << GREY << "check_request called" << C_RES << std::endl;
	size_t	pos = _request.find("\r\n");
	std::string first_line = _request.substr(0, pos);
	std::cout << first_line << std::endl;

	std::string sep = " ";
	int i = 3;
	while (i--)
	{
		pos = first_line.find(" ");
		if (i == 2)
			_method = first_line.substr(0, pos);
		else if (i == 1)
			_ressource = first_line.substr(0, pos);
		else
			_version = first_line.substr(0, pos);
		first_line.erase(0, pos + sep.length());
	}
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
	_full_path = "/server_root" + _ressource;
	return;
}
