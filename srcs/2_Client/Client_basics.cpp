
# include <webserv.hpp>

// Parametric constructor
Client::Client(Config & config) : _config(config)
{
	std::cout << C_HIDDEN << "...Client creation..." << C_RES << std::endl;

	_socket = 0;
	_status_code = 200;
	_bytes_read = 0;
	_request = "";
	_translated_path = "";
	_response = NULL;
	_request_parser = NULL;
	_page_content = "";
	_query_string = "";
	_applied_location = NULL;
	_remaining_bytes_to_recv = 0;
	_total_bytes_expected = 0;
	_remaining_bytes_to_send = 0;
	_total_bytes_to_send = 0;
	memset(_chunk, 0, MAX_RCV);	//clear the variable
	return ;
}

// Destructor
Client::~Client(void)
{
	std::cout << C_HIDDEN << "...Client destruction..." << C_RES << std::endl;
	if (_response != NULL)
		delete _response;
	if (_request_parser != NULL)
		delete _request_parser;
	return;
}

// Assignation operator
Client &	Client::operator=(const Client& rhs)
{
	std::cout << C_HIDDEN << "Client Assignation operator called" << C_RES << std::endl;
	if (this != &rhs)
	{
		_socket = rhs.get__socket();
	}
	return (*this);
}

// getters and setters (non static attributes)
SOCKET Client::get__socket(void) const
{
	return (_socket);
}

void Client::set__socket(const SOCKET client_socket)
{
	_socket = client_socket;
	return ;
}

int Client::get__remaining_bytes_to_recv(void) const
{
	return (_remaining_bytes_to_recv);
}

void Client::set__remaining_bytes_to_recv(const int bytes)
{
	_remaining_bytes_to_recv = bytes;
	return ;
}

int Client::get__total_bytes_expected(void) const
{
	return (_total_bytes_expected);
}

void Client::set__total_bytes_expected(const int bytes)
{
	_total_bytes_expected = bytes;
	return ;
}

int Client::get__remaining_bytes_to_send(void) const
{
	return (_remaining_bytes_to_send);
}

void Client::set__remaining_bytes_to_send(const int bytes)
{
	_remaining_bytes_to_send = bytes;
	return ;
}

int Client::get__total_bytes_to_send(void) const
{
	return (_total_bytes_to_send);
}

void Client::set__total_bytes_to_send(const int bytes)
{
	_total_bytes_to_send = bytes;
	return ;
}

int Client::get__status_code(void) const
{
	return (_status_code);
}

void Client::set__status_code(const int code)
{
	_status_code = code;
	return ;
}

std::string Client::get__request(void) const
{
	return (_request);
}

void Client::set__request(const std::string request)
{
	_request = request;
	return ;
}

Location * Client::get__applied_location(void) const
{
	return (_applied_location);
}

void Client::set__applied_location(Location * applied_location)
{
	_applied_location = applied_location;
	return ;
}

Config & Client::get__config(void) const
{
	return (_config);
}

void Client::set__config(const Config & config)
{
	_config = config;
	return ;
}

int Client::is_response_successful(void)
{
	if (_status_code == 200 || _status_code == 202 || _status_code == 204)
		return (1);
	return (0);
}
