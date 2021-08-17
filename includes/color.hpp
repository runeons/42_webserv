
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
# define LIGHT_BLUE	COLOR(39)
# define LIGHT_PINK	COLOR(170)
# define PINK		COLOR(164)
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

# define C_B_BLACK 		"\033[40m"
# define C_B_RED 		"\033[41m"
# define C_B_GREEN		"\033[42m"
# define C_B_YELLOW		"\033[43m"
# define C_B_BLUE		"\033[44m"
# define C_B_MAGENTA	"\033[45m"
# define C_B_CYAN		"\033[46m"
# define C_B_WHITE		"\033[47m"
# define C_B_GRAY		"\033[100m"

# define C_RES			"\033[0m"

# define MINUS_STR "----------------------------------------------------------------------------------------------------"
# define TEST "\033[36;01m(%s:%d:0) \033[31;01m%s\033[0m %.*s>\033[35;01m%d\033[0m\n", __FILE__, __LINE__, __FUNCTION__, (int)(70 - (strlen(__FUNCTION__) + strlen(__FILE__) + 3)), MINUS_STR, __LINE__

#endif