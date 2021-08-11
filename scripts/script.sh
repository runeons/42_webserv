#!/bin/bash

export REDIRECT_STATUS="200"
export GATEWAY_INTERFACE="CGI/1.1"
export REQUEST_METHOD="GET"
export SCRIPT_FILENAME="/Users/user/42_webserv/tester_42/ubuntu_cgi_tester"
export PATH_INFO="/Users/user/42_webserv/tester_42/ubuntu_cgi_tester"
export QUERY_STRING="say=Salut&to=Maman"

exec /usr/bin/php-cgi
