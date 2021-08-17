#ifndef ISQUAD_HPP
# define ISQUAD_HPP

# include <iostream>
# include <string>
# include <sstream>
# include "color.hpp"
# include "ISpaceMarine.hpp"

class ISquad
{
	public:
		virtual ~ISquad() {}
		virtual int getCount() const = 0;
		virtual ISpaceMarine * getUnit(int) const = 0;
		virtual int push(ISpaceMarine *) = 0;
};

#endif