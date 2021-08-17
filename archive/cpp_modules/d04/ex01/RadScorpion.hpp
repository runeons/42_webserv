#ifndef RADSCORPION_HPP
# define RADSCORPION_HPP

# include <iostream>
# include <string>
# include <sstream>
# include "color.hpp"
# include "Enemy.hpp"

class RadScorpion : public Enemy
{
	private:
		RadScorpion(int hp, std::string const & type);

	public:
		RadScorpion();
		RadScorpion(const RadScorpion & src);
		virtual ~RadScorpion();

		virtual void	takeDamage(int damage);

		RadScorpion		&operator=(const RadScorpion & src);
};

std::ostream	&operator<<(std::ostream & os, const RadScorpion & src);

#endif
