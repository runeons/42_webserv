# include "AWeapon.hpp"

// Default constructor
AWeapon::AWeapon(void)
{
	std::cout << GREY << "Weapon creation ..." << C_RES << std::endl;
	return ;
}

// Copy constructor
AWeapon::AWeapon(const AWeapon& src)
{
	std::cout << GREY << "Weapon creation ..." << C_RES << std::endl;
	*this = src;
	return;
}

// Parametric constructor (std::string const &)
AWeapon::AWeapon(std::string const & name, int apcost, int damage) : _name(name), _apcost(apcost), _damage(damage)
{
	std::cout << GREY << this->_name << " created!" << C_RES << std::endl;
	return ;
}

// Destructor
AWeapon::~AWeapon(void)
{
	std::cout << GREY << "Weapon destruction ..." << C_RES << std::endl;
	return;
}

// Assignation operator
AWeapon &	AWeapon::operator=(const AWeapon& rhs)
{
	std::cout << GREY << "Assignation operator called (AWeapon)" << C_RES << std::endl;
	if (this != &rhs)
	{
		this->_name = rhs.getName();
		this->_apcost = rhs.getApcost();
		this->_damage = rhs.getDamage();
		this->_attack_msg = rhs.getAttackMsg();
	}
	return (*this);
}

// getters and setters (non static attributes)
std::string AWeapon::getName(void) const
{
	return (this->_name);
}

void AWeapon::setName(const std::string name)
{
	this->_name = name;
	return ;
}

int AWeapon::getApcost(void) const
{
	return (this->_apcost);
}

void AWeapon::setApcost(const int apcost)
{
	this->_apcost = apcost;
	return ;
}

int AWeapon::getDamage(void) const
{
	return (this->_damage);
}

void AWeapon::setDamage(const int damage)
{
	this->_damage = damage;
	return ;
}

std::string AWeapon::getAttackMsg(void) const
{
	return (this->_attack_msg);
}

void AWeapon::setAttackMsg(const std::string attack_msg)
{
	this->_attack_msg = attack_msg;
	return ;
}

// overload de <<
std::ostream &operator<<(std::ostream &os, const AWeapon & src)
{
	os << src.getName();
	return (os);
}

