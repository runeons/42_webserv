# include "AMateria.hpp"

// Default constructor
AMateria::AMateria(void)
{
	std::cout << GREY << "AMateria creation..." << C_RES << std::endl;
	this->_type = "N/A";
	this->_xp = 0;
	return ;
}

// Copy constructor
AMateria::AMateria(const AMateria& src)
{
	std::cout << GREY << "AMateria creation..." << C_RES << std::endl;
	*this = src;
	return;
}

// Parametric constructor (std::string const &)
AMateria::AMateria(std::string const & type) : _type(type)
{
	std::cout << GREY << this->_type << " AMateria creation..." << C_RES << std::endl;
	this->_xp = 0;
	return ;
}

// Destructor
AMateria::~AMateria(void)
{
	std::cout << CORAIL << "AMateria destruction..." << C_RES << std::endl;
	return;
}

// Assignation operator
AMateria &	AMateria::operator=(const AMateria& rhs)
{
	std::cout << BROWN << "AMateria Assignation operator called" << C_RES << std::endl;
	if (this != &rhs)
	{
		this->_type = rhs.getType();
		this->_xp = rhs.getXp();
	}
	return (*this);
}

// getters and setters (non static attributes)
std::string const & AMateria::getType(void) const
{
	return (this->_type);
}

unsigned int AMateria::getXp(void) const
{
	return (this->_xp);
}

void AMateria::use(ICharacter& target)
{
	(void)target;
	std::cout << RED << "AMateria use called" << C_RES << std::endl;
	this->_xp += 10;
	return ;
}

// overload de <<
std::ostream &operator<<(std::ostream &os, const AMateria & src)
{
	os << src.getType();
	return (os);
}

