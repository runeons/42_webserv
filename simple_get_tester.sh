#!/usr/bin/env zsh

# /!\ USE IN DRAFT ! NOT IN overkill_tester
# usage: zsh overkill_tester/simple_get_tester.sh ./webserv ./conf/exemple.conf ./html

## COLORS
C_BLACK="\033[30;01m"
C_RED="\033[31;01m"
C_GREEN="\033[32;01m"
C_YELLOW="\033[33;01m"
C_BLUE="\033[34;01m"
C_MAGENTA="\033[35;01m"
C_CYAN="\033[36;01m"
C_WHITE="\033[37;01m"
C_GRAY="\033[90;01m"
# C_RES="\033[0m"

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


## GLOBAL VARIABLE
PATH_BIN=$1;
PATH_CONFIG=$2;
PATH_DIR=$3;

let "WIDTH_RET = 30"
let "WIDTH_RET_TITLE = WIDTH_RET + 4"
PATTERN_BORDER="═════════════════════════════════════════════════════════════════════════════════════════════════════════"
# WIDTH_RET_TITLE=$((WIDTH_RET + 4))

ERROR_5="        Couldn't resolve proxy"
ERROR_6="         Couldn't resolve host"
ERROR_7="     Failed to connect to host"
ERROR_8="            Weird server reply"
ERROR_D="                       Disable"
ERROR_UNKNOWN="                 Unknown error"

URL=127.0.0.1
PORT_WEBSERV=8000
PORT_NGINX=8080
RQST_SENDER=/usr/bin/nc

## tools

let "DEEP = 0"

check_args()
{
	# DEEP=($DEEP + 4); printf "%*s${C_GRAY}[ %s ]${C_RES} start\n" $((DEEP)) "" "CHECK_ARGS"

	if [[ ${PATH_BIN} == "" ]]; then
		printf "%*s${C_GRAY}[ %s ]${C_RES} PATH_BIN not specified \n" $((DEEP)) "" "CHECK_ARGS"
		exit
	# else
	# 	printf "%*s${C_GRAY}[ %s ]${C_RES} PATH_BIN = '${PATH_BIN}' \n" $((DEEP)) "" "CHECK_ARGS"
	fi
	if [[ ${PATH_DIR} == "" ]]; then
		printf "%*s${C_GRAY}[ %s ]${C_RES} PATH_DIR not specified \n" $((DEEP)) "" "CHECK_ARGS"
		exit
	# else
	# 	printf "%*s${C_GRAY}[ %s ]${C_RES} PATH_DIR = '${PATH_DIR}' \n" $((DEEP)) "" "CHECK_ARGS"
	fi
	# printf "%*s${C_GRAY}[ %s ]${C_RES} end\n" $((DEEP)) "" "CHECK_ARGS" ; DEEP=($DEEP - 4);
}

## core

get_test()
{
	# DEEP=($DEEP + 4); printf "%*s${C_GRAY}[ %s ]${C_RES} start\n" $((DEEP)) "" "CHECK_ARGS"
	curl -s http://127.0.0.1:$PORT_NGINX -o /dev/null
	IS_ONLINE_NGINX=$?
	# IS_ONLINE_NGINX=-1

	curl -s http://127.0.0.1:$PORT_WEBSERV -o /dev/null
	IS_ONLINE_WEBSERV=$?

	RET_NGINX=`curl -s -D - -o /dev/null http://127.0.0.1:$PORT_NGINX/$1 | grep -m1 "" | cut -c10- | head -c 3`
	RET_WEBSERV=`curl -s -D - -o /dev/null http://127.0.0.1:$PORT_WEBSERV/$1 | grep -m1 "" | cut -c10- | head -c 3`
	if [[ $RET_NGINX = $RET_WEBSERV ]]; then
		RES_COLOR=${GREEN}
	else
		RES_COLOR=${RED}
	fi
	if (( $IS_ONLINE_NGINX == 5 )); then
		RET_NGINX="${RED}$ERROR_5${C_RES}"
	elif (( $IS_ONLINE_NGINX == 6 )); then
		RET_NGINX="${RED}$ERROR_6${C_RES}"
	elif (( $IS_ONLINE_NGINX == 7 )); then
		RET_NGINX="${RED}$ERROR_7${C_RES}"
	elif (( $IS_ONLINE_NGINX == 8 )); then
		RET_NGINX="${RED}$ERROR_8${C_RES}"
	elif (( $IS_ONLINE_NGINX == -1 )); then
		RET_NGINX="${RED}$ERROR_D${C_RES}"
	elif (( $IS_ONLINE_NGINX != 0 )); then
		RET_NGINX="${RED}$ERROR_UNKNOWN${C_RES}"
	fi
	if (( $IS_ONLINE_WEBSERV == 5 )); then
		RET_WEBSERV="${RED}$ERROR_5${C_RES}"
	elif (( $IS_ONLINE_WEBSERV == 6 )); then
		RET_WEBSERV="${RED}$ERROR_6${C_RES}"
	elif (( $IS_ONLINE_WEBSERV == 7 )); then
		RET_WEBSERV="${RED}$ERROR_7${C_RES}"
	elif (( $IS_ONLINE_WEBSERV == 8 )); then
		RET_WEBSERV="${RED}$ERROR_8${C_RES}"
	elif (( $IS_ONLINE_WEBSERV == -1 )); then
		RET_WEBSERV="${RED}$ERROR_D${C_RES}"
	elif (( $IS_ONLINE_WEBSERV != 0 )); then
		RET_WEBSERV="${RED}$ERROR_UNKNOWN${C_RES}"
	fi
	if [[ $RET_NGINX == "" ]]; then
		RET_NGINX="no response"
	fi
	if [[ $RET_WEBSERV == "" ]]; then
		RET_WEBSERV="no response"
	fi

	printf "║ $RES_COLOR%-60s${C_RES} " $1
	if [[ $RET_NGINX =~ "1.." ]]; then
		printf "║     $GREEN%${WIDTH_RET}s$C_RES " $RET_NGINX
	elif [[ $RET_NGINX =~ "2.." ]]; then
		printf "║     $GREEN%${WIDTH_RET}s$C_RES " $RET_NGINX
	elif [[ $RET_NGINX =~ "3.." ]]; then
		printf "║     $YELLOW%${WIDTH_RET}s$C_RES " $RET_NGINX
	elif [[ $RET_NGINX =~ "4.." ]]; then
		printf "║     $MAGENTA%${WIDTH_RET}s$C_RES " $RET_NGINX
	elif [[ $RET_NGINX =~ "5.." ]]; then
		printf "║     $RED%${WIDTH_RET}s$C_RES " $RET_NGINX
	else
		printf "║     $RED%${WIDTH_RET}s$C_RES " $RET_NGINX
	fi

	if [[ $RET_WEBSERV =~ "1.." ]]; then
		printf "║     $GREEN%${WIDTH_RET}s$C_RES ║\n" $RET_WEBSERV
	elif [[ $RET_WEBSERV =~ "2.." ]]; then
		printf "║     $GREEN%${WIDTH_RET}s$C_RES ║\n" $RET_WEBSERV
	elif [[ $RET_WEBSERV =~ "3.." ]]; then
		printf "║     $YELLOW%${WIDTH_RET}s$C_RES ║\n" $RET_WEBSERV
	elif [[ $RET_WEBSERV =~ "4.." ]]; then
		printf "║     $MAGENTA%${WIDTH_RET}s$C_RES ║\n" $RET_WEBSERV
	elif [[ $RET_WEBSERV =~ "5.." ]]; then
		printf "║     $RED%${WIDTH_RET}s$C_RES ║\n" $RET_WEBSERV
	else
		printf "║     $RED%${WIDTH_RET}s$C_RES ║\n" $RET_WEBSERV
	fi

	# printf "%*s${C_GRAY}[ %s ]${C_RES} end\n" $((DEEP)) "" "CHECK_ARGS" ; DEEP=($DEEP - 4);
}

tester()
{
	# DEEP=($DEEP + 4); printf "%*s${C_GRAY}[ %s ]${C_RES} start\n" $((DEEP)) "" "CHECK_ARGS"
	check_args

	printf "╔═%-.60s═╦═%.${WIDTH_RET_TITLE}s═╦═%.${WIDTH_RET_TITLE}s═╗\n" $PATTERN_BORDER $PATTERN_BORDER $PATTERN_BORDER
	printf "║ %-60s ║ %${WIDTH_RET_TITLE}s ║ %${WIDTH_RET_TITLE}s ║\n" "target" "nginx" "webserv"
	printf "╠═%-.60s═╬═%.${WIDTH_RET_TITLE}s═╬═%.${WIDTH_RET_TITLE}s═╣\n" $PATTERN_BORDER $PATTERN_BORDER $PATTERN_BORDER

	# LIST FILE
	# list_file=("${(@f)$(PATHH="$PATH_DIR" ; TMP=`printf $PATHH | wc -c | xargs` ; find ./html/ | grep $PATHH | sort | cut -c`expr $TMP + 2`-)}");
	list_file=("${(@f)$(PATHH="$PATH_DIR" ; TMP=`printf $PATHH | wc -c | xargs` ; find ./html | grep $PATHH | sort | cut -c8-)}");


	for file in $list_file; do
		get_test $file
	done

	printf "╚═%-.60s═╩═%.${WIDTH_RET_TITLE}s═╩═%.${WIDTH_RET_TITLE}s═╝\n" $PATTERN_BORDER $PATTERN_BORDER $PATTERN_BORDER
	# printf "%*s${C_GRAY}[ %s ]${C_RES} end\n" $((DEEP)) "" "CHECK_ARGS" ; DEEP=($DEEP - 4);
}

main()
{
	# printf "%*s${C_GRAY}[ %s ]${C_RES} start\n" $((DEEP)) "" "MAIN"

	make -j
	if (( $? != 0 )); then
		echo "run the tester in the draft directory"
		exit
	fi

	killall webserv 2>/dev/null
	$PATH_BIN $PATH_CONFIG >/dev/null 2>/dev/null &
	# $PATH_BIN $PATH_CONFIG >/dev/ttys001 2>/dev/ttys001 &
	# $PATH_BIN $PATH_CONFIG &
	# sleep 1
	RET_WEBSERV=`curl -s -D - -o /dev/null "http://127.0.0.1:$PORT_WEBSERV" | grep -m1 "" | cut -c10- | head -c 3`
	while [[ $RET_WEBSERV != 200 ]]; do
		RET_WEBSERV=`curl -s -D - -o /dev/null "http://127.0.0.1:$PORT_WEBSERV" | grep -m1 "" | cut -c10- | head -c 3`;
	done
	tester
	killall webserv 2>/dev/null
	# printf "%*s${C_GRAY}[ %s ]${C_RES} end\n" $((DEEP)) "" "MAIN"
}

echo "v3: $3"
rm -rf /usr/local/Cellar/nginx/1.21.1/html
ln -s $3 /usr/local/Cellar/nginx/1.21.1/html

main $1 $2 $3
