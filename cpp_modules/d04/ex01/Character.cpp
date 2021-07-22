# include "Character.hpp"

// Default constructor
Character::Character(void)
{
	this->_name = "unnamed";
	this->_max_ap = 40;
	this->_ap = this->_max_ap;
	this->_weapon = 0;
	std::cout << GREY << "Character creation ..." << C_RES << std::endl;
	return ;
}

// Copy constructor
Character::Character(const Character& src)
{
	std::cout << GREY << "Character creation ..." << C_RES << std::endl;
	*this = src;
	return;
}

// Parametric constructor (std::string const &)
Character::Character(std::string const & name) : _name(name)
{
	this->_max_ap = 40;
	this->_ap = this->_max_ap;
	this->_weapon = 0;
	std::cout << GREY << this->_name << " created!" << C_RES << std::endl;
	return ;
}

// Destructor
Character::~Character(void)
{
	std::cout << GREY << "Character destruction ..." << C_RES << std::endl;
	return;
}

// Assignation operator
Character &	Character::operator=(const Character& rhs)
{
	std::cout << GREY << "Assignation operator called" << C_RES << std::endl;
	if (this != &rhs)
	{
		this->_name = rhs.getName();
		this->_ap = rhs.getAp();
		this->_weapon = rhs.getWeapon();
	}
	return (*this);
}

// getters and setters (non static attributes)
std::string Character::getName(void) const
{
	return (this->_name);
}

void Character::setName(const std::string name)
{
	this->_name = name;
	return ;
}

int Character::getAp(void) const
{
	return (this->_ap);
}

void Character::setAp(const int ap)
{
	this->_ap = ap;
	return ;
}

AWeapon *  Character::getWeapon(void) const
{
	return (this->_weapon);
}

void Character::setWeapon(AWeapon * weapon)
{
	this->_weapon = weapon;
	return ;
}

void Character::recoverAP(void)
{
	if (this->_ap >= this->_max_ap)
	{
		std::cout << GREEN << this->_name << " can't recover (already max AP)" << C_RES << std::endl;
		return ;
	}
	this->_ap += 10;
	if (this->_ap > this->_max_ap)
		this->_ap = this->_max_ap;
	std::cout << GREEN << this->_name << " recovers 10 AP (max " << this->_max_ap << ") (now : " << this->_ap << " ap)" << C_RES << std::endl;
	return ;
}

void Character::equip(AWeapon * weapon)
{
	this->_weapon = weapon;
	std::cout << GREY << this->_name << " is now equipped with a " << weapon->getName() << C_RES << std::endl;
	return ;
}

void Character::attack(Enemy * enemy)
{
	if (this->_ap < this->getWeapon()->getApcost())
		std::cout << SKY_BLUE << this->_name << " can't attack with a " << this->getWeapon()->getName() << " (has " << this->_ap << " AP and it costs " << this->getWeapon()->getApcost() << ")" << C_RES << std::endl;
	else
	{
		std::cout << SKY_BLUE << this->_name << " attacks " << enemy->getType() << " with a " << this->getWeapon()->getName() << C_RES << std::endl;
		this->getWeapon()->attack();
		this->_ap -= this->getWeapon()->getApcost();
		enemy->takeDamage(this->getWeapon()->getDamage());
		if (enemy->getHp() == 0)
			delete enemy;
	}
	return ;
}

// overload de <<
std::ostream &operator<<(std::ostream &os, const Character & src)
{
	if (src.getWeapon())
		os << ORANGE << src.getName() << " has " << src.getAp() << " AP and wields a " << src.getWeapon()->getName() << C_RES << std::endl;
	else
		os << ORANGE << src.getName() << " has " << src.getAp() << " AP and is unarmed" << C_RES << std::endl;
	return (os);
}

