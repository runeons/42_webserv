#ifndef WEAPON_HPP
# define WEAPON_HPP
# include <iostream>
# include <iomanip>
# include <sstream>

# define BLACK 		"\033[30m"
# define RED 		"\033[31m"
# define GREEN		"\033[32m"
# define YELLOW		"\033[33m"
# define BLUE		"\033[34m"
# define MAGENTA	"\033[35m"
# define CYAN		"\033[36m"
# define WHITE		"\033[37m"
# define GREY		"\033[90m"
# define C_RES		"\033[0m"

// DECLARATION

class Weapon
{
	private:
		std::string	_type;
	public:
		std::string	get_type(void);
		std::string	const & getType(void);
		void 		setType(std::string type);

		Weapon(std::string type);
		Weapon();
		~Weapon();
};
#endif