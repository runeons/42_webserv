/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi_init_map.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantoni <tsantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 11:12:07 by tsantoni          #+#    #+#             */
/*   Updated: 2021/07/31 11:12:49 by tsantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <webserv.hpp>

std::map<std::string, std::string>	Cgi::init_map_env()
{
	std::map<std::string, std::string> m;

	// MUST (discord)
	m["REDIRECT_STATUS"] = "200";		// nécessaire si utilise php-cgi

	// MUST (RFC)
	m["GATEWAY_INTERFACE"] = "CGI/1.1";	// CGI/1.1
	m["QUERY_STRING"] = "";				// parametres
	m["REMOTE_ADDR"] = "127.0.0.1";				//
	m["REQUEST_METHOD"] = "GET";			// methode
	m["SCRIPT_NAME"] = "scripts/bonjour.php";				// ROOT-RELATIVE path to script (peut être un alias dans certains cas, par ex quand on utilise Apache)
	m["SERVER_NAME"] = "webserv";				//
	m["SERVER_PORT"] = "8000";				//
	m["SERVER_PROTOCOL"] = "HTTP/1.1";			//
	m["SERVER_SOFTWARE"] = "";			//

	// CONDITIONAL (RFC)
	// m["CONTENT_LENGTH"] = "";			// if no body, MUST NOT be set
	// m["CONTENT_TYPE"] = "";				// if no body, can be NULL

	// PROBABLY (RFC)
	// m["PATH_INFO"] = "uploads/to_upload";	// SCRIPT_FILENAME will not be available if PATH_INFO is not (=$SCRIPT_FILENAME in some examples) : contient le path réel du script à exécuter
	// m["PATH_TRANSLATED"] = "";			//
	// m["REMOTE_HOST"] = "";

	// PROBABLY NOT (RFC)
	// m["AUTH_TYPE"] = ""; 				//
	// m["REMOTE_IDENT"] = ""; 			//
	// m["REMOTE_USER"] = ""; 				//

	// MAYBE : discord example (fassani) mais pas php.net/manual
	// m["SCRIPT_FILENAME"] = "";			// ABSOLUTE path to script.php que je voudrais utiliser (path réel)
	// m["HTTP_ACCEPT-ENCODING"] = "";		//
	// m["HTTP_HOST"] = "";				//
	// m["HTTP_USER-AGENT"] = "";			//
	// m["REQUEST_URI"] = "";				//

	return m;
}

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
/*
	List RFC :

	"AUTH_TYPE"
	"CONTENT_LENGTH"
	"CONTENT_TYPE"
	"GATEWAY_INTERFACE"
	"PATH_INFO"
	"PATH_TRANSLATED"
	"QUERY_STRING"
	"REMOTE_ADDR"
	"REMOTE_HOST"
	"REMOTE_IDENT"
	"REMOTE_USER"
	"REQUEST_METHOD"
	"SCRIPT_NAME"
	"SERVER_NAME"
	"SERVER_PORT"
	"SERVER_PROTOCOL"
	"SERVER_SOFTWARE"
*/

// env REDIRECT_STATUS="200" GATEWAY_INTERFACE="CGI/1.1" QUERY_STRING="" REMOTE_ADDR="127.0.0.1" REQUEST_METHOD="GET" SCRIPT_NAME="scripts/bonjour.php" SERVER_NAME="webserv" SERVER_PORT="8000" SERVER_PROTOCOL="HTTP/1.1" SERVER_SOFTWARE="" ./scripts/bonjour.php
// m["CONTENT_LENGTH"] = "";			// if no body, MUST NOT be set
// m["CONTENT_TYPE"] = "";				// if no body, can be NULL
// m["PATH_INFO"] = "uploads/to_upload";