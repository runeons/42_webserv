#ifndef AMATERIA_HPP
# define AMATERIA_HPP

# include <iostream>
# include <string>
# include <sstream>
# include "color.hpp"
# include "ICharacter.hpp"

class ICharacter;

class AMateria
{
	protected:
		std::string			_type;
		unsigned int		_xp;

	public:
		AMateria();
		AMateria(std::string const & type);
		AMateria(const AMateria & src);
		virtual ~AMateria();

		std::string	const &	getType(void) const;
		unsigned int		getXp(void) const;

		virtual AMateria *	clone(void) = 0;
		virtual void		use(ICharacter & target);

		AMateria			&operator=(const AMateria & src);
};

std::ostream	&operator<<(std::ostream & os, const AMateria & src);

#endif
