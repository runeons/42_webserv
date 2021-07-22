#ifndef PLASMARIFLE_HPP
# define PLASMARIFLE_HPP

# include <iostream>
# include <string>
# include <sstream>
# include "color.hpp"
# include "AWeapon.hpp"

class PlasmaRifle : public AWeapon
{
	private:
		PlasmaRifle(std::string const & name, int apcost, int damage);

	public:
		PlasmaRifle();
		PlasmaRifle(const PlasmaRifle & src);
		virtual ~PlasmaRifle();

		void	attack(void) const;

		PlasmaRifle		&operator=(const PlasmaRifle & src);
};

std::ostream	&operator<<(std::ostream & os, const PlasmaRifle & src);

#endif
