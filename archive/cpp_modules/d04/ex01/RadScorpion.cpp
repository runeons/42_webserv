# include "RadScorpion.hpp"

// Default constructor
RadScorpion::RadScorpion(void)
{
	this->_hp = 80;
	this->_type = "RadScorpion";
	this->_birth_msg = "* click click click *";
	this->_death_msg = "* SPROTCH *";
	std::cout << GREEN_TREE << this->_birth_msg << C_RES << std::endl;
	return ;
}

// Copy constructor
RadScorpion::RadScorpion(const RadScorpion& src)
{
	std::cout << GREEN_TREE << this->_birth_msg << C_RES << std::endl;
	*this = src;
	return;
}

// Parametric constructor (std::string const &)
RadScorpion::RadScorpion(int hp, std::string const & type) : Enemy(hp, type)
{
	this->_birth_msg = "* click click click *";
	this->_death_msg = "* SPROTCH *";
	std::cout << GREEN_TREE << this->_birth_msg << C_RES << std::endl;
	return ;
}

// Destructor
RadScorpion::~RadScorpion(void)
{
	std::cout << CORAIL << this->_death_msg<< C_RES << std::endl;
	return;
}

// Assignation operator
RadScorpion &	RadScorpion::operator=(const RadScorpion& rhs)
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

void RadScorpion::takeDamage(int damage)
{
	Enemy::takeDamage(damage);
	return ;
}

// overload de <<
std::ostream &operator<<(std::ostream &os, const RadScorpion & src)
{
	os << src.getHp();
	return (os);
}

