#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# include <iostream>
# include <string>
# include "color.hpp"
# include <netinet/ip.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <cstdlib>
# include <map>

typedef int SOCKET;
# define MAX_RCV 4096

# include "Config.hpp"
# include "Client.hpp"
# include "Server.hpp"
# include "Exceptions.hpp"

#endif
