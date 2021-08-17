# include "D.hpp"

// Default constructor
D::D(void)
{
	std::cout << GREY << "D creation..." << C_RES << std::endl;
	return ;
}

// Dopy constructor
D::D(const D & src)
{
	std::cout << GREY << "D creation..." << C_RES << std::endl;
	*this = src;
	return;
}

// Destructor
D::~D(void)
{
	std::cout << GREY << "D destruction..." << C_RES << std::endl;
	return;
}

// Dssignation operator
D &	D::operator=(const D& rhs)
{
	std::cout << GREY << "D Dssignation operator called" << C_RES << std::endl;
	if (this != &rhs)
	{
	}
	return (*this);
}
