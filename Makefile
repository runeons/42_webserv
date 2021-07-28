# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/22 13:24:55 by tharchen          #+#    #+#              #
#    Updated: 2021/07/28 11:04:48 by tsantoni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                                                              #
#    Makefile project webserv by tharchen and tsantoni                         #
#                                                                              #
#    rules:                                                                    #
#                                                                              #
#    make           : make the project                                         #
#    make all       : make the project                                         #
#    make webserv   : make the project                                         #
#    make clean     : clean object files (.o)                                  #
#    make fclean    : clean object files (.o) and remove webserv bin           #
#    make re        : run rules fclean then all                                #
#    make run       : run re then run ./$(NAME)                                #
#                                                                              #
# *** NAME - CC - FLAGS ****************************************************** #

# COMPILE_MODE:  0 = normal | 1 = fsanitize
COMPILE_MODE			=	0

_NAME					=	webserv
_FNAME					=	webserv.fsanitize
_FLAGS					=	-Wall -Wextra -Werror -std=c++98 -fsanitize=address -g3

ifeq ($(COMPILE_MODE), 0)
NAME					=	webserv
FLAGS					=	-Wall -Wextra -Werror -std=c++98 -Ofast
COMPILE_MSG				=	printf "\033[31m Program \033[32m%s : \033[34;01;03mCompilation \033[36m%-50s\033[0m\n" $(NAME) "done !"
COMPILE_MSG_OBJ			=	printf "\033[31m Program \033[32m%s : \033[34;01;03mCompilation of \033[36m%-50s\033[0m\r" $(NAME) $(notdir $<)
else
NAME					=	webserv.fsanitize
FLAGS					=	-Wall -Wextra -Werror -std=c++98 -fsanitize=address -g3
COMPILE_MSG				=	printf "\033[31m Program \033[32m%s : \033[34;01;03mCompilation\033[33m in sanitizer mode \033[36m%-50s\033[0m\n" $(NAME) "done !"
COMPILE_MSG_OBJ			=	printf "\033[31m Program \033[32m%s : \033[34;01;03mCompilation\033[33m in sanitizer mode \033[34;01;of \033[36m%-50s\033[0m\r" $(NAME) $(notdir $<)
endif

CC						=	clang++

# *** PROJECT HEADER ********************************************************* #

HDIR					=	$(addprefix -I, $(HEADER_DIR))

HEAD					=	$(addprefix $(HEADER_DIR), $(HEADER))

HEADER_DIR				=	\
							./includes/

HEADER					=	\
							Client.hpp \
							Cgi.hpp \
							Response.hpp \
							Config.hpp \
							Exceptions.hpp \
							RequestParser.class.hpp \
							Server.hpp \
							color.hpp \
							utils.hpp \
							webserv.hpp \

# *** SRCS ******************************************************************* #

SRCS_DIR				=	./srcs/

SRCS_REQUESTPARSER		=	\
							RequestParser/RequestParser.cd.class.cpp \
							RequestParser/RequestParser.class.cpp \
							RequestParser/RequestParser.gs.class.cpp \
							RequestParser/RequestParser.lexer.class.cpp \
							RequestParser/RequestParser.ovop.class.cpp \
							RequestParser/RequestParser.parser.class.cpp \
							RequestParser/RequestParser.maps.class.cpp \

SRCS_SERVER				=	\
							Server/Server_basics.cpp \
							Server/Server_class.cpp \

SRCS_CGI				=	\
							Cgi/Cgi_basics.cpp \
							Cgi/Cgi_class.cpp \
							Cgi/Cgi_init_map.cpp \

SRCS_CONFIG				=	\
							Config/Config_basics.cpp \
							Config/Config_class.cpp \

SRCS_CLIENT				=	\
							Client/Client_basics.cpp \
							Client/Client_class.cpp \

SRCS_RESPONSE			=	\
							Response/Response_basics.cpp \
							Response/Response_class.cpp \
							Response/Response_headers.cpp \
							Response/Response_init_maps.cpp \

SRCS_UTILS			=	\
							utils/utils.cpp \

SRCS_LIST				=	\
							main.cpp \
							$(SRCS_REQUESTPARSER) \
							$(SRCS_SERVER) \
							$(SRCS_CGI) \
							$(SRCS_CONFIG) \
							$(SRCS_CLIENT) \
							$(SRCS_RESPONSE) \
							$(SRCS_UTILS) \


SRCS					=	$(addprefix $(SRCS_DIR), $(SRCS_LIST))

# *** OBJS ******************************************************************* #

OBJS_DIR				=	./objs/

OBJS_LIST				=	$(patsubst %.cpp, %.o, $(SRCS_LIST))

OBJS					=	$(addprefix $(OBJS_DIR), $(OBJS_LIST))

# *** RULES ****************************************************************** #

.PHONY: all clean fclean re fsan ffsan

all: $(OBJS) $(SRCS) $(NAME)

$(NAME): $(OBJS) $(SRCS)
	@ $(CC) $(_FLAGS) $(HDIR) $(OBJS) -o $(NAME)
	@ $(COMPILE_MSG)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.cpp
	@ mkdir -p $(dir $@)
	@ $(CC) $(FLAGS) $(HDIR) -c -o $@ $<
	@ $(COMPILE_MSG_OBJ)

clean:
	@ rm -rf $(OBJS_DIR)

fclean: clean
	@ rm -f $(_NAME)
	@ rm -f $(_NAME).dSYM
	@ rm -f $(_FNAME)
	@ rm -f $(_FNAME).dSYM

re: fclean
	@ make -j

fsan:
	@ make COMPILE_MODE=1 -j

ffsan: fclean
	@ make fsan -j

# **************************************************************************** #
