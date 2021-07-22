#ifndef AWEAPON_HPP
# define AWEAPON_HPP

# include <iostream>
# include <string>
# include <sstream>
# include "color.hpp"

class AWeapon
{
	protected:
		std::string	_name;
		int			_apcost;
		int			_damage;
		std::string	_attack_msg;

	public:
		AWeapon();
		AWeapon(std::string const & name, int apcost, int damage);
		AWeapon(const AWeapon & src);
		virtual ~AWeapon();

		std::string getName(void) const;
		void		setName(const std::string name);
		int			getApcost(void) const;
		void		setApcost(const int apcost);
		int			getDamage(void) const;
		void		setDamage(const int damage);
		std::string	getAttackMsg(void) const;
		void		setAttackMsg(const std::string attack_msg);

		virtual void	attack(void) const = 0;

		AWeapon		&operator=(const AWeapon & src);
};

std::ostream	&operator<<(std::ostream & os, const AWeapon & src);

#endif
