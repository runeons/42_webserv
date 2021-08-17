#ifndef SUPERTRAP_HPP
# define SUPERTRAP_HPP

# include <iostream>
# include <string>
# include <sstream>
# include "color.hpp"
# include "ClapTrap.hpp"
# include "FragTrap.hpp"
# include "NinjaTrap.hpp"

class SuperTrap : virtual public ClapTrap,  public FragTrap, public NinjaTrap
{
	private:


	public:
		SuperTrap();
		SuperTrap(std::string);
		SuperTrap(const SuperTrap & src);
		~SuperTrap();

		int rangedAttack(std::string const &target);
		int meleeAttack(std::string const &target);

};

#endif
