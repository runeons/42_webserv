#ifndef SCAVTRAP_HPP
# define SCAVTRAP_HPP

# include <iostream>
# include <string>
# include <sstream>
# include "color.hpp"
# include "ClapTrap.hpp"

class ScavTrap : public ClapTrap
{
	private:


	public:
		ScavTrap();
		ScavTrap(std::string);
		ScavTrap(const ScavTrap & src);
		~ScavTrap();

		void	challTreeClimb(std::string const & target);
		void	challPoemLearn(std::string const & target);
		void	challSongSing(std::string const & target);
		void	challengeNewcomer(std::string const & target);
};

#endif
