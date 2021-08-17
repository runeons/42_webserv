# include "MateriaSource.hpp"

// Default constructor
MateriaSource::MateriaSource(void)
{
	std::cout << GREY << "MateriaSource creation..." << C_RES << std::endl;
	for (int i = 0; i < 4; i++)
		this->_inventory[i] = NULL;
	return ;
}

// Copy constructor
MateriaSource::MateriaSource(const MateriaSource& src)
{
	std::cout << GREY << "MateriaSource creation..." << C_RES << std::endl;
	*this = src;
	return;
}

// Destructor
MateriaSource::~MateriaSource(void)
{
	std::cout << CORAIL << "MateriaSource destruction..." << C_RES << std::endl;
	for (int i = 0; i < this->countInventory(); i++)
	{
		if (this->_inventory[i] != NULL)
			delete this->_inventory[i];
	}
	return;
}

// Assignation operator
MateriaSource &	MateriaSource::operator=(const MateriaSource& rhs)
{
	std::cout << BROWN << "MateriaSource Assignation operator called" << C_RES << std::endl;
	if (this != &rhs)
	{
	}
	return (*this);
}

int	MateriaSource::countInventory(void)
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

/*
	learnMateria must copy the Materia passed as parameter, and store it in memory
	to be cloned later. Much in the same way as for Character , the Source can know at
	most 4 Materia, which are not necessarily unique.
*/

void MateriaSource::learnMateria(AMateria * m)
{
	std::cout << GREY << "learnMateria called" << C_RES << std::endl;
	if (m == NULL)
		std::cout << GREY << "This materia doesn't exists" << std::endl;
	else if (this->countInventory() == 4)
	{
		std::cout << GREY << "Inventory is full, deleting " << m->getType() << std::endl;
		delete m;
	}
	else
	{
		this->_inventory[this->countInventory()] = m;
		std::cout << GREEN_TREE << "Successfully learned ! Materia Source now has " << this->countInventory() << " materia in the inventory" << C_RES << std::endl;
	}
	return ;
}

/*
	In a nutshell, your Source must be able to learn "templates" of Materia, and re-create
	them on demand. You’ll then be able to create a Materia without knowing it "real" type,
	just a string identifying it.
*/

AMateria * MateriaSource::createMateria(std::string const & type)
{
	/*
		createMateria(std::string const &) will return a new Materia, which will be a
		copy of the Materia (previously learned by the Source) which type equals the parameter.
		Returns 0 if the type is unknown.
	*/
	std::cout << GREY << "createMateria called" << C_RES << std::endl;
	for (int i = 0; i < this->countInventory(); i++)
	{
		if (this->_inventory[i]->getType() == type)
		{
			AMateria *res;
			res = this->_inventory[i]->clone();
			return (res);
		}
	}
	std::cout << RED << "Error : type unknown - materia has not been learned" << C_RES << std::endl;
	return 0;
}
