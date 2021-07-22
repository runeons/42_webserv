
NAME		= 	phonebook

CC			= 	clang++

CFLAGS		= 	-Wall -Wextra -Werror -std=c++98

SRCS		=	./srcs/phonebook_main.cpp \
				./srcs/phonebook_add.cpp \
				./srcs/phonebook_autofill.cpp \
				./srcs/phonebook_search_del.cpp \
				./srcs/Contact_class.cpp

INCS		=	./includes/phonebook.hpp \
				./includes/Contact_class.hpp

INC_DIR		=	./includes/

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
