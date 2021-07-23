# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    class_creator.sh                                   :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsantoni <tsantoni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/16 21:13:33 by tsantoni          #+#    #+#              #
#    Updated: 2021/07/23 10:55:23 by tsantoni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#!/bin/bash

#____________________________________________________________#
#___________________________ INPUT __________________________#
#____________________________________________________________#
TAB_SIZE=4

#___________________________ CLASS_NAME __________________________#
CLASS_NAME="Response"
INHERIT_FROM=""

#___________________________ FILES TO INCLUDE __________________________#
CPP=1
HPP=1
MAIN=0
# FILE_MAIN+="main_"$CLASS_NAME".cpp"
FILE_MAIN+="main.cpp"
MAKEFILE=0
COLOR=0

#___________________________ FUNCTIONS TO INCLUDE __________________________#
GETTERS=1
SETTERS=1
OVERLOAD_OSTREAM=0
VIRTUAL_DESTRUCT=1

#___________________________ OTHER CLASSES TO INCLUDE TO MAKEFILE __________________________#
# ADD_TO_MAKEFILE=("Bureaucrat" "" "")

#___________________________ MESSAGES COLOR __________________________#
ALL_GREY=1

#_____________________ INPUT ATTRIBUTES _____________________#
# "Type"	"Name"	"Value" (Value : " " si pas de value)

ATT_1=("int"			"status_code"	" ")
ATT_2=("std::string"	"full_path"	" ")
ATT_3=("std::string"	"response"	" ")
ATT_4=("std::string"	"response_header"	" ")
ATT_5=("std::string"	"response_body"	" ")
ATT_6=("std::string"	"response_bin"	" ")
ATT_7=("std::string"	"response_header_bin"	" ")
ATT_8=("std::string"	"response_body_bin"	" ")
ATT_9=("std::map<int, std::string>"	"error_msg"	" ")
ATT_10=("std::map<int, std::string>"	"error_body"	" ")
# ATT_3=("const int"	"gradeToSign"	" ")
# ATT_4=("const int"	"gradeToExecute"	" ")
# ATT_5=(""	""	" ")
# ATT_6=(""	""	" ")
# ATT_7=(""	""	" ")
# ATT_8=(""	""	" ")
# ATT_9=(""	""	" ")

#_____________________ INPUT INCLUDES _____________________#
# INCLUDES_GLOBAL=("" "")
INCLUDES_LOCAL=("webserv")
#_____________________ INPUT CONSTRUCTORS/DESTRUCTOR MESSAGES _____________________#
# si *STRUCT_*_MSG="", rempli par defaut
CONSTRUCT_DEF_MSG="\""$CLASS_NAME" creation...\""
CONSTRUCT_CPY_MSG="\""$CLASS_NAME" creation...\""
DESTRUCTOR_MSG="\""$CLASS_NAME" destruction...\""
#_____________________ INPUT PARAMETRIC CONSTRUCTORS _____________________#
#CONSTRUCT_PARAM_1=("TYPE"	"NAME"	"MSG") : si MSG == "", rempli par defaut

# CONSTRUCT_PARAM_1=("unsigned int"	"n"	"\""$CLASS_NAME" creation...\"")
# CONSTRUCT_PARAM_2=("std::string"	"name" "")
#_____________________ INPUT OVERLOAD << ATTRIBUTE _____________________#
OSTREAM="${ATT_1[1]}"
#_____________________ INPUT FUNCTIONS _____________________#

#PRIV/PUB_FUNC_X=("ret_type" "func_name" "param_type" "param_name")
# if param_type == "", writes (void)

# PRIV_FUNC_1=("" "" "" " ")
# PRIV_FUNC_2=("" "" "" " ")
# PRIV_FUNC_3=("" "" "" " ")
# PRIV_FUNC_4=("" "" "" " ")

# PUB_FUNC_1=("void" "treat_client" "void" " ")
# PUB_FUNC_2=("void" "receive_request" "void" " ")
# PUB_FUNC_3=("void" "check_request" "void" " ")
# PUB_FUNC_4=("const value_type &" "top" "void" " ")
# PUB_FUNC_5=("void" "push" "const value_type&" "val")
# PUB_FUNC_6=("void" "emplace" "Args&&..." "args")
# PUB_FUNC_7=("void" "pop" "void" " ")
# PUB_FUNC_8=("void" "swap" "MutantStack &" "x")
# PUB_FUNC_9=("" "" "" " ")
#_____________________ INPUT COLORS _____________________#
CONSTRUCT_COLOR="GREEN_TREE"
DESTRUCT_COLOR="CORAIL"
ASSIGN_COLOR="BROWN"
PUB_FUNC_COLOR="SKY_BLUE"
PRIV_FUNC_COLOR="SKY_BLUE"

if [[ $ALL_GREY == 1 ]]; then
	CONSTRUCT_COLOR="GREY"
	DESTRUCT_COLOR="GREY"
	ASSIGN_COLOR="GREY"
	PUB_FUNC_COLOR="GREY"
	PRIV_FUNC_COLOR="GREY"
fi
#____________________________________________________________#
#___________________________ SETUP __________________________#
#____________________________________________________________#

OLD_IFS="$IFS"
IFS=$'\n'

ATT_TYPES=($ATT_1 $ATT_2 $ATT_3 $ATT_4 $ATT_5 $ATT_6 $ATT_7 $ATT_8 $ATT_9 $ATT_10 $ATT_11 $ATT_12 $ATT_13 $ATT_14 $ATT_15)
ATT_NAMES=(${ATT_1[1]} ${ATT_2[1]} ${ATT_3[1]} ${ATT_4[1]} ${ATT_5[1]} ${ATT_6[1]} ${ATT_7[1]} ${ATT_8[1]} ${ATT_9[1]} ${ATT_10[1]} ${ATT_11[1]} ${ATT_12[1]} ${ATT_13[1]} ${ATT_14[1]} ${ATT_15[1]})
ATT_VALS=(${ATT_1[2]} ${ATT_2[2]} ${ATT_3[2]} ${ATT_4[2]} ${ATT_5[2]} ${ATT_6[2]} ${ATT_7[2]} ${ATT_8[2]} ${ATT_9[2]} ${ATT_10[2]} ${ATT_11[2]} ${ATT_12[2]} ${ATT_13[2]} ${ATT_14[2]} ${ATT_15[2]})

CONSTRUCT_TYPES=(${CONSTRUCT_PARAM_1[0]} ${CONSTRUCT_PARAM_2[0]} ${CONSTRUCT_PARAM_3[0]} ${CONSTRUCT_PARAM_4[0]} ${CONSTRUCT_PARAM_5[0]})
CONSTRUCT_NAMES=(${CONSTRUCT_PARAM_1[1]} ${CONSTRUCT_PARAM_2[1]} ${CONSTRUCT_PARAM_3[1]} ${CONSTRUCT_PARAM_4[1]} ${CONSTRUCT_PARAM_5[1]})
CONSTRUCT_MSGS=(${CONSTRUCT_PARAM_1[2]} ${CONSTRUCT_PARAM_2[2]} ${CONSTRUCT_PARAM_3[2]} ${CONSTRUCT_PARAM_4[2]} ${CONSTRUCT_PARAM_5[2]})

PUB_FUNC_RET=(${PUB_FUNC_1[0]} ${PUB_FUNC_2[0]} ${PUB_FUNC_3[0]} ${PUB_FUNC_4[0]} ${PUB_FUNC_5[0]} ${PUB_FUNC_6[0]} ${PUB_FUNC_7[0]} ${PUB_FUNC_8[0]} ${PUB_FUNC_9[0]} ${PUB_FUNC_10[0]})
PUB_FUNC_NAME=(${PUB_FUNC_1[1]} ${PUB_FUNC_2[1]} ${PUB_FUNC_3[1]} ${PUB_FUNC_4[1]} ${PUB_FUNC_5[1]} ${PUB_FUNC_6[1]} ${PUB_FUNC_7[1]} ${PUB_FUNC_8[1]} ${PUB_FUNC_9[1]} ${PUB_FUNC_10[1]})
PUB_FUNC_PTYPE=(${PUB_FUNC_1[2]} ${PUB_FUNC_2[2]} ${PUB_FUNC_3[2]} ${PUB_FUNC_4[2]} ${PUB_FUNC_5[2]} ${PUB_FUNC_6[2]} ${PUB_FUNC_7[2]} ${PUB_FUNC_8[2]} ${PUB_FUNC_9[2]} ${PUB_FUNC_10[2]})
PUB_FUNC_PNAME=(${PUB_FUNC_1[3]} ${PUB_FUNC_2[3]} ${PUB_FUNC_3[3]} ${PUB_FUNC_4[3]} ${PUB_FUNC_5[3]} ${PUB_FUNC_6[3]} ${PUB_FUNC_7[3]} ${PUB_FUNC_8[3]} ${PUB_FUNC_9[3]} ${PUB_FUNC_10[3]})

PRIV_FUNC_RET=(${PRIV_FUNC_1[0]} ${PRIV_FUNC_2[0]} ${PRIV_FUNC_3[0]} ${PRIV_FUNC_4[0]} ${PRIV_FUNC_5[0]} ${PRIV_FUNC_6[0]} ${PRIV_FUNC_7[0]} ${PRIV_FUNC_8[0]} ${PRIV_FUNC_9[0]} ${PRIV_FUNC_10[0]})
PRIV_FUNC_NAME=(${PRIV_FUNC_1[1]} ${PRIV_FUNC_2[1]} ${PRIV_FUNC_3[1]} ${PRIV_FUNC_4[1]} ${PRIV_FUNC_5[1]} ${PRIV_FUNC_6[1]} ${PRIV_FUNC_7[1]} ${PRIV_FUNC_8[1]} ${PRIV_FUNC_9[1]} ${PRIV_FUNC_10[1]})
PRIV_FUNC_PTYPE=(${PRIV_FUNC_1[2]} ${PRIV_FUNC_2[2]} ${PRIV_FUNC_3[2]} ${PRIV_FUNC_4[2]} ${PRIV_FUNC_5[2]} ${PRIV_FUNC_6[2]} ${PRIV_FUNC_7[2]} ${PRIV_FUNC_8[2]} ${PRIV_FUNC_9[2]} ${PRIV_FUNC_10[2]})
PRIV_FUNC_PNAME=(${PRIV_FUNC_1[3]} ${PRIV_FUNC_2[3]} ${PRIV_FUNC_3[3]} ${PRIV_FUNC_4[3]} ${PRIV_FUNC_5[3]} ${PRIV_FUNC_6[3]} ${PRIV_FUNC_7[3]} ${PRIV_FUNC_8[3]} ${PRIV_FUNC_9[3]} ${PRIV_FUNC_10[3]})

#____________________________________________________________#
#_____________________ HPP CONSTRUCTION _____________________#
#____________________________________________________________#

toCamel() # ret=`toCamel get my_var` -> ret -> getMyVar
{
	IFS=" "
	local tmp=$1
	arr=(${tmp//_/ })
	# printf $1
	for i in "${arr[@]}"; do
		printf "${i^}"
	done
	IFS="\n"
}

if [[ $HPP == 1 ]]; then
#_____________________ WRITE INCLUDES _____________________#

FILE_HPP+=$CLASS_NAME".hpp"

#_____________________ DEFINE INCLUDES _____________________#

printf "#ifndef %s_HPP\n" ${CLASS_NAME^^} > $FILE_HPP
printf "# define %s_HPP\n\n" ${CLASS_NAME^^} >> $FILE_HPP

for i in "${INCLUDES_GLOBAL[@]}" ; do : ;
   printf "# include <%s>\n" $i >> $FILE_HPP
done

for i in "${INCLUDES_LOCAL[@]}" ; do : ;
   printf "# include \"%s.hpp\"\n" $i >> $FILE_HPP
done
if [[ $INHERIT_FROM != "" ]]; then
	printf "# include \"%s.hpp\"\n" $INHERIT_FROM >> $FILE_HPP
fi

printf "\nclass %s" $CLASS_NAME >> $FILE_HPP
if [[ $INHERIT_FROM != "" ]]; then
	printf " : public %s" $INHERIT_FROM >> $FILE_HPP
fi
printf "\n{\n	private:\n" >> $FILE_HPP

#_____________________ DEFINE PRIVATE ATTRIBUTES _____________________#

MAX_LEN=${#ATT_1[0]}
for i in "${ATT_TYPES[@]}" ; do : ;
	if 	[[ $i ]]; then
		if (( ${#i} > $MAX_LEN )); then # REMOVED the if $i condition
			MAX_LEN=${#i}
		fi
	fi
done

# printf "MAX_LEN : %d\n" $MAX_LEN

if [[ $(( MAX_LEN % $TAB_SIZE )) == 0 ]]; then
	((MAX_TAB=($MAX_LEN / $TAB_SIZE) + 2))
else
	((MAX_TAB=($MAX_LEN / $TAB_SIZE) + 1))
fi
# printf "MAX_TAB : %d\n" $MAX_TAB
for i in "${!ATT_TYPES[@]}"; do
	if [[ $i ]]; then
		printf "		%s" "${ATT_TYPES[i]}" >> $FILE_HPP
		for (( j = 0; j < $((MAX_TAB - ("${#ATT_TYPES[i]}" / TAB_SIZE))); j++ )); do
			printf "	" >> $FILE_HPP
		done
		printf "_%s" "${ATT_NAMES[i]}" >> $FILE_HPP
		if [[ "${ATT_TYPES[i]}" == *"static const"* ]]; then
			printf " = %s" "${ATT_VALS[i]}" >> $FILE_HPP
		fi
		printf ";\n" >> $FILE_HPP
	fi
done

#_____________________ DEFINE PRIVATE FUNCTIONS _____________________#
printf "\n" >> $FILE_HPP
for i in "${!PRIV_FUNC_RET[@]}"; do
	if [[ $i ]]; then
		printf "		%s" ${PRIV_FUNC_RET[i]} >> $FILE_HPP
		for (( j = 0; j < $((MAX_TAB - ("${#PRIV_FUNC_RET[i]}" / TAB_SIZE))); j++ )); do
			printf "	" >> $FILE_HPP
		done
		if [[ ${PRIV_FUNC_PTYPE[i]} == "" ]]; then
			printf "%s(void);\n" ${PRIV_FUNC_NAME[i]} >> $FILE_HPP
		else
			printf "%s(%s %s);\n" ${PRIV_FUNC_NAME[i]} ${PRIV_FUNC_PTYPE[i]} ${PRIV_FUNC_PNAME[i]} >> $FILE_HPP
		fi
	fi
done

#_____________________ DEFINE CONSTRUCTORS/DESTRUCTOR _____________________#

printf "	public:\n" >> $FILE_HPP
printf "		%s();\n" $CLASS_NAME >> $FILE_HPP
for i in "${!CONSTRUCT_TYPES[@]}"; do
	if [[ $i ]]; then
		printf "		%s(%s);\n" $CLASS_NAME "${CONSTRUCT_TYPES[i]}" >> $FILE_HPP
	fi
done
printf "		%s(const %s & src);\n" $CLASS_NAME $CLASS_NAME >> $FILE_HPP
printf "		" >> $FILE_HPP
if [[ $INHERIT_FROM != "" || $VIRTUAL_DESTRUCT == 1 ]]; then
	printf "virtual " >> $FILE_HPP
fi
printf "~%s();\n\n" $CLASS_NAME >> $FILE_HPP

#_____________________ DEFINE GETTERS/SETTERS _____________________#

for i in "${!ATT_TYPES[@]}"; do
	if [[ $i ]]; then
		if [[ $GETTERS == 1 ]]; then
			TMP=${ATT_TYPES[i]//"static const "/}
			printf "		%s" "${TMP}" >> $FILE_HPP
			for (( j = 0; j < $((MAX_TAB - ("${#TMP}" / TAB_SIZE))); j++ )); do
				printf "	" >> $FILE_HPP
			done
			printf "get%s(void) const;\n" `toCamel ${ATT_NAMES[i]}` >> $FILE_HPP
		fi
		# setter
		if [[ $SETTERS == 1 ]]; then
			printf "		void" >> $FILE_HPP
			for (( j = 0; j < $((MAX_TAB - (4 / TAB_SIZE))); j++ )); do
				printf "	" >> $FILE_HPP
			done
			printf "set%s(const %s %s);\n" `toCamel ${ATT_NAMES[i]}` "${TMP}" "${ATT_NAMES[i]}" >> $FILE_HPP
		fi
	fi
done


#_____________________ DEFINE PUBLIC FUNCTIONS _____________________#
printf "\n" >> $FILE_HPP
for i in "${!PUB_FUNC_RET[@]}"; do
	if [[ $i ]]; then
		printf "		%s" ${PUB_FUNC_RET[i]} >> $FILE_HPP
		for (( j = 0; j < $((MAX_TAB - ("${#PUB_FUNC_RET[i]}" / TAB_SIZE))); j++ )); do
			printf "	" >> $FILE_HPP
		done
		if [[ ${PUB_FUNC_PTYPE[i]} == "" ||  ${PUB_FUNC_PTYPE[i]} == "void" ]]; then
			printf "%s(void);\n" ${PUB_FUNC_NAME[i]} >> $FILE_HPP
		else
			printf "%s(%s %s);\n" ${PUB_FUNC_NAME[i]} ${PUB_FUNC_PTYPE[i]} ${PUB_FUNC_PNAME[i]} >> $FILE_HPP
		fi
	fi
done

#_____________________ DEFINE ASSIGNATION OPERATOR _____________________#

printf "\n		%s" $CLASS_NAME >> $FILE_HPP
for (( j = 0; j < $((MAX_TAB - ("${#CLASS_NAME}" / TAB_SIZE))); j++ )); do
	printf "	" >> $FILE_HPP
done
printf "&operator=(const %s & src);\n" $CLASS_NAME >> $FILE_HPP

#_____________________ DEFINE OSTREAM OPERATOR _____________________#

printf "};\n\n" >> $FILE_HPP
if [[ $OVERLOAD_OSTREAM == 1 ]]; then
printf "std::ostream	&operator<<(std::ostream & os, const %s & src);\n" $CLASS_NAME >> $FILE_HPP
fi
printf "\n#endif\n" >> $FILE_HPP

fi #HPP CONSTRUCTION

#____________________________________________________________#
#_____________________ CPP CONSTRUCTION _____________________#
#____________________________________________________________#

if [[ $CPP == 1 ]]; then

FILE_CPP+=$CLASS_NAME".cpp"

#_____________________ INCLUDES _____________________#

printf "# include \"%s.hpp\"\n" $CLASS_NAME > $FILE_CPP
printf "\n" >> $FILE_CPP

#_____________________ DECLARE DEFAULT CONSTRUCTOR _____________________#

# Assigns the non static variables with values
printf "// Default constructor\n" >> $FILE_CPP
printf "%s::%s(void)\n{\n" $CLASS_NAME $CLASS_NAME >> $FILE_CPP
if [[ $CONSTRUCT_DEF_MSG == "" ]]; then
	printf "	std::cout << %s << \"Default constructor called\" << C_RES << std::endl;\n" $CONSTRUCT_COLOR >> $FILE_CPP
else
	printf "	std::cout << %s << %s << C_RES << std::endl;\n" $CONSTRUCT_COLOR $CONSTRUCT_DEF_MSG >> $FILE_CPP
fi
for i in "${!ATT_TYPES[@]}"; do
	if [[ $i ]]; then
		if [[ "${ATT_TYPES[i]}" != *"static const"* ]]; then
			if [[ "${ATT_VALS[i]}" != " " ]]; then
				printf "	this->_%s = %s;\n" "${ATT_NAMES[i]}" "${ATT_VALS[i]}" >> $FILE_CPP
			fi
		fi
	fi
done
printf "	return ;\n}\n\n" >> $FILE_CPP

#_____________________ DECLARE COPY CONSTRUCTOR _____________________#

printf "// Copy constructor\n" >> $FILE_CPP
printf "%s::%s(const %s& src)\n{\n" $CLASS_NAME $CLASS_NAME $CLASS_NAME >> $FILE_CPP
if [[ $CONSTRUCT_CPY_MSG == "" ]]; then
	printf "	std::cout << %s << \"Copy constructor called\" << C_RES << std::endl;\n" $CONSTRUCT_COLOR $CONSTRUCT_CPY_MSG>> $FILE_CPP
else
	printf "	std::cout << %s << %s << C_RES << std::endl;\n" $CONSTRUCT_COLOR $CONSTRUCT_CPY_MSG>> $FILE_CPP
fi
printf "	*this = src;\n" >> $FILE_CPP
printf "	return;\n}\n\n" >> $FILE_CPP

#_____________________ DECLARE PARAMETRIC CONSTRUCTORS _____________________#


# // HumanA::HumanA(std::string name, Weapon& weapon) : _name(name), _weapon(weapon)

for i in "${!CONSTRUCT_TYPES[@]}"; do
	if [[ $i ]]; then
		printf "// Parametric constructor (%s)\n" "${CONSTRUCT_TYPES[i]}" >> $FILE_CPP
		printf "%s::%s(%s %s) : _%s(%s)\n{\n" $CLASS_NAME $CLASS_NAME "${CONSTRUCT_TYPES[i]}" "${CONSTRUCT_NAMES[i]}" "${CONSTRUCT_NAMES[i]}" "${CONSTRUCT_NAMES[i]}" >> $FILE_CPP
		if [[ "${CONSTRUCT_MSGS[i]}" == "" ]]; then
			printf "	std::cout << %s << \"%s constructor called\" << C_RES << std::endl;\n" $CONSTRUCT_COLOR "${CONSTRUCT_TYPES[i]^}" >> $FILE_CPP
		else
			printf "	std::cout << %s << %s << C_RES << std::endl;\n" $CONSTRUCT_COLOR "${CONSTRUCT_MSGS[i]}" >> $FILE_CPP
		fi
		printf "	return ;\n}\n\n" >> $FILE_CPP
	fi
done

#_____________________ DECLARE DESTRUCTOR _____________________#

printf "// Destructor\n" >> $FILE_CPP
printf "%s::~%s(void)\n{\n" $CLASS_NAME $CLASS_NAME >> $FILE_CPP
if [[ $DESTRUCTOR_MSG == "" ]]; then
	printf "	std::cout << %s << \"Destructor called\" << C_RES << std::endl;\n" $DESTRUCT_COLOR >> $FILE_CPP
else
	printf "	std::cout << %s << %s << C_RES << std::endl;\n" $DESTRUCT_COLOR $DESTRUCTOR_MSG >> $FILE_CPP
fi
printf "	return;\n}\n\n" >> $FILE_CPP

#_____________________ DECLARE ASSIGNATION OPERATOR _____________________#

# Assigns the non static variables with values
printf "// Assignation operator\n" >> $FILE_CPP
printf "%s &	%s::operator=(const %s& rhs)" $CLASS_NAME $CLASS_NAME $CLASS_NAME >> $FILE_CPP
printf "\n{\n" >> $FILE_CPP
printf "	std::cout << %s << \"%s Assignation operator called\" << C_RES << std::endl;\n" $ASSIGN_COLOR $CLASS_NAME >> $FILE_CPP
printf "	if (this != &rhs)\n" >> $FILE_CPP
printf "	{\n" >> $FILE_CPP
for i in "${!ATT_TYPES[@]}"; do
	if [[ $i ]]; then
		if [[ "${ATT_TYPES[i]}" != *"const"* ]]; then
			printf "		this->_%s = rhs.get%s();\n" "${ATT_NAMES[i]}" `toCamel ${ATT_NAMES[i]}` >> $FILE_CPP
		fi
	fi
done
printf "	}\n" >> $FILE_CPP
printf "	return (*this);\n}\n\n" >> $FILE_CPP

#_____________________ DECLARE PRIVATE FUNCTIONS _____________________#

for i in "${!PRIV_FUNC_RET[@]}"; do
	if [[ $i ]]; then
		if [[ ${PRIV_FUNC_PTYPE[i]} == "" || ${PRIV_FUNC_PTYPE[i]} == "void" ]]; then
			printf "%s %s::%s(void)\n{\n" ${PRIV_FUNC_RET[i]} $CLASS_NAME ${PRIV_FUNC_NAME[i]} >> $FILE_CPP
		else
			printf "%s %s::%s(%s %s)\n{\n" ${PRIV_FUNC_RET[i]} $CLASS_NAME ${PRIV_FUNC_NAME[i]} ${PRIV_FUNC_PTYPE[i]} ${PRIV_FUNC_PNAME[i]} >> $FILE_CPP
		fi
		printf "	(void)%s;\n" ${PRIV_FUNC_PNAME[i]} >> $FILE_CPP
		printf "	std::cout << %s << \"%s called\" << C_RES << std::endl;\n" $PRIV_FUNC_COLOR ${PRIV_FUNC_NAME[i]} >> $FILE_CPP
		printf "	return ;\n}\n\n" >> $FILE_CPP
	fi
done

#_____________________ DECLARE GETTERS AND SETTERS _____________________#

printf "// getters and setters (non static attributes)\n" >> $FILE_CPP

for i in "${!ATT_TYPES[@]}"; do
	if [[ $i ]]; then
		# getter
		if [[ $GETTERS == 1 ]]; then
			TMP=${ATT_TYPES[i]//"static const "/}
			printf "%s %s::get%s(void) const" ${TMP} $CLASS_NAME `toCamel ${ATT_NAMES[i]}` >> $FILE_CPP
			printf "\n{\n\treturn (this->_%s);\n}\n\n" ${ATT_NAMES[i]} >> $FILE_CPP
		fi
		# setter only if non static
		if [[ $SETTERS == 1 ]]; then
			if [[ "${ATT_TYPES[i]}" != *"static const"* ]]; then
				printf "void %s::set%s(const %s %s)" $CLASS_NAME `toCamel ${ATT_NAMES[i]}` ${TMP} ${ATT_NAMES[i]} >> $FILE_CPP
				printf "\n{\n\tthis->_%s = %s;\n\treturn ;\n}\n\n" ${ATT_NAMES[i]} ${ATT_NAMES[i]} >> $FILE_CPP
			fi
		fi
	fi
done

#_____________________ DECLARE PUBLIC FUNCTIONS _____________________#

for i in "${!PUB_FUNC_RET[@]}"; do
	if [[ $i ]]; then
		if [[ ${PUB_FUNC_PTYPE[i]} == "" || ${PUB_FUNC_PTYPE[i]} == "void" ]]; then
			printf "%s %s::%s(void)\n{\n" ${PUB_FUNC_RET[i]} $CLASS_NAME ${PUB_FUNC_NAME[i]} >> $FILE_CPP
		else
			printf "%s %s::%s(%s %s)\n{\n" ${PUB_FUNC_RET[i]} $CLASS_NAME ${PUB_FUNC_NAME[i]} ${PUB_FUNC_PTYPE[i]} ${PUB_FUNC_PNAME[i]} >> $FILE_CPP
		fi
		if [[ ${PUB_FUNC_PNAME[i]} != "void" && ${PUB_FUNC_PNAME[i]} != "" && ${PUB_FUNC_PNAME[i]} != " " ]]; then
			printf "	(void)%s;\n" ${PUB_FUNC_PNAME[i]} >> $FILE_CPP
		fi
		printf "	std::cout << %s << \"%s called\" << C_RES << std::endl;\n" $PUB_FUNC_COLOR ${PUB_FUNC_NAME[i]} >> $FILE_CPP
		printf "	return ;\n}\n\n" >> $FILE_CPP
	fi
done

#_____________________ DECLARE OSTREAM OPERATOR _____________________#

if [[ $OVERLOAD_OSTREAM == 1 ]]; then

printf "// overload de <<\n" >> $FILE_CPP
printf "std::ostream &operator<<(std::ostream &os, const %s & src)" $CLASS_NAME >> $FILE_CPP
printf "\n{\n" >> $FILE_CPP
printf "	os << src.get%s();\n" `toCamel ${OSTREAM}`>> $FILE_CPP
printf "	return (os);\n}\n\n" >> $FILE_CPP
fi

fi # CPP CONSTRUCTION

#____________________________________________________________#
#_____________________ MAIN CONSTRUCTION ____________________#
#____________________________________________________________#

if [[ $MAIN == 1 ]]; then
# if [[ $INHERIT_FROM != "" ]]; then
# 	printf "# include \"%s.hpp\"\n" $INHERIT_FROM > $FILE_MAIN
# fi
printf "# include \"%s.hpp\"\n" $CLASS_NAME > $FILE_MAIN
for i in "${!ADD_TO_MAKEFILE[@]}"; do
	printf "# include \"%s.hpp\"\n" ${ADD_TO_MAKEFILE[i]} >> $FILE_MAIN
done

printf "
int main(void)
{
	%s a;
	%s b(a);
	%s c;
	c = b;\n"  $CLASS_NAME $CLASS_NAME $CLASS_NAME >> $FILE_MAIN
	if [[ $OVERLOAD_OSTREAM == 1 ]]; then
		printf "	std::cout << a << std::endl;
	std::cout << b << std::endl;
	std::cout << c << std::endl;\n" >> $FILE_MAIN
	fi
printf "\n	return 0;\n}\n\n" >> $FILE_MAIN
fi

#____________________________________________________________#
#___________________ MAKEFILE CONSTRUCTION __________________#
#____________________________________________________________#

if [[ $MAKEFILE == 1 ]]; then
FILE_MAKEFILE+="Makefile"

printf "
NAME		= 	%s

CC			= 	clang++

CFLAGS		= 	-Wall -Wextra -Werror -std=c++98 -g3

SRCS		=	%s \\
" ${CLASS_NAME,,} ${FILE_MAIN} > $FILE_MAKEFILE
printf "				%s \\
" ${FILE_CPP} >> $FILE_MAKEFILE
if [[ $INHERIT_FROM != "" ]]; then
	printf "				%s.cpp \\
" ${INHERIT_FROM} >> $FILE_MAKEFILE
fi
for i in "${!ADD_TO_MAKEFILE[@]}"; do
	printf "				%s.cpp \\
" ${ADD_TO_MAKEFILE[i]} >> $FILE_MAKEFILE
done
printf "
OBJS		=	\$(SRCS:.cpp=.o)

.cpp.o:
			\$(CC) \$(CFLAGS) -c \$< -o \$(<:.cpp=.o)

\$(NAME): \$(OBJS)
			\$(CC) \$(CFLAGS) \$(OBJS) -o \$(NAME)

all: \$(NAME)

clean:
		@	rm -rf \$(OBJS)

fclean:	clean
		@	rm -rf \$(NAME)

re: fclean
	make -j

fsan: \$(OBJS)
	\$(CC) \$(CFLAGS) \$(OBJS) -fsanitize=address -g3 -o \$(NAME)

ffsan: fclean
	make fsan -j

.PHONY: all clean fclean re fsan ffsan
" >> $FILE_MAKEFILE
fi

#____________________________________________________________#
#___________________ MAKEFILE CONSTRUCTION __________________#
#____________________________________________________________#

if [[ $COLOR == 1 ]]; then
FILE_COLOR+="color.hpp"

printf "#ifndef COLOR_HPP
# define COLOR_HPP

# define BLACK 		\"\\033[30m\"
# define RED 		\"\\033[31m\"
# define GREEN		\"\\033[32m\"
# define YELLOW		\"\\033[33m\"
# define BLUE		\"\\033[34m\"
# define MAGENTA	\"\\033[35m\"
# define CYAN		\"\\033[36m\"
# define WHITE		\"\\033[37m\"
# define GREY		\"\\033[90m\"
# define C_RES		\"\\033[0m\"

# define RED_B		\"\\033[31;01m\"
# define WHITE_B	\"\\033[37;01m\"
# define GREY_B		\"\\033[90;01m\"
# define GREEN_B	\"\\033[32;01m\"

# define COLOR(id)	\"\\033[38;5;\"#id\"m\"
# define CORAIL		COLOR(168)
# define GREEN_TREE	COLOR(106)
# define BROWN		COLOR(137)
# define SKY_BLUE	COLOR(69)
# define ORANGE		COLOR(130)

#endif" > $FILE_COLOR
fi

IFS="$OLD_IFS"
#