# include "Sheep.hpp"

// Default constructor
Sheep::Sheep(void)
{
	std::cout << GREEN_TREE << "A simple sheep is born." << C_RES << std::endl;
	return ;
}

// Copy constructor
Sheep::Sheep(const Sheep& src)
{
	std::cout << GREEN_TREE << "A simple sheep is born." << C_RES << std::endl;
	*this = src;
	return;
}

// Parametric constructor (std::string)
Sheep::Sheep(std::string name) : Victim(name)
{
	this->_polym_msg = "a bear";
	std::cout << GREEN_TREE << "A simple sheep is born." << C_RES << std::endl;
	return ;
}

// Destructor
Sheep::~Sheep(void)
{
	std::cout << CORAIL << "Sheep death...." << C_RES << std::endl;
	return;
}

// Assignation operator
Sheep &	Sheep::operator=(const Sheep& rhs)
{
	std::cout << BROWN << "Assignation operator called" << C_RES << std::endl;
	if (this != &rhs)
	{
		this->_name = rhs.getName();
	}
	return (*this);
}

// overload de <<
std::ostream &operator<<(std::ostream &os, const Sheep & src)
{
	os << src.introduce();
	return (os);
}
