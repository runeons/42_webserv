#ifndef SHEEP_HPP
# define SHEEP_HPP

# include <iostream>
# include <string>
# include <sstream>
# include "color.hpp"
# include "Victim.hpp"

class Sheep : public Victim
{
	private:
		Sheep();

	public:
		Sheep(std::string);
		Sheep(const Sheep & src);
		virtual ~Sheep();

		Sheep			&operator=(const Sheep & src);
};

std::ostream	&operator<<(std::ostream & os, const Sheep & src);

#endif
