# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/22 13:24:55 by tharchen          #+#    #+#              #
#    Updated: 2021/07/22 13:59:59 by tharchen         ###   ########.fr        #
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

NAME					=	webserv

CC						=	clang++

FLAGS					=	-Wall -Wextra -Werror -std=c++98
FLAGSSAN				=	-fsanitize=address -g3

# *** PROJECT HEADER ********************************************************* #

HDIR					=	$(addprefix -I, $(HEADER_DIR))

HEAD					=	$(addprefix $(HEADER_DIR), $(HEADER))

HEADER_DIR				=	\
							./includes/

HEADER					=	\
							Client.hpp \
							Config.hpp \
							Exceptions.hpp \
							RequestParser.class.hpp \
							Server.hpp \
							color.hpp \
							webserv.hpp \

# *** SRCS ******************************************************************* #

SRCS_DIR				=	./srcs/

SRCS_REQUESTPARSER		=	\
							RequestParser/RequestParser.class.cpp \
							RequestParser/RequestParser.cd.class.cpp \
							RequestParser/RequestParser.gs.class.cpp \
							RequestParser/RequestParser.ovop.class.cpp \

SRCS_SERVER				=	\
							Server/Server.cpp \

SRCS_CONFIG				=	\
							Config/Config.cpp \

SRCS_CLIENT				=	\
							Client/Client.cpp \

SRCS_LIST				=	\
							main.cpp \
							$(SRCS_REQUESTPARSER) \
							$(SRCS_SERVER) \
							$(SRCS_CONFIG) \
							$(SRCS_CLIENT) \


SRCS					=	$(addprefix $(SRCS_DIR), $(SRCS_LIST))

# *** OBJS ******************************************************************* #

OBJS_DIR				=	./objs/

OBJS_LIST				=	$(patsubst %.cpp, %.o, $(SRCS_LIST))

OBJS					=	$(addprefix $(OBJS_DIR), $(OBJS_LIST))

# *** RULES ****************************************************************** #

.PHONY: all clean fclean re fsan ffsan

all: $(OBJS) $(SRCS) $(NAME)
	@ printf "\033[31m Program \033[32m%s : \033[34;01;03mCompilation \033[36m%-50s\033[0m\n" $(NAME) "done !"

$(NAME): $(OBJS) $(SRCS)
	@ $(CC) $(FLAGS) $(HDIR) $(OBJS) -o $(NAME)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.cpp
	@ mkdir -p $(dir $@)
	@ $(CC) $(FLAGS) $(HDIR) -c -o $@ $<
	@ printf "\033[31m Program \033[32m%s : \033[34;01;03mCompilation of \033[36m%-50s\033[0m\r" $(NAME) $(notdir $<)

clean:
	@ rm -rf $(OBJS_DIR)

fclean: clean
	@ rm -f $(NAME)
	@ rm -f $(NAME).dSYM

re: fclean
	@ make -j

fsan: $(OBJS) $(SRCS) $(NAME)
	@ $(CC) $(FLAGS) $(FLAGSSAN) $(HDIR) $(OBJS) -o $(NAME)
	@ printf "\033[31m Program \033[32m%s :\033[34;01;03m Compilation\033[33m in sanitizer mode \033[36m%-50s\033[0m\n" $(NAME) "done !"

ffsan: fclean
	@ make fsan -j

# **************************************************************************** #