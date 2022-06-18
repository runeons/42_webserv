
# include <webserv.hpp>

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

	std::cout << C_HIDDEN << "...Server destruction..." << C_RES << std::endl;
	return;
}
