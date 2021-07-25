# include "Server.hpp"


/*
struct sockaddr_in {
    sa_family_t    sin_family; // famille d'adresses : AF_INET
    uint16_t       sin_port;   // port dans l'ordre d'octets réseau
    struct in_addr sin_addr;   // adresse Internet, adresse IP de l'hôte
};

// Adresse Internet
struct in_addr {
    uint32_t       s_addr;     // Adresse dans l'ordre d'octets réseau
};
*/


// Default constructor
Server::Server(void)
{
	std::cout << GREY << "Server creation..." << C_RES << std::endl;
	_config = new Config;
	_client = new Client;
	_address.sin_family = AF_INET;
	_address.sin_addr.s_addr = INADDR_ANY;
	try
	{
		if (inet_aton("127.0.0.1", &_address.sin_addr) <= 0)
			throw Exceptions::InvalidAddress();
		std::cout << GREEN << "Address set !" <<  C_RES << std::endl;
	}
	catch (Exceptions::InvalidAddress & e)
	{
		std::cerr << RED << e.what() <<  C_RES << std::endl;
	}
	_address.sin_port = htons(_config->getPort());
	_socket = 0;
	return ;
}

// Copy constructor
Server::Server(const Server& src)
{
	std::cout << GREY << "Server creation..." << C_RES << std::endl;
	*this = src;
	return;
}

// Destructor
Server::~Server(void)
{
	delete _config;
	delete _client;
	std::cout << GREY << "Server destruction..." << C_RES << std::endl;
	return;
}

// Assignation operator
Server &	Server::operator=(const Server& rhs)
{
	std::cout << GREY << "Server Assignation operator called" << C_RES << std::endl;
	if (this != &rhs)
	{
		_config = rhs.getConfig();
		_socket = rhs.getSocket();
	}
	return (*this);
}

// getters and setters (non static attributes)
Config * Server::getConfig(void) const
{
	return (_config);
}

void Server::setConfig(Config * config)
{
	_config = config;
	return ;
}

Client * Server::getClient(void) const
{
	return (_client);
}

void Server::setClient(Client * client)
{
	_client = client;
	return ;
}

SOCKET Server::getSocket(void) const
{
	return (_socket);
}

void Server::setSocket(const SOCKET server_socket)
{
	_socket = server_socket;
	return ;
}

void Server::listen(void)
{
	socklen_t addrlen = sizeof(_address);

	if (::listen(_socket, 50) == -1)
		throw Exceptions::ServerListen();
	std::cout << GREEN << "Server ready to listen !" <<  C_RES << std::endl;
	while (1)
	{
		_client->setSocket(::accept(_socket, reinterpret_cast<struct sockaddr *>(&_address), reinterpret_cast<socklen_t *>(&addrlen)));
		// accept() ne renvoie pas d'exception car renvoie -1 en continu
		if (_client->getSocket() >= 0)
		{
			std::cout << GREEN_B << "Connexion received from " << _client->getSocket() << C_RES << std::endl;
			_client->treat_client();
			// break ;
		}
	}
	return ;
}

void Server::print_config(void)
{
	std::cout	<< ORANGE
				<< "[Host : " <<  _config->getHost() << "] "
				<< "[Port : " <<  _config->getPort() << "] "
				<< "[Dir  : " <<  _config->getRootDir() << "]"
				<< C_RES << std::endl;
	return ;
}

void		Server::create_server_socket()
{
	int option = 1;

	_socket = ::socket(AF_INET, SOCK_STREAM, 0);
	::setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
	// _socket = -1;
	if (_socket == -1)
		throw Exceptions::ServerSocket();
	std::cout << GREEN << "Server socket created !" <<  C_RES << std::endl;
}

void		Server::bind_address_and_port()
{
	if (::bind(_socket, reinterpret_cast<const struct sockaddr *>(&_address), sizeof(_address)) == -1)
	{
		perror("bind");
		throw Exceptions::BindServer();
	}
	std::cout << GREEN << "Address and port bound !" <<  C_RES << std::endl;
}

void		Server::stop_server()
{
	std::cerr << GREY << "Server shut down" <<  C_RES << std::endl;
	close(_socket); // pas besoin de protéger le close parce qu'on va quitter le programme
}

int		Server::launch(void)
{
	try
	{
		this->print_config();
		this->create_server_socket();
		this->bind_address_and_port();
		while (1)
			this->listen();
	}
	catch (std::exception & e)
	{
		std::cerr << RED << e.what() <<  C_RES << std::endl;
		this->stop_server();
		return (1);
	}
	return (0);
}