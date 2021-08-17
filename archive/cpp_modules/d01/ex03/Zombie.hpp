#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP
# include <iostream>
# include <iomanip>

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

class Zombie
{
	private:
		std::string	_name;
		std::string	_type;
	public:
		std::string get_name(void);
		std::string get_type(void);
		void set_name(std::string name);
		void set_type(std::string type);
		void announce(void);

		Zombie(std::string name, std::string type);
		Zombie();
		~Zombie();
};
#endif