#!/usr/bin/env zsh

cd html;
if (( $? != 0 )); then
	echo "error: lance le script dans draft"
	exit
fi
TMP=`pwd`;
cd ..;
mv /usr/local/Cellar/nginx/1.21.1/html/ /usr/local/Cellar/nginx/1.21.1/html.old;
ln -s $TMP /usr/local/Cellar/nginx/1.21.1/html;
mkdir -p html/permissions_tests;
zsh overkill_tester/perm.sh html/permissions_tests;
zsh overkill_tester/simple_get_tester.sh ./webserv ./conf/exemple.conf ./html
