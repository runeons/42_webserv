
#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# include <iostream>
# include <sstream>
# include <fstream>
# include <string>
# include <netinet/ip.h>
# include <sys/socket.h>
# include <sys/select.h>
# include <arpa/inet.h>
# include <fcntl.h>
# include <unistd.h>
# include <cstdlib>
# include <ctime>
# include <map>
# include "color.hpp"
# include <vector>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/time.h>
// #include <pstream.h>
//
typedef int SOCKET;
# define MAX_RCV	4096
# define MAX_DATE	80
# define SUCCESS	0
# define FAILURE	-1

# include <Exceptions.hpp>
# include <0_Config.hpp>
# include <0_Location.hpp>
# include <ConfigParser.hpp>
# include <1_Server.hpp>
# include <2_Client.hpp>
# include <3_RequestParser.hpp>
# include <4_Response.hpp>
# include <5_Cgi.hpp>
# include <utils.hpp>

typedef std::map<std::string, std::string>::iterator	headers_iterator;
typedef std::vector<std::string>::iterator				v_string_iterator;

#endif
