#ifndef PEON_HPP
# define PEON_HPP

# include <iostream>
# include <string>
# include <sstream>
# include "color.hpp"
# include "Victim.hpp"

class Peon : public Victim
{
	private:
		Peon();

	public:
		Peon(std::string);
		Peon(const Peon & src);
		virtual ~Peon();

		Peon			&operator=(const Peon & src);

};

std::ostream	&operator<<(std::ostream & os, const Peon & src);

#endif
