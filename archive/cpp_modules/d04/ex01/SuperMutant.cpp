# include "SuperMutant.hpp"

// Default constructor
SuperMutant::SuperMutant(void)
{
	this->_hp = 170;
	this->_type = "Super Mutant";
	this->_birth_msg = "Gaaah. Me want smash heads!";
	this->_death_msg = "Aaargh...";
	std::cout << GREEN_TREE << this->_birth_msg << C_RES << std::endl;
	return ;
}

// Copy constructor
SuperMutant::SuperMutant(const SuperMutant& src)
{
	std::cout << GREEN_TREE << this->_birth_msg << C_RES << std::endl;
	*this = src;
	return;
}

// Parametric constructor (std::string const &)
SuperMutant::SuperMutant(int hp, std::string const & type) : Enemy(hp, type)
{
	this->_birth_msg = "Gaaah. Me want smash heads!";
	this->_death_msg = "Aaargh...";
	std::cout << GREEN_TREE << this->_birth_msg << C_RES << std::endl;
	return ;
}

// Destructor
SuperMutant::~SuperMutant(void)
{
	std::cout << CORAIL << this->_death_msg<< C_RES << std::endl;
	return;
}

// Assignation operator
SuperMutant &	SuperMutant::operator=(const SuperMutant& rhs)
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

void SuperMutant::takeDamage(int damage)
{
	std::cout << SKY_BLUE << this->_type << " is supposed to take " << damage << " damage, but will only take " << damage - 3 << "!" << C_RES << std::endl;
	Enemy::takeDamage(damage - 3);
	// std::cout << SKY_BLUE << this->_type << " takes " << damage << " damage! (now : " << this->_hp << " hit points)" << C_RES << std::endl;
	return ;
}

// overload de <<
std::ostream &operator<<(std::ostream &os, const SuperMutant & src)
{
	os << src.getHp();
	return (os);
}

