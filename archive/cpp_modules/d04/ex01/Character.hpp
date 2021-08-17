#ifndef CHARACTER_HPP
# define CHARACTER_HPP

# include <iostream>
# include <string>
# include <sstream>
# include "color.hpp"
# include "AWeapon.hpp"
# include "Enemy.hpp"

class Character
{
	private:
		std::string	_name;
		int			_ap;
		int			_max_ap;
		AWeapon * 	_weapon;


	public:
		Character();
		Character(std::string const &);
		Character(const Character & src);
		~Character();

		std::string	getName(void) const;
		void		setName(const std::string name);
		int			getAp(void) const;
		void		setAp(const int ap);
		AWeapon * 	getWeapon(void) const;
		void		setWeapon(AWeapon * weapon);

		void		recoverAP(void);
		void		equip(AWeapon * weapon);
		void		attack(Enemy * enemy);

		Character	&operator=(const Character & src);
};

std::ostream	&operator<<(std::ostream & os, const Character & src);

#endif
