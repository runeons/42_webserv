#include "HumanA.hpp"

HumanA::HumanA(std::string name, Weapon& weapon) : _name(name), _weapon(weapon)
{
	// std::cout << GREEN << "Appel au constructeur d'un humain A nommé " << this->_name << " avec " << this->_weapon.getType() << C_RES << std::endl;
	return ;
}

HumanA::~HumanA(void)
{
	// std::cout << RED << "Appel au constructeur d'un humain A nommé " << this->_name << " avec " << this->_weapon.getType() << C_RES << std::endl;
	return ;
}

void	HumanA::attack(void)
{
	std::cout << this->_name <<  "attacks with his " << this->_weapon.getType() << std::endl;
}
