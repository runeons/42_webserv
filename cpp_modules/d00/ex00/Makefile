
NAME		= 	megaphone

CC			= 	clang++

CFLAGS		= 	-Wall -Wextra -Werror -std=c++98

SRCS		=	megaphone.cpp

OBJS		=	$(SRCS:.cpp=.o)

.cpp.o:
			$(CC) $(CFLAGS) -c $< -o $(<:.cpp=.o)

$(NAME): $(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
			rm -rf $(OBJS)

fclean:	clean
			rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
