# include "PlasmaRifle.hpp"

// Default constructor
PlasmaRifle::PlasmaRifle(void)
{
	this->_name = "Plasma Rifle";
	this->_apcost = 5;
	this->_damage = 21;
	this->_attack_msg = "* piouuu piouuu piouuu *";
	std::cout << GREY << "Plasma Rifle created!" << C_RES << std::endl;
	return ;
}

// Copy constructor
PlasmaRifle::PlasmaRifle(const PlasmaRifle& src)
{
	std::cout << GREY << "Plasma Rifle (copy) created!" << C_RES << std::endl;
	*this = src;
	return;
}

// Parametric constructor (std::string const &)
PlasmaRifle::PlasmaRifle(std::string const & name, int apcost, int damage) : AWeapon(name, apcost, damage)
{
	this->_attack_msg = "* piouuu piouuu piouuu *";
	std::cout << GREY << this->_name << " created!" << C_RES << std::endl;
	return ;
}

// Destructor
PlasmaRifle::~PlasmaRifle(void)
{
	std::cout << GREY << "Plasma Rifle destruction ..." << C_RES << std::endl;
	return;
}

// Assignation operator
PlasmaRifle &	PlasmaRifle::operator=(const PlasmaRifle& rhs)
{
	std::cout << GREY << "Assignation operator called (PlasmaRifle)" << C_RES << std::endl;
	if (this != &rhs)
	{
		this->_name = rhs.getName();
		this->_apcost = rhs.getApcost();
		this->_damage = rhs.getDamage();
		this->_attack_msg = rhs.getAttackMsg();
	}
	return (*this);
}

void PlasmaRifle::attack(void) const
{
	std::cout << SKY_BLUE << this->_attack_msg << C_RES << std::endl;
	return ;
}

// overload de <<
std::ostream &operator<<(std::ostream &os, const PlasmaRifle & src)
{
	os << src.getName();
	return (os);
}

