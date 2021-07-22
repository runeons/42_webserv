# include "B.hpp"

// Default constructor
B::B(void)
{
	std::cout << GREY << "B creation..." << C_RES << std::endl;
	return ;
}

// Copy constructor
B::B(const B & src)
{
	std::cout << GREY << "B creation..." << C_RES << std::endl;
	*this = src;
	return;
}

// Destructor
B::~B(void)
{
	std::cout << GREY << "B destruction..." << C_RES << std::endl;
	return;
}

// Bssignation operator
B &	B::operator=(const B& rhs)
{
	std::cout << GREY << "B Bssignation operator called" << C_RES << std::endl;
	if (this != &rhs)
	{
	}
	return (*this);
}
