# include "C.hpp"

// Default constructor
C::C(void)
{
	std::cout << GREY << "C creation..." << C_RES << std::endl;
	return ;
}

// Copy constructor
C::C(const C & src)
{
	std::cout << GREY << "C creation..." << C_RES << std::endl;
	*this = src;
	return;
}

// Destructor
C::~C(void)
{
	std::cout << GREY << "C destruction..." << C_RES << std::endl;
	return;
}

// Cssignation operator
C &	C::operator=(const C& rhs)
{
	std::cout << GREY << "C Cssignation operator called" << C_RES << std::endl;
	if (this != &rhs)
	{
	}
	return (*this);
}
