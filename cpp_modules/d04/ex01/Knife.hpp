#ifndef KNIFE_HPP
# define KNIFE_HPP

# include <iostream>
# include <string>
# include <sstream>
# include "color.hpp"
# include "AWeapon.hpp"

class Knife : public AWeapon
{
	private:
		Knife(std::string const & name, int apcost, int damage);

	public:
		Knife();
		Knife(const Knife & src);
		virtual ~Knife();

		void	attack(void) const;

		Knife		&operator=(const Knife & src);
};

std::ostream	&operator<<(std::ostream & os, const Knife & src);

#endif
