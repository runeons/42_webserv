#ifndef SORCERER_HPP
# define SORCERER_HPP

# include <iostream>
# include <string>
# include <sstream>
# include "color.hpp"
# include "Victim.hpp"

class Sorcerer
{
	private:
		Sorcerer();
		std::string	_name;
		std::string	_title;

	public:
		Sorcerer(std::string name, std::string title);
		Sorcerer(const Sorcerer & src);
		~Sorcerer();

		std::string	getName(void) const;
		void		setName(const std::string name);
		std::string	getTitle(void) const;
		void		setTitle(const std::string title);

		void		polymorph(Victim const & victim) const;
		std::string	introduce(void) const;

		Sorcerer	&operator=(const Sorcerer & src);
};

std::ostream	&operator<<(std::ostream & os, const Sorcerer & src);

#endif
