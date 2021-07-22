#include "Zombie.hpp"

Zombie::Zombie(std::string name, std::string type) : _name(name), _type(type) {
	// std::cout << GREEN << "Appel au constructeur de " << this->_name << C_RES << std::endl;
	return ;
}

Zombie::Zombie(void) {
	// std::cout << GREEN << "Appel au constructeur de (void) zombie" << C_RES << std::endl;
	return ;
}

Zombie::~Zombie(void) {
	std::cout << GREY << this->_name << " died." << C_RES << std::endl;
	return ;
}

void	Zombie::set_name(std::string name)
{
	this->_name = name;
}

std::string	Zombie::get_name(void)
{
	return (this->_name);
}

void	Zombie::set_type(std::string type)
{
	this->_type = type;
}

std::string	Zombie::get_type(void)
{
	return (this->_type);
}

void	Zombie::announce(void)
{
	if (this->get_type().length() == 0)
		std::cout << WHITE << "I am the zombie "<< this->get_name() << ", without any family...";
	else if (this->get_type() == "social")
		std::cout << GREEN << "I am the zombie "<< this->get_name() << ", part of the "<< this->get_type() << " family !";
	else if (this->get_type() == "toxic")
		std::cout << RED << "I am the zombie "<< this->get_name() << ", part of the "<< this->get_type() << " family !";
	else if (this->get_type() == "psychiatric")
		std::cout << YELLOW << "I am the zombie "<< this->get_name() << ", part of the "<< this->get_type() << " family !";
	else
		std::cout << ", part of the "<< this->get_type() << " family !";
	std::cout << C_RES << std::endl;
}