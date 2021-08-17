# include "Character.hpp"

// Default constructor
int	Character::countInventory(void) const
{
	int	nb = 0;
	for (int i = 0; i < 4; i++)
	{
		if (this->_inventory[i] == NULL)
			return (nb);
		nb++;
	}
	return (nb);
}

Character::Character(void)
{
	std::cout << GREY << "Character creation..." << C_RES << std::endl;
	this->_name = "unknown";
	for (int i = 0; i < 4; i++)
		this->_inventory[i] = NULL;
	return ;
}

// Copy constructor
Character::Character(const Character& src)
{
	/*
		Copy or
		assignation of a Character must be deep, of course. The old Materia of a Character
		must be deleted. Same upon destruction of a Character .
	*/
	std::cout << GREY << "Character creation..." << C_RES << std::endl;
	this->_name = "";
	for (int i = 0; i < 4; i++)
		this->_inventory[i] = NULL;
	for (int i = 0; i < src.countInventory(); i++)
		this->_inventory[i] = src._inventory[i]->clone();
	this->_name = src.getName();
	// *this = src;
	return;
}

// Parametric constructor (std::string)
Character::Character(std::string name) : _name(name)
{
	/*
		Your Character must have a constructor taking its name as parameter.
	*/
	std::cout << GREY << this->_name << " Character creation..." << C_RES << std::endl;
	for (int i = 0; i < 4; i++)
		this->_inventory[i] = NULL;
	return ;
}

// Destructor
Character::~Character(void)
{
	/*
		Copy or
		assignation of a Character must be deep, of course. The old Materia of a Character
		must be deleted. Same upon destruction of a Character .
	*/
	std::cout << CORAIL << "Character destruction..." << C_RES << std::endl;
	for (int i = 0; i < this->countInventory(); i++)
		delete this->_inventory[i];
	return;
}

// Assignation operator
Character &	Character::operator=(const Character& rhs)
{
	/*
		Copy or
		assignation of a Character must be deep, of course. The old Materia of a Character
		must be deleted. Same upon destruction of a Character .
	*/
	std::cout << BROWN << "Character Assignation operator called" << C_RES << std::endl;
	if (this != &rhs)
	{
		this->_name = rhs.getName();
		for (int i = 0; i < this->countInventory(); i++)
		{
			delete this->_inventory[i];
			this->_inventory[i] = NULL;
		}
		for (int i = 0; i < rhs.countInventory(); i++)
			this->_inventory[i] = rhs._inventory[i]->clone();
	}
	return (*this);
}

// getters and setters (non static attributes)
std::string const &	Character::getName(void) const
{
	return (this->_name);
}

void Character::equip(AMateria *m)
{
	/*
		The Character possesses an inventory of 4 Materia at most, empty at start. He’ll
		equip the Materia in slots 0 to 3, in this order.
		In case we try to equip a Materia in a full inventory, or use/uneqip a nonexistent
		Materia, don’t do a thing.

		Of course, you’ll have to be able to support ANY AMateria in a
		Character’s inventory.
	*/
	if (m == NULL)
	{
		std::cout << GREY << "This materia doesn't exists" << std::endl;
		return ;
	}
	if (this->countInventory() == 4)
	{
		std::cout << GREY << "Inventory is full" << C_RES << std::endl;
		return ;
	}
	this->_inventory[this->countInventory()] = m;
	std::cout << GREEN_TREE << "Successfully equipped ! " << this->_name << " now has " << this->countInventory() << " materia in the inventory" << C_RES << std::endl;
	return ;
}

void Character::unequip(int idx)
{
	/*
		The unequip method must NOT delete Materia
	*/
	if (idx < 0 || idx >= this->countInventory())
	{
		std::cout << GREY << "Index out of boundaries" << std::endl;
		return ;
	}
	int i;
	for (i = idx; i < 3; i++)
	{
		this->_inventory[i] = this->_inventory[i + 1];
	}
	this->_inventory[i] = NULL;
	std::cout << CORAIL << "Successfully unequipped ! " << this->_name << " now has " << this->countInventory() << " materia in the inventory" << C_RES << std::endl;
	return ;
}

void Character::use(int idx, ICharacter & target)
{
	/*
		The use(int, ICharacter&) method will have to use the Materia at the idx slot,
		and pass target as parameter to the AMateria::use method.
		virtual void		use(ICharacter & target);
	*/
	if (idx < 0 || idx >= this->countInventory())
	{
		std::cout << GREY << "Index out of boundaries" << C_RES << std::endl;
		return ;
	}
	this->_inventory[idx]->use(target);
	return ;
}

std::string Character::getAddress(void) const
{
	std::stringstream address;

	address << this;
	return(address.str());
}

std::string Character::getNameAddress(void) const
{
	std::stringstream address;

	address << this->_name;
	return(address.str());
}

std::string Character::getInvAddress(void) const
{
	std::stringstream address;

	address << this->_inventory;
	return(address.str());
}

std::string Character::getFirstInvAddress(void) const
{
	std::stringstream address;

	address << this->_inventory[0];
	return(address.str());
}

// overload de <<
std::ostream &operator<<(std::ostream &os, const Character & src)
{
	os << "[" << src.getAddress() << "] [" << src.getNameAddress() << "] " << " [" << src.getInvAddress() << "]" << " [" << src.getFirstInvAddress() << "]";
	return (os);
}