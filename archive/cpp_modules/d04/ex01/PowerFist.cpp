# include "PowerFist.hpp"

// Default constructor
PowerFist::PowerFist(void)
{
	this->_name = "Power Fist";
	this->_apcost = 8;
	this->_damage = 50;
	this->_attack_msg = "* pschhh... SBAM! *";
	std::cout << GREY << "Power Fist created!" << C_RES << std::endl;
	return ;
}

// Copy constructor
PowerFist::PowerFist(const PowerFist& src)
{
	std::cout << GREY << "Power Fist (copy) created!" << C_RES << std::endl;
	*this = src;
	return;
}

// Parametric constructor (std::string const &)
PowerFist::PowerFist(std::string const & name, int apcost, int damage) : AWeapon(name, apcost, damage)
{
	std::cout << GREY << this->_name << " created!" << C_RES << std::endl;
	return ;
}

// Destructor
PowerFist::~PowerFist(void)
{
	std::cout << GREY << "Power Fist destruction ..." << C_RES << std::endl;
	return;
}

// Assignation operator
PowerFist &	PowerFist::operator=(const PowerFist& rhs)
{
	std::cout << GREY << "Assignation operator called (PowerFist)" << C_RES << std::endl;
	if (this != &rhs)
	{
		this->_name = rhs.getName();
		this->_apcost = rhs.getApcost();
		this->_damage = rhs.getDamage();
		this->_attack_msg = rhs.getAttackMsg();
	}
	return (*this);
}

void PowerFist::attack(void) const
{
	std::cout << SKY_BLUE << this->_attack_msg << C_RES << std::endl;
	return ;
}

// overload de <<
std::ostream &operator<<(std::ostream &os, const PowerFist & src)
{
	os << src.getName();
	return (os);
}

