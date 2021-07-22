#ifndef ASSAULTTERMINATOR_HPP
# define ASSAULTTERMINATOR_HPP

# include <iostream>
# include <string>
# include <sstream>
# include "color.hpp"
# include "ISpaceMarine.hpp"

class AssaultTerminator : public ISpaceMarine
{
	private:

	public:
		AssaultTerminator();
		AssaultTerminator(const AssaultTerminator & src);
		virtual ~AssaultTerminator();


		ISpaceMarine * clone(void) const;
		void	battleCry(void) const;
		void	rangedAttack(void) const;
		void	meleeAttack(void) const;
		std::string	getAddress(void) const;

		AssaultTerminator&operator=(const AssaultTerminator & src);
};

std::ostream	&operator<<(std::ostream & os, const AssaultTerminator & src);

#endif
