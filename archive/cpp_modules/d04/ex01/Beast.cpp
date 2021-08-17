# include "Beast.hpp"

// Default constructor
Beast::Beast(void)
{
	this->_hp = 90;
	this->_type = "Beast";
	this->_birth_msg = "* BEAAAAAST *";
	this->_death_msg = "* Beath death! *";
	std::cout << GREEN_TREE << this->_birth_msg << C_RES << std::endl;
	return ;
}

// Copy constructor
Beast::Beast(const Beast& src)
{
	std::cout << GREEN_TREE << this->_birth_msg << C_RES << std::endl;
	*this = src;
	return;
}

// Parametric constructor (std::string const &)
Beast::Beast(int hp, std::string const & type) : Enemy(hp, type)
{
	this->_birth_msg = "* BEAAAAAST *";
	this->_death_msg = "* Beath death! *";
	std::cout << GREEN_TREE << this->_birth_msg << C_RES << std::endl;
	return ;
}

// Destructor
Beast::~Beast(void)
{
	std::cout << CORAIL << this->_death_msg<< C_RES << std::endl;
	return;
}

// Assignation operator
Beast &	Beast::operator=(const Beast& rhs)
{
	std::cout << BROWN << "Assignation operator called" << C_RES << std::endl;
	if (this != &rhs)
	{
		this->_hp = rhs.getHp();
		this->_type = rhs.getType();
		this->_birth_msg = rhs.getBirthMsg();
		this->_death_msg = rhs.getDeathMsg();
	}
	return (*this);
}

void Beast::takeDamage(int damage)
{
	Enemy::takeDamage(damage);
	return ;
}

// overload de <<
std::ostream &operator<<(std::ostream &os, const Beast & src)
{
	os << src.getHp();
	return (os);
}

