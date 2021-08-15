# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    tester.sh                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/25 13:28:04 by tharchen          #+#    #+#              #
#    Updated: 2021/08/15 13:40:37 by tharchen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/usr/bin/env zsh

WIDTH_RET=30
WIDTH_RET_TITLE=$((WIDTH_RET + 4))

ERROR_5="        Couldn't resolve proxy"
ERROR_6="         Couldn't resolve host"
ERROR_7="     Failed to connect to host"
ERROR_8="            Weird server reply"
ERROR_UNKNOWN="                 Unknown error"

URL=127.0.0.1
PORT_WEBSERV=8000
PORT_NGINX=8080
RQST_SENDER=/usr/bin/nc

WEBSERV_ROOT=/Users/tharchen/Prog/42/projects/circle_6/webserv/draft/html
NGINX_ROOT=/usr/local/Cellar/nginx/1.21.1/html/


PATTERN_BORDER="═════════════════════════════════════════════════════════════════════════════════════════════════════════"

# curl -Il $URL:$PORT_NGINX$2 -s -o response
# curl -l $URL:$PORT_NGINX$2 -s -o response_body
#
# printf "\033[31mresponse     : \033[0m\n" ; cat response
# printf "\033[31mresponse_body: \033[0m\n" ; cat response_body

# send_request port <method> <target> []
# send_request()
# {
# 	PORT=$1
# 	printf "$2 $3 HTTP/1.1\r\n" > rqstfile
# 	shift 3
# 	for header in "$@"; do
# 		printf "$header\r\n" >> rqstfile
# 	done
# 	printf "\r\n" >> rqstfile
# 	cat rqstfile | $RQST_SENDER $URL $PORT
# }
#
# send_request $PORT_NGINX   "GET" "/" "host: tharchen"
# send_request $PORT_WEBSERV "GET" "/" "host: tharchen"
# send_request $PORT_NGINX   "GET" "/qwer" "host: tharchen"
# send_request $PORT_WEBSERV "GET" "/qwer" "host: tharchen"

BLACK=$(tput setaf 0)
RED=$(tput setaf 1)
GREEN=$(tput setaf 2)
YELLOW=$(tput setaf 3)
LIME_YELLOW=$(tput setaf 190)
POWDER_BLUE=$(tput setaf 153)
BLUE=$(tput setaf 4)
MAGENTA=$(tput setaf 5)
CYAN=$(tput setaf 6)
WHITE=$(tput setaf 7)
BRIGHT=$(tput bold)
C_RES=$(tput sgr0)
BLINK=$(tput blink)
REVERSE=$(tput smso)
UNDERLINE=$(tput smul)

# test ()
# {
# 	curl -s 127.0.0.1:$PORT_NGINX -o /dev/null
# 	IS_ONLINE_NGINX=$?
# 	curl -s 127.0.0.1:$PORT_WEBSERV -o /dev/null
# 	IS_ONLINE_WEBSERV=$?
#
# 	RET_NGINX=`curl -s -D - -o /dev/null 127.0.0.1:$PORT_NGINX$1 | grep -m1 "" | cut -c10- | head -c 3`
# 	RET_WEBSERV=`curl -s -D - -o /dev/null 127.0.0.1:$PORT_WEBSERV$1 | grep -m1 "" | cut -c10- | head -c 3`
# 	if [[ $RET_NGINX = $RET_WEBSERV ]]; then
# 		RES_COLOR=${GREEN}
# 	else
# 		RES_COLOR=${RED}
# 	fi
# 	if (( $IS_ONLINE_NGINX == 5 )); then
# 		RET_NGINX="${RED}$ERROR_5${C_RES}"
# 	elif (( $IS_ONLINE_NGINX == 6 )); then
# 		RET_NGINX="${RED}$ERROR_6${C_RES}"
# 	elif (( $IS_ONLINE_NGINX == 7 )); then
# 		RET_NGINX="${RED}$ERROR_7${C_RES}"
# 	elif (( $IS_ONLINE_NGINX == 8 )); then
# 		RET_NGINX="${RED}$ERROR_8${C_RES}"
# 	elif (( $IS_ONLINE_NGINX != 0 )); then
# 		RET_NGINX="${RED}$ERROR_UNKNOWN${C_RES}"
# 	fi
# 	if (( $IS_ONLINE_WEBSERV == 5 )); then
# 		RET_WEBSERV="${RED}$ERROR_5${C_RES}"
# 	elif (( $IS_ONLINE_WEBSERV == 6 )); then
# 		RET_WEBSERV="${RED}$ERROR_6${C_RES}"
# 	elif (( $IS_ONLINE_WEBSERV == 7 )); then
# 		RET_WEBSERV="${RED}$ERROR_7${C_RES}"
# 	elif (( $IS_ONLINE_WEBSERV == 8 )); then
# 		RET_WEBSERV="${RED}$ERROR_8${C_RES}"
# 	elif (( $IS_ONLINE_WEBSERV != 0 )); then
# 		RET_WEBSERV="${RED}$ERROR_UNKNOWN${C_RES}"
# 	fi
# 	if [[ $RET_NGINX == "" ]]; then
# 		RET_NGINX="no response"
# 	fi
# 	if [[ $RET_WEBSERV == "" ]]; then
# 		RET_WEBSERV="no response"
# 	fi
# 	printf "║ $RES_COLOR%-30s${C_RES} ║ %-3s %${WIDTH_RET}s ║ %-3s %${WIDTH_RET}s ║\n" $1 $IS_ONLINE_NGINX $RET_NGINX $IS_ONLINE_WEBSERV $RET_WEBSERV
# }

config:
	- no server
	- 1 server
		- no location
		- 1 location
			- 
			- /
		- 2 locations
			-
		- 3 locations
			-
	- 2 servers
	- 3 servers


test ()
{

}

tester()
{
	test "/asdfasd"
	test "/"
	test "/?ok=lol"
	test "^/#@!_()_#"
	test "/asd"
	test "/sdfds"
	test "/docs/"
	test "/as"
	test "//////////"
	test "./"
}

printf "╔═%-.30s═╦═%.${WIDTH_RET_TITLE}s═╦═%.${WIDTH_RET_TITLE}s═╗\n" $PATTERN_BORDER $PATTERN_BORDER $PATTERN_BORDER
printf "║ %-30s ║ %${WIDTH_RET_TITLE}s ║ %${WIDTH_RET_TITLE}s ║\n" "target" "nginx" "webserv"
printf "╠═%-.30s═╬═%.${WIDTH_RET_TITLE}s═╬═%.${WIDTH_RET_TITLE}s═╣\n" $PATTERN_BORDER $PATTERN_BORDER $PATTERN_BORDER
tester
printf "╚═%-.30s═╩═%.${WIDTH_RET_TITLE}s═╩═%.${WIDTH_RET_TITLE}s═╝\n" $PATTERN_BORDER $PATTERN_BORDER $PATTERN_BORDER





# target                         |      nginx |    webserv
#
# ╔ ╦ ╗
#
# ╠ ╬ ╬ ╣
#
# ╚ ╩ ╩ ╝
# ║═
#
# ╔═╗
