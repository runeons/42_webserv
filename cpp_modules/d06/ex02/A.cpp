# include "A.hpp"

// Default constructor
A::A(void)
{
	std::cout << GREY << "A creation..." << C_RES << std::endl;
	return ;
}

// Copy constructor
A::A(const A & src)
{
	std::cout << GREY << "A creation..." << C_RES << std::endl;
	*this = src;
	return;
}

// Destructor
A::~A(void)
{
	std::cout << GREY << "A destruction..." << C_RES << std::endl;
	return;
}

// Assignation operator
A &	A::operator=(const A& rhs)
{
	std::cout << GREY << "A Assignation operator called" << C_RES << std::endl;
	if (this != &rhs)
	{
	}
	return (*this);
}
