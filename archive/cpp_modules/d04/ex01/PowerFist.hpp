#ifndef POWERFIST_HPP
# define POWERFIST_HPP

# include <iostream>
# include <string>
# include <sstream>
# include "color.hpp"
# include "AWeapon.hpp"

class PowerFist : public AWeapon
{
	private:
		PowerFist(std::string const & name, int apcost, int damage);

	public:
		PowerFist();
		PowerFist(const PowerFist & src);
		virtual ~PowerFist();

		void	attack(void) const;

		PowerFist		&operator=(const PowerFist & src);
};

std::ostream	&operator<<(std::ostream & os, const PowerFist & src);

#endif
