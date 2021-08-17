# include "Fixed.hpp"

// Constructeur par défaut
Fixed::Fixed(void)
{
	std::cout << GREEN << "Default constructor called" << C_RES << std::endl;
	this->_rawBits = 0;
	return ;
}

// Constructeur par copie
Fixed::Fixed(const Fixed& src)
{
	std::cout << GREEN << "Copy constructor called" << C_RES << std::endl;

	*this = src;
	return ;
}

// Destructeur éventuellement virtuel
Fixed::~Fixed(void)
{
	std::cout << RED << "Destructor called" << C_RES << std::endl;
	return ;
}

// Operateur d'affectation
Fixed &	Fixed::operator=(const Fixed& rhs)
{
	std::cout << YELLOW << "Assignation operator called" << C_RES << std::endl;
	if (this != &rhs)
		this->_rawBits = rhs.getRawBits();
	return (*this);
}

// renvoie la valeur brute du nombre à point fixe
int Fixed::getRawBits(void) const
{
	std::cout << GREY << "getRawBits member function called" << C_RES << std::endl;
	return (this->_rawBits);
}

// set la valeur du nombre à point fixe
void Fixed::setRawBits(int const raw)
{
	std::cout << GREY << "setRawBits member function called" << C_RES << std::endl;
	this->_rawBits = raw;
	return ;
}

/*
// overload de <<
std::ostream &operator<<(std::ostream &o, const Fixed & src)
{
	o << "The value of number is : " << src.getRawBits();
	return (o);
}
*/
