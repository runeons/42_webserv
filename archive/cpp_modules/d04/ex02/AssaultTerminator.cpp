# include "AssaultTerminator.hpp"

// Default constructor
AssaultTerminator::AssaultTerminator(void)
{
	std::cout << GREEN_TREE << "* teleports from space *" << C_RES << std::endl;
	return ;
}

// Copy constructor
AssaultTerminator::AssaultTerminator(const AssaultTerminator& src)
{
	std::cout << GREEN_TREE << "* teleports from space *" << C_RES << std::endl;
	*this = src;
	return;
}

// Destructor
AssaultTerminator::~AssaultTerminator(void)
{
	std::cout << CORAIL << "I’ll be back..." << C_RES << std::endl;
	return;
}

// Assignation operator
AssaultTerminator &	AssaultTerminator::operator=(const AssaultTerminator& rhs)
{
	std::cout << BROWN << "Assault Terminator Assignation operator called" << C_RES << std::endl;
	if (this != &rhs)
	{
	}
	return (*this);
}

ISpaceMarine * AssaultTerminator::clone(void) const
{
	std::cout << GREY << "Tactical Marine clone called" << C_RES << std::endl;
	return (new AssaultTerminator (*this));
}

void AssaultTerminator::battleCry(void) const
{
	std::cout << SKY_BLUE << "This code is unclean. PURIFY IT!" << C_RES << std::endl;
	return ;
}

void AssaultTerminator::rangedAttack(void) const
{
	std::cout << SKY_BLUE << "* does nothing *" << C_RES << std::endl;
	return ;
}

void AssaultTerminator::meleeAttack(void) const
{
	std::cout << SKY_BLUE << "* attacks with chainfists *" << C_RES << std::endl;
	return ;
}

std::string AssaultTerminator::getAddress(void) const
{
	std::stringstream address;

	address << this;
	return(address.str());
}

// overload de <<
std::ostream &operator<<(std::ostream &os, const AssaultTerminator & src)
{
	os << src.getAddress();
	return (os);
}
