#include "HumanB.hpp"

HumanB::HumanB(std::string name) : _name(name)
{
	// std::cout << GREEN << "Appel au constructeur d'un humain B nommé " << this->_name << C_RES << std::endl;
	return ;
}

HumanB::~HumanB(void)
{
	// std::cout << RED << "Appel au constructeur d'un humain B nommé " << this->_name << " avec " << this->_weapon->getType() << C_RES << std::endl;
	return ;
}

void	HumanB::setWeapon(Weapon& weapon)
{
	this->_weapon = &weapon;
}
void	HumanB::attack(void)
{
	std::cout << this->_name <<  "attacks with his " << this->_weapon->getType() << std::endl;
}
