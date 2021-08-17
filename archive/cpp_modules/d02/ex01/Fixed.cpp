# include "Fixed.hpp"

// Default constructor
Fixed::Fixed(void)
{
	std::cout << GREEN << "Default constructor called" << C_RES << std::endl;
	this->_rawBits = 0;
	return ;
}

// Copy constructor
Fixed::Fixed(const Fixed& src)
{
	std::cout << GREEN << "Copy constructor called" << C_RES << std::endl;
	*this = src;
	return ;
}

// Parametric constructor I
Fixed::Fixed(int n)
{
	std::cout << GREEN << "Int constructor called" << C_RES << std::endl;

	// on decale les bits de 8 a gauche <=> decaler la virgule de 8 a droite
	// n << this->_fracBits equivaut a mutiplier par 2, 8 fois, donc mult par 2 ^ 8 = 256
	this->setRawBits(n << this->_fractBits);
	return ;
}

// Parametric constructor II
Fixed::Fixed(float f)
{
	std::cout << GREEN << "Float constructor called" << C_RES << std::endl;

	// on mutiplie encore par 2 ^ _fracBits
	this->_rawBits = (int)(roundf(f * (1 << this->_fractBits)));

	return ;
}

// Destructor
Fixed::~Fixed(void)
{
	std::cout << RED << "Destructor called" << C_RES << std::endl;
	return ;
}

// Assignation operator
Fixed &	Fixed::operator=(const Fixed& rhs)
{
	std::cout << YELLOW << "Assignation operator called" << C_RES << std::endl;
	if (this != &rhs)
		this->_rawBits = rhs.getRawBits();
	return (*this);
}

// getter
int Fixed::getRawBits(void) const
{
	return (this->_rawBits);
}

// setter
void Fixed::setRawBits(int const raw)
{
	this->_rawBits = raw;
	return ;
}

float	Fixed::toFloat(void) const
{
	// je divise par 256 (2 ^ _fractBits)
	return ((float)this->_rawBits / (float)(1 << this->_fractBits));
}

int	Fixed::toInt(void) const
{
	// je divise a nouveau par 256 (2 ^ _fractBits) (decale de 8 bits a droite)
	return (this->_rawBits >> this->_fractBits);
}

// overload de <<
std::ostream &operator<<(std::ostream &os, const Fixed & src)
{
	os << src.toFloat();
	return (os);
}
