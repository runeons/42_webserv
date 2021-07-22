#ifndef ICE_HPP
# define ICE_HPP

# include <iostream>
# include <string>
# include <sstream>
# include "color.hpp"
# include "AMateria.hpp"

class AMateria;
class ICharacter;

class Ice : public AMateria
{
	protected:

	public:
		Ice();
		Ice(std::string const & type);
		Ice(const Ice & src);
		virtual ~Ice();

		Ice *		clone(void);
		void		use(ICharacter & target);

		Ice			&operator=(const Ice & src);
};

std::ostream	&operator<<(std::ostream & os, const Ice & src);

#endif
