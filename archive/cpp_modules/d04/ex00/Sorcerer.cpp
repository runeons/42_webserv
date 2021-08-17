# include "Sorcerer.hpp"

// Default constructor
Sorcerer::Sorcerer(void)
{
	std::cout << GREEN_TREE << this->_name << ", " << this->_title << ", is born!" << C_RES << std::endl;
	return ;
}

// Copy constructor
Sorcerer::Sorcerer(const Sorcerer& src)
{
	std::cout << GREEN_TREE << this->_name << ", " << this->_title << ", is born!" << C_RES << std::endl;
	*this = src;
	return;
}

// Parametric constructor (std::string)
Sorcerer::Sorcerer(std::string name, std::string title) : _name(name), _title(title)
{
	std::cout << GREEN_TREE << this->_name << ", " << this->_title << ", is born!" << C_RES << std::endl;
	return ;
}

// Destructor
Sorcerer::~Sorcerer(void)
{
	std::cout << CORAIL << this->_name << ", " << this->_title << ", is dead. Consequences will never be the same!" << C_RES << std::endl;
	return;
}

// Assignation operator
Sorcerer &	Sorcerer::operator=(const Sorcerer& rhs)
{
	std::cout << BROWN << "Assignation operator called" << C_RES << std::endl;
	if (this != &rhs)
	{
		this->_name = rhs.getName();
		this->_title = rhs.getTitle();
	}
	return (*this);
}

// getters and setters (non static attributes)
std::string Sorcerer::getName(void) const
{
	return (this->_name);
}

void Sorcerer::setName(const std::string name)
{
	this->_name = name;
	return ;
}

std::string Sorcerer::getTitle(void) const
{
	return (this->_title);
}

void Sorcerer::setTitle(const std::string title)
{
	this->_title = title;
	return ;
}

void Sorcerer::polymorph(Victim const & victim) const
{
	// std::cout << ORANGE << "I am "<< this->_name << "and am polymorphing you, " << victim.getName() << "!" << C_RES << std::endl;
	victim.getPolymorphed();
	return ;
}


// overload de <<
std::ostream &operator<<(std::ostream &os, const Sorcerer & src)
{
	os << src.introduce();
	return (os);
}

std::string Sorcerer::introduce(void) const
{
	std::stringstream ss;

	ss << SKY_BLUE << "I am " << this->_name << ", " << this->_title << ", and I like ponies!" << C_RES << std::endl;
	return ss.str();
}

