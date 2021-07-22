# include "Cat.hpp"

// Default constructor
Cat::Cat(void)
{
	std::cout << GREEN_TREE << "A grey cat is born." << C_RES << std::endl;
	return ;
}

// Copy constructor
Cat::Cat(const Cat& src)
{
	std::cout << GREEN_TREE << "A grey cat is born." << C_RES << std::endl;
	*this = src;
	return;
}

// Parametric constructor (std::string)
Cat::Cat(std::string name) : Victim(name)
{
	this->_polym_msg = "a dog";
	std::cout << GREEN_TREE << "A grey cat is born." << C_RES << std::endl;
	return ;
}

// Destructor
Cat::~Cat(void)
{
	std::cout << CORAIL << "Cat death...." << C_RES << std::endl;
	return;
}

// Assignation operator
Cat &	Cat::operator=(const Cat & rhs)
{
	std::cout << BROWN << "Assignation operator called" << C_RES << std::endl;
	if (this != &rhs)
	{
		this->_name = rhs.getName();
	}
	return (*this);
}

// overload de <<
std::ostream &operator<<(std::ostream &os, const Cat & src)
{
	os << src.introduce();
	return (os);
}
