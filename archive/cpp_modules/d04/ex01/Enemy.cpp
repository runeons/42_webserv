# include "Enemy.hpp"

// Default constructor
Enemy::Enemy(void)
{
	// this->_birth_msg = "Enemy creation...";
	// this->_death_msg = "Enemy destruction...";
	std::cout << GREY << "Enemy creation..." << C_RES << std::endl;
	return ;
}

// Copy constructor
Enemy::Enemy(const Enemy& src)
{
	*this = src;
	return;
}

// Parametric constructor (std::string const &)
Enemy::Enemy(int hp, std::string const & type) : _hp(hp), _type(type)
{
	// this->_birth_msg = "Enemy creation...";
	// this->_death_msg = "Enemy destruction...";
	std::cout << GREY << "Enemy creation..." << C_RES << std::endl;
	return ;
}

// Destructor
Enemy::~Enemy(void)
{
	std::cout << GREY << "Enemy destruction..." << C_RES << std::endl;
	return;
}

// Assignation operator
Enemy &	Enemy::operator=(const Enemy& rhs)
{
	std::cout << GREY << "Assignation operator called" << C_RES << std::endl;
	if (this != &rhs)
	{
		this->_hp = rhs.getHp();
		this->_type = rhs.getType();
		this->_birth_msg = rhs.getBirthMsg();
		this->_death_msg = rhs.getDeathMsg();
	}
	return (*this);
}

// getters and setters (non static attributes)
int Enemy::getHp(void) const
{
	return (this->_hp);
}

void Enemy::setHp(const int hp)
{
	this->_hp = hp;
	return ;
}

std::string Enemy::getType(void) const
{
	return (this->_type);
}

void Enemy::setType(const std::string type)
{
	this->_type = type;
	return ;
}

std::string Enemy::getBirthMsg(void) const
{
	return (this->_birth_msg);
}

void Enemy::setBirthMsg(const std::string birth_msg)
{
	this->_birth_msg = birth_msg;
	return ;
}

std::string Enemy::getDeathMsg(void) const
{
	return (this->_death_msg);
}

void Enemy::setDeathMsg(const std::string death_msg)
{
	this->_death_msg = death_msg;
	return ;
}

void Enemy::takeDamage(int damage)
{
	if (damage < 0)
		return ;
	this->_hp -= damage;
	if (this->_hp < 0)
		this->_hp = 0;
	std::cout << RED << this->_type << " takes " << damage << " damage! (now : " << this->_hp << " hit points)" << C_RES << std::endl;
	return ;
}

// overload de <<
std::ostream &operator<<(std::ostream &os, const Enemy & src)
{
	os << src.getHp();
	return (os);
}

