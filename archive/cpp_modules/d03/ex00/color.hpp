#ifndef COLOR_HPP
# define COLOR_HPP

# define BLACK 		"\033[30m"
# define RED 		"\033[31m"
# define GREEN		"\033[32m"
# define YELLOW		"\033[33m"
# define BLUE		"\033[34m"
# define MAGENTA	"\033[35m"
# define CYAN		"\033[36m"
# define WHITE		"\033[37m"
# define GREY		"\033[90m"
# define BLUE_ID	69
// # define COLOR(id)	#id
// # define COLOR(id)	"\033[38;5;"#id"m"
# define COLOR(id)	"\033[38;5;"#id"m"
# define C_RES		"\033[0m"
# define CORAIL		COLOR(168)
# define GREEN_TREE		COLOR(106)
# define BROWN		COLOR(137)

#endif