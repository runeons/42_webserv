# include "Victim.hpp"

// Default constructor
Victim::Victim(void)
{
	std::cout << GREEN_TREE << "Some random victim called " << this->_name << " just appeared!" << C_RES << std::endl;
	return ;
}

// Copy constructor
Victim::Victim(const Victim& src)
{
	std::cout << GREEN_TREE << "Some random victim called " << this->_name << " just appeared!" << C_RES << std::endl;
	*this = src;
	return;
}

// Parametric constructor (std::string)
Victim::Victim(std::string name) : _name(name)
{
	this->_polym_msg = "a cute little sheep";
	std::cout << GREEN_TREE << "Some random victim called " << this->_name << " just appeared!" << C_RES << std::endl;
	return ;
}

// Destructor
Victim::~Victim(void)
{
	std::cout << CORAIL << "Victim " << this->_name << " just died for no apparent reason!" << C_RES << std::endl;
	return;
}

// Assignation operator
Victim &	Victim::operator=(const Victim& rhs)
{
	std::cout << BROWN << "Assignation operator called" << C_RES << std::endl;
	if (this != &rhs)
	{
		this->_name = rhs.getName();
		this->_polym_msg = rhs._polym_msg;
	}
	return (*this);
}

// getters and setters (non static attributes)
std::string Victim::getName(void) const
{
	return (this->_name);
}

void Victim::setName(const std::string name)
{
	this->_name = name;
	return ;
}

void Victim::getPolymorphed(void) const
{
	std::cout << ORANGE << this->_name << " has been turned into " << this->_polym_msg << "!" << C_RES << std::endl;
	return ;
}

// overload de <<
std::ostream &operator<<(std::ostream &os, const Victim & src)
{
	os << src.introduce();
	return (os);
}

std::string Victim::introduce(void) const
{
	std::stringstream ss;

	ss << SKY_BLUE << "I am " << this->_name << " and I like otters!" << C_RES << std::endl;
	return ss.str();
}

