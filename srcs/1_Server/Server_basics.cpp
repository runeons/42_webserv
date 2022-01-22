
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
	_max_fd = 0;
	return ;
}

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
	// std::cout << C_HIDDEN << "...in Server destruction..." << C_RES << std::endl;
	// std::map<int, Client *>::iterator it;
	// for (it = _clients_map.begin(); it != _clients_map.end(); it++) // delete client pour chaque socket existante
	// {
		// std::cout << C_ERROR << "_clients_map socket " << it->first << " @ : " << it->second << " ===> " << it->second->get__socket() << C_RES << std::endl;
		// delete it->second;
	// }
	// TO DO delete all clients
	std::cout << C_HIDDEN << "...Server destruction..." << C_RES << std::endl;
	return;
}
