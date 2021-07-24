#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# include <iostream>
# include <sstream>
# include <fstream>
# include <string>
# include <netinet/ip.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <fcntl.h>
# include <unistd.h>
# include <cstdlib>
# include <ctime>
# include <map>
# include "color.hpp"
# include <vector>
// #include <pstream.h>
//
typedef int SOCKET;
# define MAX_RCV	4096
# define MAX_DATE	80
# define SUCCESS	0
# define FAILURE	-1

# include "utils.hpp"
# include "Config.hpp"
# include "RequestParser.class.hpp"
# include "Response.hpp"
# include "Client.hpp"
# include "Server.hpp"
# include "Exceptions.hpp"

#endif
