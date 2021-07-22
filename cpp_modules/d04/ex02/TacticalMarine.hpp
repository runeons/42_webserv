#ifndef TACTICALMARINE_HPP
# define TACTICALMARINE_HPP

# include <iostream>
# include <string>
# include <sstream>
# include "color.hpp"
# include "ISpaceMarine.hpp"

class TacticalMarine : public ISpaceMarine
{
	private:

	public:
		TacticalMarine();
		TacticalMarine(const TacticalMarine & src);
		virtual ~TacticalMarine();


		ISpaceMarine * clone(void) const;
		void	battleCry(void) const;
		void	rangedAttack(void) const;
		void	meleeAttack(void) const;
		std::string	getAddress(void) const;

		TacticalMarine&operator=(const TacticalMarine & src);
};

std::ostream	&operator<<(std::ostream & os, const TacticalMarine & src);

#endif
