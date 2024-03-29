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
FLAGS					=	-Wall -Wextra -Werror -std=c++98 -Ofast -g3
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
							webserv.hpp \
							ConfigParser.hpp \
							0_Config.hpp \
							0_Location.hpp \
							1_Server.hpp \
							2_Client.hpp \
							3_RequestParser.hpp \
							4_Response.hpp \
							5_Cgi.hpp \
							Exceptions.hpp \
							color.hpp \
							utils.hpp \

# *** SRCS ******************************************************************* #

SRCS_DIR				=	./srcs/

SRCS_REQUESTPARSER		=	\
							3_RequestParser/RequestParser.cd.class.cpp \
							3_RequestParser/RequestParser.class.cpp \
							3_RequestParser/RequestParser.gs.class.cpp \
							3_RequestParser/RequestParser.lexer.class.cpp \
							3_RequestParser/RequestParser.ovop.class.cpp \
							3_RequestParser/RequestParser.parser.class.cpp \
							3_RequestParser/RequestParser.maps.class.cpp \

SRCS_CONFIGPARSER		=	\
							ConfigParser/ConfigParser.cd.class.cpp \
							ConfigParser/ConfigParser.class.cpp \
							ConfigParser/ConfigParser.gs.class.cpp \
							ConfigParser/ConfigParser.lexer.class.cpp \
							ConfigParser/ConfigParser.ovop.class.cpp \
							ConfigParser/ConfigParser.parser.class.cpp \
							ConfigParser/ConfigParser.tokens.class.cpp \

SRCS_SERVER				=	\
							1_Server/Server_basics.cpp \
							1_Server/Server_class.cpp \

SRCS_CGI				=	\
							5_Cgi/Cgi_basics.cpp \
							5_Cgi/Cgi_class.cpp \
							5_Cgi/Cgi_init_map.cpp \

SRCS_CONFIG				=	\
							0_Config/Location/Location_basics.cpp \
							0_Config/Location/Location_class.cpp \
							0_Config/Config_basics.cpp \
							0_Config/Config_class.cpp \
							0_Config/Config_init_maps.cpp \

SRCS_CLIENT				=	\
							2_Client/Client_basics.cpp \
							2_Client/Client_class.cpp \

SRCS_RESPONSE			=	\
							4_Response/Response_basics.cpp \
							4_Response/Response_class.cpp \
							4_Response/Response_headers.cpp \
							4_Response/Response_init_maps.cpp \

SRCS_UTILS			=	\
							utils/utils.cpp \

SRCS_LIST				=	\
							main.cpp \
							$(SRCS_CONFIGPARSER) \
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
	@ $(CC) $(FLAGS) $(HDIR) $(OBJS) -o $(NAME)
	@ $(COMPILE_MSG)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.cpp
	@ mkdir -p $(dir $@)
	@ $(CC) $(FLAGS) $(HDIR) -c -o $@ $<
	@ $(COMPILE_MSG_OBJ)

clean:
	@ rm -f cmd_res
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
