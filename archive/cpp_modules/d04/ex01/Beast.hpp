#ifndef BEAST_HPP
# define BEAST_HPP

# include <iostream>
# include <string>
# include <sstream>
# include "color.hpp"
# include "Enemy.hpp"

class Beast : public Enemy
{
	private:
		Beast(int hp, std::string const & type);

	public:
		Beast();
		Beast(const Beast & src);
		virtual ~Beast();

		virtual void	takeDamage(int damage);

		Beast		&operator=(const Beast & src);
};

std::ostream	&operator<<(std::ostream & os, const Beast & src);

#endif
