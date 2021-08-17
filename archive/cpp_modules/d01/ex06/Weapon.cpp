#include "Weapon.hpp"

Weapon::Weapon(void) {
	// std::cout << GREEN << "Appel au constructeur d'une Weapon sans type" << C_RES << std::endl;
	return ;
}

Weapon::Weapon(std::string type) : _type(type) {
	// std::cout << GREEN << "Appel au constructeur d'une Weapon de type " << this->_type << C_RES << std::endl;
	return ;
}

Weapon::~Weapon(void) {
	// std::cout << RED << "Appel au destructeur d'une Weapon de type " << this->_type << C_RES << std::endl;
	return ;
}

void	Weapon::setType(std::string type)
{
	this->_type = type;
}

std::string	const & Weapon::getType(void)
{
	return (this->_type);
}
