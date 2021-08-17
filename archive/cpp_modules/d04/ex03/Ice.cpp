# include "Ice.hpp"

// Default constructor
Ice::Ice(void)
{
	std::cout << GREY << "Ice creation..." << C_RES << std::endl;
	this->_type = "ice";
	this->_xp = 0;
	return ;
}

// Copy constructor
Ice::Ice(const Ice& src)
{
	std::cout << GREY << "Ice creation..." << C_RES << std::endl;
	*this = src;
	return;
}

// Parametric constructor (std::string const &)
Ice::Ice(std::string const & type) : AMateria(type)
{
	std::cout << GREY << this->_type << " Ice creation..." << C_RES << std::endl;
	this->_xp = 0;
	return ;
}

// Destructor
Ice::~Ice(void)
{
	std::cout << CORAIL << "Ice destruction..." << C_RES << std::endl;
	return;
}

/*
	While assigning a Materia to another, copying the type doesn’t make sense...
*/
// Assignation operator
Ice &	Ice::operator=(const Ice& rhs)
{
	std::cout << BROWN << "Ice Assignation operator called" << C_RES << std::endl;
	if (this != &rhs)
	{
		// this->_type = rhs.getType();
		this->_xp = rhs.getXp();
	}
	return (*this);
}

Ice * Ice::clone(void)
{
	std::cout << GREY << "clone called" << C_RES << std::endl;
	return (new Ice (*this));
}

/*
	Si target uses ice/cure : (name = target.getName())
	• Ice: "* shoots an ice bolt at NAME *"
	• Cure: "* heals NAME’s wounds *"
*/
void Ice::use(ICharacter& target)
{
	std::cout << SKY_BLUE << "* shoots an ice bolt at " << target.getName() << " *" << C_RES << std::endl;
	this->_xp += 10;
	std::cout << GREY << this->getType() << " now has " << this->getXp() << " XP" << C_RES << std::endl;
	return ;
}

// overload de <<
std::ostream &operator<<(std::ostream &os, const Ice & src)
{
	os << src.getType();
	return (os);
}
