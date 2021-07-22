#ifndef PONY_HPP
# define PONY_HPP
# include <iostream>
# include <iomanip>
# include "color.hpp"

// DECLARATION

class Pony
{
	private:
		std::string	_name;
		std::string	_race;
		std::string	_speed;
	public:
		std::string get_name(void);
		std::string get_race(void);
		std::string get_speed(void);

		void set_name(std::string name);
		void set_race(std::string race);
		void set_speed(std::string speed);

		void	move_faster();
		void	move_slower();
		void	shout_speed();
		void	shout_new_speed();

		Pony(std::string name, std::string race, std::string speed);
		~Pony(void);
};
#endif