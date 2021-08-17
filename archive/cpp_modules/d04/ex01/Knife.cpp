# include "Knife.hpp"

// Default constructor
Knife::Knife(void)
{
	this->_name = "Knife";
	this->_apcost = 23;
	this->_damage = 12;
	this->_attack_msg = "* kniiiiiiiife *";
	std::cout << GREY << "Knife created!" << C_RES << std::endl;
	return ;
}

// Copy constructor
Knife::Knife(const Knife& src)
{
	std::cout << GREY << "Knife (copy) created!" << C_RES << std::endl;
	*this = src;
	return;
}

// Parametric constructor (std::string const &)
Knife::Knife(std::string const & name, int apcost, int damage) : AWeapon(name, apcost, damage)
{
	this->_attack_msg = "* kniiiiiiiife *";
	std::cout << GREY << this->_name << " created!" << C_RES << std::endl;
	return ;
}

// Destructor
Knife::~Knife(void)
{
	std::cout << GREY << "Knife destruction ..." << C_RES << std::endl;
	return;
}

// Assignation operator
Knife &	Knife::operator=(const Knife& rhs)
{
	std::cout << GREY << "Assignation operator called (Knife)" << C_RES << std::endl;
	if (this != &rhs)
	{
		this->_name = rhs.getName();
		this->_apcost = rhs.getApcost();
		this->_damage = rhs.getDamage();
		this->_attack_msg = rhs.getAttackMsg();
	}
	return (*this);
}

void Knife::attack(void) const
{
	std::cout << SKY_BLUE << this->_attack_msg << C_RES << std::endl;
	return ;
}

// overload de <<
std::ostream &operator<<(std::ostream &os, const Knife & src)
{
	os << src.getName();
	return (os);
}

