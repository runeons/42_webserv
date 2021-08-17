# include "TacticalMarine.hpp"

// Default constructor
TacticalMarine::TacticalMarine(void)
{
	std::cout << GREEN_TREE << "Tactical Marine ready for battle!" << C_RES << std::endl;
	return ;
}

// Copy constructor
TacticalMarine::TacticalMarine(const TacticalMarine& src)
{
	std::cout << GREEN_TREE << "Tactical Marine ready for battle!" << C_RES << std::endl;
	*this = src;
	return;
}

// Destructor
TacticalMarine::~TacticalMarine(void)
{
	std::cout << CORAIL << "Aaargh..." << C_RES << std::endl;
	return;
}

// Assignation operator
TacticalMarine &	TacticalMarine::operator=(const TacticalMarine& rhs)
{
	std::cout << BROWN << "Tactical Marine Assignation operator called" << C_RES << std::endl;
	if (this != &rhs)
	{
	}
	return (*this);
}

ISpaceMarine * TacticalMarine::clone(void) const
{
	std::cout << GREY << "Tactical Marine clone called" << C_RES << std::endl;
	return (new TacticalMarine (*this));
}

void TacticalMarine::battleCry(void) const
{
	std::cout << SKY_BLUE << "For the holy PLOT!" << C_RES << std::endl;
	return ;
}

void TacticalMarine::rangedAttack(void) const
{
	std::cout << SKY_BLUE << "* attacks with a bolter *" << C_RES << std::endl;
	return ;
}

void TacticalMarine::meleeAttack(void) const
{
	std::cout << SKY_BLUE << "* attacks with a chainsword *" << C_RES << std::endl;
	return ;
}

std::string TacticalMarine::getAddress(void) const
{
	std::stringstream address;

	address << this;
	return(address.str());
}

// overload de <<
std::ostream &operator<<(std::ostream &os, const TacticalMarine & src)
{
	os << src.getAddress();
	return (os);
}
