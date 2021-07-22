# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsantoni <tsantoni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/22 12:04:08 by tsantoni          #+#    #+#              #
#    Updated: 2021/07/22 12:39:22 by tharchen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= 	webserv

CC			= 	clang++

CFLAGS		= 	-Wall -Wextra -Werror -std=c++98 -g3

SRCS_DIR	=	./srcs

INCLUDES_DIR	=	./includes

SRCS_REQUESTPARSER	=	\
					$(SRCS_DIR)/RequestParser/RequestParser.class.cpp \
					$(SRCS_DIR)/RequestParser/RequestParser.cd.class.cpp \
					$(SRCS_DIR)/RequestParser/RequestParser.gs.class.cpp \
					$(SRCS_DIR)/RequestParser/RequestParser.ovop.class.cpp \

SRCS		=	$(SRCS_DIR)/main.cpp \
				$(SRCS_DIR)/Server/Server.cpp \
				$(SRCS_DIR)/Config/Config.cpp \
				$(SRCS_DIR)/Client/Client.cpp \
				$(SRCS_REQUESTPARSER) \

OBJS		=	$(SRCS:.cpp=.o)

.cpp.o:
			$(CC) $(CFLAGS) -I $(INCLUDES_DIR) -c $< -o $(<:.cpp=.o)

$(NAME): $(OBJS)
			$(CC) $(CFLAGS) -I $(INCLUDES_DIR) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	@	rm -rf $(OBJS)

fclean:	clean
	@	rm -rf $(NAME)
	@	rm -rf $(NAME).dSYM

re: fclean
	make -j

fsan: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -fsanitize=address -g3 -o $(NAME)

ffsan: fclean
	make fsan -j

.PHONY: all clean fclean re fsan ffsan
