#ifndef HUMANA_HPP
# define HUMANA_HPP
# include "Weapon.hpp"

// DECLARATION
class HumanA
{
	private:
		std::string _name;
		Weapon&		_weapon;
	public:
		void		attack(void);

		HumanA(std::string name, Weapon& weapon);
		~HumanA();
};
#endif