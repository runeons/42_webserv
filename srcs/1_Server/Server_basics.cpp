
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

Server::Server(std::vector<Config> config_vec) : _config_vec(config_vec)
{
	std::cout << C_HIDDEN << "...Multi server creation..." << C_RES << std::endl;

	return ;
}

// Server::Server(const Config & config)
// {
// 	std::cout << C_HIDDEN << "...Server creation..." << C_RES << std::endl;
// 	// TO DO parse config
// 	_config = const_cast<Config *>(&config); // parametree avec le parsing
// 	_config->set__root_dir("./" + _config->get__root_dir());
// 	_address.sin_family = AF_INET;
// 	_address.sin_addr.s_addr = INADDR_ANY;
// 	try
// 	{
// 		if (inet_aton(_config->get__host().c_str(), &_address.sin_addr) <= 0)
// 			throw (Exceptions::ServerException("Server invalid address"));
// 	}
// 	catch (Exceptions::ServerException & e)
// 	{
// 		std::cerr << C_ERROR << e.what() <<  C_RES << std::endl;
// 	}
// 	_address.sin_port = htons(_config->get__port());
// 	_master_socket = 0;
// 	return ;
// }

// Copy constructor
Server::Server(const Server& src)
{
	std::cout << C_HIDDEN << "Server creation..." << C_RES << std::endl;
	*this = src;
	return;
}

// Destructor
Server::~Server(void)
{
	// delete _config;
	// TO DO delete all clients
	std::cout << C_HIDDEN << "...Server destruction..." << C_RES << std::endl;
	return;
}

// Assignation operator
Server &	Server::operator=(const Server& rhs)
{
	std::cout << C_HIDDEN << "Server Assignation operator called" << C_RES << std::endl;
	if (this != &rhs)
	{
		// TO DO
		;
		// _config = rhs.getConfig();
		// _master_socket = rhs.getSocket();
	}
	return (*this);
}
