#include "Brain.hpp"

Brain::Brain(void) {
	// std::cout << GREEN << "Appel au constructeur d'un (void) cerveau " << this->identify() << C_RES << std::endl;
	return ;
}

Brain::~Brain(void) {
	// std::cout << RED << "Appel au destructeur d'un cerveau " << this->identify() << C_RES << std::endl;
	return ;
}

void	Brain::set_name(std::string name)
{
	this->_name = name;
}

std::string	Brain::get_name(void)
{
	return (this->_name);
}

std::string	Brain::identify(void) const
{
	std::stringstream address;

	address << this;
	return (address.str());
}