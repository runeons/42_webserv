#ifndef FRAGTRAP_HPP
# define FRAGTRAP_HPP

# include <iostream>
# include <string>
# include <sstream>
# include <cstdlib>
# include "color.hpp"
# include "ClapTrap.hpp"

class FragTrap : virtual public ClapTrap
{
	private:

	public:
		FragTrap();
		FragTrap(std::string);
		FragTrap(const FragTrap & src);
		~FragTrap();

		int					ironyAttack(std::string const & target);
		int					britishAttack(std::string const & target);
		int					darkAttack(std::string const & target);
		int					embarrassingAttack(std::string const & target);
		int					sarcasmAttack(std::string const & target);
		int					vaulthunter_dot_exe(std::string const & target);
};

#endif
