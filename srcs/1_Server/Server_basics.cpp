
# include <webserv.hpp>


/*
	struct sockaddr_in {
		sa_family_t	sin_family; // famille d'adresses : AF_INET
		uint16_t	   sin_port;   // port dans l'ordre d'octets réseau
		struct in_addr sin_addr;   // adresse Internet, adresse IP de l'hôte
	};

	// Adresse Internet
	struct in_addr {
		uint32_t	   s_addr;	 // Adresse dans l'ordre d'octets réseau
	};
*/


// Default constructor
Server::Server(void)
{
	std::cout << GREY << "Server creation..." << C_RES << std::endl;
	// TO DO parse config
	_config = new Config; // parametree avec le parsing
	// _client = new Client(*_config); // dans lequel j'envoie Config
	// _client = NULL;
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
	_address.sin_port = htons(_config->get__port());
	_master_socket = 0;
	return ;
}

Server::Server(const Config & config)
{
	std::cout << GREY << "Server creation..." << C_RES << std::endl;
	// TO DO parse config
	_config = const_cast<Config *>(&config); // parametree avec le parsing
	_config->set__root_dir("./" + _config->get__root_dir());
	_client = new Client(*_config); // dans lequel j'envoie Config
	// _client = NULL;
	_address.sin_family = AF_INET;
	_address.sin_addr.s_addr = INADDR_ANY;
	try
	{
		if (inet_aton(_config->get__host().c_str(), &_address.sin_addr) <= 0)
			throw Exceptions::InvalidAddress();
		std::cout << GREEN << "Address set !" <<  C_RES << std::endl;
	}
	catch (Exceptions::InvalidAddress & e)
	{
		std::cerr << RED << e.what() <<  C_RES << std::endl;
	}
	_address.sin_port = htons(_config->get__port());
	_master_socket = 0;
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
	if (_client)
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
		_master_socket = rhs.getSocket();
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
//
// Client * Server::getClient(void) const
// {
// 	return (_client);
// }
//
// void Server::setClient(Client * client)
// {
// 	_client = client;
// 	return ;
// }

SOCKET Server::getSocket(void) const
{
	return (_master_socket);
}

void Server::setSocket(const SOCKET server_socket)
{
	_master_socket = server_socket;
	return ;
}
