#ifndef CHARACTER_HPP
# define CHARACTER_HPP

# include <iostream>
# include <string>
# include <sstream>
# include "color.hpp"
# include "ICharacter.hpp"

class Character : public ICharacter
{
	private:
		Character();
		std::string	_name;
		AMateria *	_inventory[4];

	public:
		Character(std::string name);
		Character(const Character & src);
		virtual ~Character();

		std::string	const &	getName(void) const;

		void		equip(AMateria* m);
		void		unequip(int idx);
		void		use(int idx, ICharacter & target);
		int			countInventory(void) const;
		std::string		getAddress(void) const;
		std::string		getNameAddress(void) const;
		std::string		getInvAddress(void) const;
		std::string		getFirstInvAddress(void) const;

		Character	&operator=(const Character & src);
};

std::ostream	&operator<<(std::ostream & os, const Character & src);

#endif
