# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsantoni <tsantoni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/22 12:04:08 by tsantoni          #+#    #+#              #
#    Updated: 2021/07/22 12:09:39 by tharchen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= 	webserv

CC			= 	clang++

CFLAGS		= 	-Wall -Wextra -Werror -std=c++98 -g3

SRCS_REQUESTPARSER	=	\
					RequestParser/RequestParser.class.cpp \
					RequestParser/RequestParser.cd.class.cpp \
					RequestParser/RequestParser.gs.class.cpp \
					RequestParser/RequestParser.ovop.class.cpp \

SRCS		=	main.cpp \
				Server.cpp \
				Config.cpp \
				Client.cpp \
				$(SRCS_REQUESTPARSER) \

OBJS		=	$(SRCS:.cpp=.o)

.cpp.o:
			$(CC) $(CFLAGS) -c $< -o $(<:.cpp=.o)

$(NAME): $(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
		@	rm -rf $(OBJS)

fclean:	clean
		@	rm -rf $(NAME)

re: fclean
	make -j

fsan: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -fsanitize=address -g3 -o $(NAME)

ffsan: fclean
	make fsan -j

.PHONY: all clean fclean re fsan ffsan
