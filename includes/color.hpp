#ifndef COLOR_HPP
# define COLOR_HPP

# define BLACK 		"[30m"
# define RED 		"[31m"
# define GREEN		"[32m"
# define YELLOW		"[33m"
# define BLUE		"[34m"
# define MAGENTA	"[35m"
# define CYAN		"[36m"
# define WHITE		"[37m"
# define GREY		"[90m"

# define RED_B		"[31;01m"
# define WHITE_B	"[37;01m"
# define GREY_B		"[90;01m"
# define GREEN_B	"[32;01m"

# define COLOR(id)	"[38;5;"#id"m"
# define CORAIL		COLOR(168)
# define GREEN_TREE	COLOR(106)
# define BROWN		COLOR(137)
# define SKY_BLUE	COLOR(69)
# define ORANGE		COLOR(130)

# define C_G_BLACK 		"\033[30;01m"
# define C_G_RED 		"\033[31;01m"
# define C_G_GREEN		"\033[32;01m"
# define C_G_YELLOW		"\033[33;01m"
# define C_G_BLUE		"\033[34;01m"
# define C_G_MAGENTA	"\033[35;01m"
# define C_G_CYAN		"\033[36;01m"
# define C_G_WHITE		"\033[37;01m"
# define C_G_GRAY		"\033[90;01m"
# define C_RES			"\033[0m"

#endif