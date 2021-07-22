#ifndef NINJATRAP_HPP
# define NINJATRAP_HPP

# include <iostream>
# include <string>
# include <sstream>
# include "color.hpp"
# include "ClapTrap.hpp"
# include "FragTrap.hpp"
# include "ScavTrap.hpp"

class NinjaTrap : virtual public ClapTrap
{
	private:


	public:
		NinjaTrap();
		NinjaTrap(std::string);
		NinjaTrap(const NinjaTrap & src);
		~NinjaTrap();

		int	ninjaShoebox(const ClapTrap & claptrap);
		int	ninjaShoebox(const FragTrap & fragtrap);
		int	ninjaShoebox(const ScavTrap & scavtrap);
		int	ninjaShoebox(const NinjaTrap & ninjatrap);
};

#endif
