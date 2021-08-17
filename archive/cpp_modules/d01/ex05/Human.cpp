#include "Human.hpp"

Human::Human(void)
{
	// std::cout << GREEN << "Appel au constructeur d'un humain " << this->identify() << C_RES << std::endl;
	return ;
}

Human::~Human(void)
{
	// std::cout << RED << "Appel au destructeur d'un humain " << this->identify() << C_RES << std::endl;
	return ;
}

Brain const & Human::getBrain() const
{
	return (this->_brain);
}

std::string	Human::identify(void) const
{
	return (this->_brain.identify());
}

