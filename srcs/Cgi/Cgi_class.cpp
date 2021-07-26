# include "Cgi.hpp"

std::map<std::string, std::string>	Cgi::init_map_env()
{
	std::map<std::string, std::string> m;

	// très important
	m["REDIRECT_STATUS"] = "200";		// nécessaire si utilise php-cgi
	m["GATEWAY_INTERFACE"] = "CGI/1.1";	// CGI/1.1
	m["REQUEST_METHOD"] = "";			// methode
	m["SCRIPT_FILENAME"] = "";			// ABSOLUTE path to script.php que je voudrais utiliser (path réel)
	m["SCRIPT_NAME"] = "";				// ROOT-RELATIVE path to script (peut être un alias dans certains cas, par ex quand on utilise Apache)
	m["PATH_INFO"] = "";				// SCRIPT_FILENAME will not be available if PATH_INFO is not (=$SCRIPT_FILENAME in some examples) : contient le path réel du script à exécuter
	m["QUERY_STRING"] = "";				// parametres

	m["CONTENT_LENGTH"] = "";			//
	m["CONTENT_TYPE"] = "";				//
	m["PATH_TRANSLATED"] = "";			//
	m["REMOTE_ADDR"] = "";				//
	m["SERVER_NAME"] = "";				//
	m["SERVER_PORT"] = "";				//
	m["SERVER_PROTOCOL"] = "";			//
	m["SERVER_SOFTWARE"] = "";			//

	// source : php.net/manual mais pas example discord

	m["AUTH_TYPE"] = ""; 				//
	m["REMOTE_HOST"] = ""; 				//
	m["REMOTE_IDENT"] = ""; 			//
	m["REMOTE_USER"] = ""; 				//

	// source : discord example (fassani) mais pas php.net/manual

	m["HTTP_ACCEPT-ENCODING"] = "";		//
	m["HTTP_HOST"] = "";				//
	m["HTTP_USER-AGENT"] = "";			//
	m["REMOTE_ADDR"] = "";				//
	m["REQUEST_URI"] = "";				//

	return m;
}

/*
env
REDIRECT_STATUS="200"
GATEWAY_INTERFACE="CGI/1.1"
REQUEST_METHOD="GET"
SCRIPT_FILENAME="/Users/user/42_webserv/tester_42/ubuntu_cgi_tester"
PATH_INFO="/Users/user/42_webserv/tester_42/ubuntu_cgi_tester"
QUERY_STRING="say=Salut&to=Maman"
./ubuntu_cgi_tester

env
CONTENT_LENGTH="0"
CONTENT_TYPE="text/plain"
GATEWAY_INTERFACE="CGI/1.1"
HTTP_ACCEPT-ENCODING="gzip"
HTTP_HOST="localhost"
HTTP_USER-AGENT="Go-http-client/1.1"
PATH_INFO="/ubuntu_cgi_tester"
PATH_TRANSLATED="/ubuntu_cgi_tester"
REDIRECT_STATUS="200"
REMOTE_ADDR="127.0.0.1"
REQUEST_METHOD="GET"
REQUEST_URI="/directory/youpi.bla"
SCRIPT_FILENAME="/Users/user/42_webserv/tester_42/ubuntu_cgi_tester"
SCRIPT_NAME="ubuntu_cgi_tester"
SERVER_NAME="webserv"
SERVER_PORT="8000"
SERVER_PROTOCOL="HTTP/1.1"
SERVER_SOFTWARE="WebServ/1.0"
./ubuntu_cgi_tester

env REDIRECT_STATUS="200" GATEWAY_INTERFACE="CGI/1.1" REQUEST_METHOD="GET" SCRIPT_FILENAME="/Users/user/42_webserv/tester_42/ubuntu_cgi_tester" PATH_INFO="/Users/user/42_webserv/tester_42/ubuntu_cgi_tester" QUERY_STRING="say=Salut&to=Maman" ./ubuntu_cgi_tester
env CONTENT_LENGTH="0" CONTENT_TYPE="text/plain" GATEWAY_INTERFACE="CGI/1.1" HTTP_ACCEPT-ENCODING="gzip" HTTP_HOST="localhost" HTTP_USER-AGENT="Go-http-client/1.1" PATH_INFO="/ubuntu_cgi_tester" PATH_TRANSLATED="/ubuntu_cgi_tester" REDIRECT_STATUS="200" REMOTE_ADDR="127.0.0.1" REQUEST_METHOD="GET" REQUEST_URI="/directory/youpi.bla" SCRIPT_FILENAME="/Users/user/42_webserv/tester_42/ubuntu_cgi_tester" SCRIPT_NAME="ubuntu_cgi_tester" SERVER_NAME="webserv" SERVER_PORT="8000" SERVER_PROTOCOL="HTTP/1.1" SERVER_SOFTWARE="WebServ/1.0" ./ubuntu_cgi_tester
*/
/*

	Example discord :

	CONTENT_LENGTH=0
	CONTENT_TYPE=text/plain
	GATEWAY_INTERFACE=CGI/1.1
	HTTP_ACCEPT-ENCODING=gzip
	HTTP_HOST=localhost
	HTTP_USER-AGENT=Go-http-client/1.1
	PATH_INFO=/directory/youpi.bla
	PATH_TRANSLATED=/YoupiBanane/youpi.bla
	REDIRECT_STATUS=200
	REMOTE_ADDR=127.0.0.1
	REQUEST_METHOD=GET
	REQUEST_URI=/directory/youpi.bla
	SCRIPT_FILENAME=/home/fouad/Bureau/webserv/YoupiBanane/youpi.bla
	SCRIPT_NAME=/home/fouad/Bureau/webserv/ubuntu_cgi_tester
	SERVER_NAME=42WebServer
	SERVER_PORT=8080
	SERVER_PROTOCOL=HTTP/1.1
	SERVER_SOFTWARE=WebServ/1.0
*/