#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# include <iostream>
# include <sstream>
# include <string>
# include "color.hpp"
# include <netinet/ip.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <cstdlib>
# include <ctime>
# include <map>

typedef int SOCKET;
# define MAX_RCV	4096
# define MAX_DATE	80
# define SUCCESS	0
# define FAILURE	-1

# include "Config.hpp"
# include "RequestParser.class.hpp"
# include "Client.hpp"
# include "Server.hpp"
# include "Exceptions.hpp"

#endif
