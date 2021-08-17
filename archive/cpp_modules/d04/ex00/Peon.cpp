# include "Peon.hpp"

// Default constructor
Peon::Peon(void)
{
	std::cout << GREEN_TREE << "Zog zog." << C_RES << std::endl;
	return ;
}

// Copy constructor
Peon::Peon(const Peon& src)
{
	std::cout << GREEN_TREE << "Zog zog." << C_RES << std::endl;
	*this = src;
	return;
}

// Parametric constructor (std::string)
Peon::Peon(std::string name) : Victim(name)
{
	this->_polym_msg = "a pink pony";
	std::cout << GREEN_TREE << "Zog zog." << C_RES << std::endl;
	return ;
}

// Destructor
Peon::~Peon(void)
{
	std::cout << CORAIL << "Bleuark..." << C_RES << std::endl;
	return;
}

// Assignation operator
Peon &	Peon::operator=(const Peon& rhs)
{
	std::cout << BROWN << "Assignation operator called" << C_RES << std::endl;
	if (this != &rhs)
	{
		this->_name = rhs.getName();
	}
	return (*this);
}

// overload de <<
std::ostream &operator<<(std::ostream &os, const Peon & src)
{
	os << src.introduce();
	return (os);
}
