#ifndef CURE_HPP
# define CURE_HPP

# include <iostream>
# include <string>
# include <sstream>
# include "color.hpp"
# include "AMateria.hpp"

class AMateria;
class ICharacter;

class Cure : public AMateria
{
	protected:

	public:
		Cure();
		Cure(std::string const & type);
		Cure(const Cure & src);
		virtual ~Cure();

		Cure *		clone(void);
		void		use(ICharacter & target);

		Cure			&operator=(const Cure & src);
};

std::ostream	&operator<<(std::ostream & os, const Cure & src);

#endif
