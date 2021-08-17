# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    class_copy.sh                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsantoni <tsantoni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/16 21:13:37 by tsantoni          #+#    #+#              #
#    Updated: 2021/06/16 21:14:00 by tsantoni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#!/bin/bash

#___________________________ COLORS __________________________#
RED_B="\033[31;01m"
WHITE_B="\033[37;01m"
GREY_B="\033[90;01m"
C_RES="\033[37;01m"

#____________________________________________________________#
#___________________________ INPUT __________________________#
#____________________________________________________________#

if [[ $# != 2  ]]; then
	printf "${RED_B}Error : ${GREY_B}(Usage) : bash class_copy.sh CLASS_SRC NEW_CLASS${C_RES}\n"
	exit 1;
fi
if [[ $1 ]]; then
	SRC=$1;
fi
if [[ $2 ]]; then
	NEW=$2;
fi

CPP=1
HPP=1
# in Makefile : add Cpy.cpp
MAKEFILE=1
# in Main : add Cpy.hpp
MAIN=1
FILE_MAIN+="main.cpp"

#_____________________ INIT _____________________#
SRC_CPP_FILE=$SRC".cpp"
NEW_CPP_FILE=$NEW".cpp"
SRC_HPP_FILE=$SRC".hpp"
NEW_HPP_FILE=$NEW".hpp"
ADD_TO_MAKEFILE="!				"$NEW_CPP_FILE" \\\ "
ADD_TO_MAIN="# include \"${NEW_HPP_FILE}\""
#_____________________ CPP _____________________#
if [[ $CPP == 1 ]]; then
	cp $SRC_CPP_FILE $NEW_CPP_FILE
	sed -i "" "s/$SRC/$NEW/g" $NEW_CPP_FILE
fi
#_____________________ HPP _____________________#
if [[ $HPP == 1 ]]; then
	cp $SRC_HPP_FILE $NEW_HPP_FILE
	sed -i "" "s/$SRC/$NEW/g" $NEW_HPP_FILE
	sed -i "" "s/${SRC^^}/${NEW^^}/g" $NEW_HPP_FILE
fi
#_____________________ MAKEFILE _____________________#
if [[ $MAKEFILE == 1 ]]; then
	LINE=`grep -n -m 1 $SRC_CPP_FILE Makefile | sed  "s/\([0-9]*\).*/\1/"`
	LINE=$((LINE+1))
	sed -i "" "${LINE}i\\
					$ADD_TO_MAKEFILE
	" Makefile
	sed -i "" "${LINE}s/^!//g" Makefile
	sed -i "" "${LINE}s/.$//g" Makefile
fi
#_____________________ MAIN _____________________#
if [[ $MAIN == 1 ]]; then
	LINE=`grep -n -m 1 $SRC_HPP_FILE $FILE_MAIN | sed  "s/\([0-9]*\).*/\1/"`
	LINE=$((LINE+1))
	sed -i "" "${LINE}i\\
					$ADD_TO_MAIN
	" $FILE_MAIN
fi