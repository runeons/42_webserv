#ifndef SUPERMUTANT_HPP
# define SUPERMUTANT_HPP

# include <iostream>
# include <string>
# include <sstream>
# include "color.hpp"
# include "Enemy.hpp"

class SuperMutant : public Enemy
{
	private:
		SuperMutant(int hp, std::string const & type);

	public:
		SuperMutant();
		SuperMutant(const SuperMutant & src);
		virtual ~SuperMutant();

		virtual void	takeDamage(int damage);

		SuperMutant		&operator=(const SuperMutant & src);
};

std::ostream	&operator<<(std::ostream & os, const SuperMutant & src);

#endif
