# include "Client.hpp"

// Default constructor
Client::Client(void)
{
	std::cout << GREY << "Client creation..." << C_RES << std::endl;
	_socket = 0;
	_status_code = 0;
	_request = "";
	_full_path = "";
	_response = NULL;
	_request_parser = NULL;
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
	if (_response != NULL)
		delete _response;
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

void		Client::construct_full_path(void)
{
	// _full_path = ROOT_DIR + _request_parser.getResource();
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

void Client::read_resource(void)
{
	_full_path = "./html/forty-two";

	std::ifstream ifs(_full_path);
	std::ostringstream oss;

	if (!ifs)
	{
		std::cerr << RED << "Error (404) : file does'nt exist" <<  C_RES << std::endl;
		_status_code = 404;
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

void Client::generate_response(void)
{
	_response = new Response(_status_code, _page_content);
	_response->generate();
}

void Client::send_response(void)
{
	int	bytes_sent = 0;
	int len = _response->getResponse().length() + 1;

	char response_array[len];
	strcpy(response_array, _response->getResponse().c_str());
	try
	{
		bytes_sent = ::send(_socket, response_array, len, 0);
		if (bytes_sent == -1)
			throw Exceptions::SendFailure();
		std::cout << GREEN << "Response of size " << bytes_sent << " sent !" <<  C_RES << std::endl;
	}
	catch (Exceptions::SendFailure & e)
	{
		std::cerr << RED << e.what() <<  C_RES << std::endl;
	}
}

void Client::treat_client(void)
{
	std::cout << GREEN_B << "Treating client " << _socket << C_RES << std::endl;
	receive_request();
	check_request();
	read_resource();
	generate_response();
	send_response();

	std::cout <<  _response->getResponse() << std::endl;

	return ;
}
