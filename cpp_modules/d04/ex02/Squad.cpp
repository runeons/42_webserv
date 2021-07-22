# include "Squad.hpp"

// Default constructor
Squad::Squad(void)
{
	std::cout << GREY << "Squad creation ..." << C_RES << std::endl;
	this->_nb_units = 0;
	this->_lst_begin = NULL;
	return ;
}

// Copy constructor
// A deep copy allocates memory for the copy and then copies the actual value, so that the copy lives in distinct memory from the source.
Squad::Squad(const Squad& src)
{
	/*
		Upon copy construction or assignation of a Squad , the copy must be deep. Upon
		assignation, if there was any unit in the Squad before, they must be destroyed before
		being replaced. You can assume every unit will be created with new .
	*/
	std::cout << GREY << "Squad copy creation ..." << C_RES << std::endl;
	this->_nb_units = 0;
	this->_lst_begin = NULL;
	this->lst_cpy(src);
	this->_nb_units = src.getNbUnits();
	return;
}

void	Squad::lst_clear(void)
{
	t_unit	*tmp;
	t_unit	*curr;

	tmp = NULL;
	curr = this->_lst_begin;
	while (curr)
	{
		tmp = curr->next;
		delete (curr->unit);
		delete (curr);
		curr = tmp;
	}
}

Squad::~Squad(void)
{
	Squad::lst_clear();
	std::cout << GREY << "Squad destruction ..." << C_RES << std::endl;
	return;
}

void Squad::lst_cpy(const Squad &src)
{
    for (int i = 0; i < src.getCount(); i++)
        push(src.getUnit(i)->clone());
    return ;
}

// Assignation operator
Squad &	Squad::operator=(const Squad& rhs)
{
	/*
		Upon copy construction or assignation of a Squad , the copy must be deep. Upon
		assignation, if there was any unit in the Squad before, they must be destroyed before
		being replaced. You can assume every unit will be created with new .
	*/
	std::cout << BROWN << "Squad assignation operator called" << C_RES << std::endl;
	t_unit *curr;
	t_unit	*tmp;
	int		nb_units;

	nb_units = this->getCount();
	curr = this->_lst_begin;
	this->_nb_units = 0;
	this->_lst_begin = NULL;
	if (this != &rhs)
	{
		if (nb_units > 0)
		{
			tmp = NULL;
			while (curr)
			{
				tmp = curr->next;
				delete (curr->unit);
				delete (curr);
				curr = tmp;
			}
		}
		this->lst_cpy(rhs);
		this->_nb_units = rhs.getNbUnits();
	}
	return (*this);
}

// getters and setters (non static attributes)
int Squad::getNbUnits(void) const
{
	return (this->_nb_units);
}

void Squad::setNbUnits(const int nb_units)
{
	this->_nb_units = nb_units;
	return ;
}

Squad::t_unit * Squad::getLst(void) const
{
	return (this->_lst_begin);
}

void Squad::setLst(Squad::t_unit * lst)
{
	this->_lst_begin = lst;
	return ;
}

int Squad::getCount(void) const
{
	return (this->_nb_units);
}

ISpaceMarine * Squad::getUnit(int nb) const
{
	if (nb < 0 || nb >= this->getCount() || this->_lst_begin == NULL)
	{
		std::cout << RED << "Error : unit nb out of boundaries" << C_RES << std::endl;
		return (NULL);
	}
	t_unit *tmp;
	int	i = -1;
	tmp = this->_lst_begin;
	while (++i < nb && tmp->next)
		tmp = tmp->next;
	if (i != nb)
	{
		std::cout << RED << "Error : iterate in getUnit()" << C_RES << std::endl;
		return NULL;
	}
	return (tmp->unit);
}

void Squad::lst_add_back(ISpaceMarine * new_unit)
{
	t_unit	*tmp;

	if (this->_lst_begin == NULL)
	{
		std::cout << GREY << "Adding first unit [" << new_unit << "]" << C_RES << std::endl;
		this->_lst_begin = new t_unit;
		this->_lst_begin->unit = new_unit;
		this->_lst_begin->next = NULL;;
		this->_lst_begin->prev = NULL;;
	}
	else
	{
		tmp = this->_lst_begin;
		while (tmp && tmp->next)
			tmp = tmp->next;
		std::cout << GREY << "Adding new unit [" << new_unit << "]" << C_RES << std::endl;
		tmp->next = new t_unit;
		tmp->next->unit = new_unit;
		tmp->next->prev = tmp;
		tmp->next->next = NULL;
	}
	this->_nb_units++;
}

int Squad::push(ISpaceMarine * new_unit)
{
	if (new_unit == NULL)
	{
		std::cout << GREY << "Don't expect me to add a NULL unit!" << C_RES << std::endl;
		return (this->_nb_units);
	}
	int	i = -1;
	while (++i < this->getCount())
	{
		if (this->getUnit(i) == new_unit)
		{
			std::cout << GREY << "Were you thinking I would add this unit twice? [" << new_unit << "]" << C_RES << std::endl;
			return (this->_nb_units);
		}
	}
	this->lst_add_back(new_unit);
	return (this->_nb_units);
}

std::string Squad::getAddress(void) const
{
	std::stringstream address;

	address << this;
	return(address.str());
}

std::string Squad::getLstBeginAddress(void) const
{
	std::stringstream address;

	address << this->_lst_begin;
	return(address.str());
}

std::string Squad::getNbUnitsAddress(void) const
{
	std::stringstream address;

	address << this->_nb_units;
	return(address.str());
}

// overload de <<
std::ostream &operator<<(std::ostream &os, const Squad & src)
{
	os << "[" << src.getAddress() << "] [" << src.getLstBeginAddress() << "] " << " [" << src.getNbUnitsAddress() << "]";
	return (os);
}
