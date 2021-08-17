# include "Cure.hpp"

// Default constructor
Cure::Cure(void)
{
	std::cout << GREY << "Cure creation..." << C_RES << std::endl;
	this->_type = "cure";
	this->_xp = 0;
	return ;
}

// Copy constructor
Cure::Cure(const Cure& src)
{
	std::cout << GREY << "Cure creation..." << C_RES << std::endl;
	*this = src;
	return;
}

// Parametric constructor (std::string const &)
Cure::Cure(std::string const & type) : AMateria(type)
{
	std::cout << GREY << this->_type << " Cure creation..." << C_RES << std::endl;
	this->_xp = 0;
	return ;
}

// Destructor
Cure::~Cure(void)
{
	std::cout << CORAIL << "Cure destruction..." << C_RES << std::endl;
	return;
}

// Assignation operator
/*
	While assigning a Materia to another, copying the type doesn’t make sense...
*/
Cure &	Cure::operator=(const Cure& rhs)
{
	std::cout << BROWN << "Cure Assignation operator called" << C_RES << std::endl;
	if (this != &rhs)
	{
		this->_type = rhs.getType();
		this->_xp = rhs.getXp();
	}
	return (*this);
}

Cure * Cure::clone(void)
{
	std::cout << GREY << "clone called" << C_RES << std::endl;
	return (new Cure (*this));
}

/*
	Si target uses ice/cure : (name = target.getName())
	• Cure: "* shoots an ice bolt at NAME *"
	• Cure: "* heals NAME’s wounds *"
*/
void Cure::use(ICharacter& target)
{
	std::cout << SKY_BLUE << "* heals " << target.getName() << "’s wounds *" << C_RES << std::endl;
	this->_xp += 10;
	std::cout << GREY << this->getType() << " now has " << this->getXp() << " XP" << C_RES << std::endl;
	return ;
}

// overload de <<
std::ostream &operator<<(std::ostream &os, const Cure & src)
{
	os << src.getType();
	return (os);
}
