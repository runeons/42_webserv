# include "ScavTrap.hpp"

typedef void(ScavTrap::* challenges) (std::string const & target);

// Default constructor
ScavTrap::ScavTrap(void)
{
	std::cout << GREY << "SC4V-TP " << "Default constructor called" << C_RES << std::endl;
	this->_hit_points = 100;
	this->_energy_points = 50;
	this->_level = 1;
	return ;
}

// Copy constructor
ScavTrap::ScavTrap(const ScavTrap& src)
{
	std::cout << GREY << "SC4V-TP " << "Copy constructor called" << C_RES << std::endl;
	*this = src;
	return;
}

// Parametric constructor (std::string)
ScavTrap::ScavTrap(std::string name)
{
	std::cout << GREY << "SC4V-TP " << name << " Std::string constructor called" << C_RES << std::endl;
	this->setName(name);
	this->_hit_points = 100;
	this->_energy_points = 50;
	this->_level = 1;
	return ;
}

// Destructor
ScavTrap::~ScavTrap(void)
{
	std::cout << GREY << "SC4V-TP " << this->_name << " Destructor called" << C_RES << std::endl;
	return;
}

// Assignation operator
ScavTrap &	ScavTrap::operator=(const ScavTrap& rhs)
{
	std::cout << GREY << "SC4V-TP " << "Assignation operator called" << C_RES << std::endl;
	if (this != &rhs)
	{
		this->_hit_points = rhs.getHitPoints();
		this->_energy_points = rhs.getEnergyPoints();
		this->_level = rhs.getLevel();
	}
	return (*this);
}

// getters and setters (non static attributes)
int ScavTrap::getHitPoints(void) const
{
	return (this->_hit_points);
}

void ScavTrap::setHitPoints(const int hit_points)
{
	this->_hit_points = hit_points;
	return ;
}

int ScavTrap::getMaxHitPoints(void) const
{
	return (this->_max_hit_points);
}

int ScavTrap::getEnergyPoints(void) const
{
	return (this->_energy_points);
}

void ScavTrap::setEnergyPoints(const int energy_points)
{
	this->_energy_points = energy_points;
	return ;
}

int ScavTrap::getMaxEnergyPoints(void) const
{
	return (this->_max_energy_points);
}

int ScavTrap::getLevel(void) const
{
	return (this->_level);
}

void ScavTrap::setLevel(const int level)
{
	this->_level = level;
	return ;
}

std::string ScavTrap::getName(void) const
{
	return (this->_name);
}

void ScavTrap::setName(const std::string name)
{
	this->_name = name;
	return ;
}

int ScavTrap::getMeleeAttackDamage(void) const
{
	return (this->_melee_attack_damage);
}

int ScavTrap::getRangedAttackDamage(void) const
{
	return (this->_ranged_attack_damage);
}

int ScavTrap::getArmorAttackReduction(void) const
{
	return (this->_armor_attack_reduction);
}

int ScavTrap::rangedAttack(std::string const & target)
{
	std::cout << BROWN << "SC4V-TP " << this->_name << " attacks " << target << " from a distance, causing " << this->_ranged_attack_damage << " damage points !" << C_RES << std::endl;
	return (this->_ranged_attack_damage);
}

int ScavTrap::meleeAttack(std::string const & target)
{
	std::cout << BROWN << "SC4V-TP " << this->_name << " closely attacks " << target << ", causing " << this->_melee_attack_damage << " damage points !" << C_RES << std::endl;
	return (this->_melee_attack_damage);
}

void ScavTrap::shoutPoints(void)
{
	if (this->_energy_points == 0)
		std::cout << GREEN_TREE << "SC4V-TP " << this->_name << " is supposed to be dead !" << C_RES << std::endl;
	else
		std::cout << GREEN_TREE << "SC4V-TP " << this->_name << " has " << this->_energy_points << " life points" << C_RES << std::endl;

}
void ScavTrap::takeDamage(unsigned int amount)
{
	if (amount == 0)
		return ;
	if ((int)(amount - this->_armor_attack_reduction) <= 0)
	{
		std::cout << CORAIL << "SC4V-TP " << this->_name << " does not take any damage (armor = " << this->_armor_attack_reduction << ")" << C_RES << std::endl;
		return ;
	}
	std::cout << CORAIL << "SC4V-TP " << this->_name << " takes " << amount - this->_armor_attack_reduction << " damage points (armor = " << this->_armor_attack_reduction << ")" << C_RES << std::endl;
	this->_energy_points -= (amount - this->_armor_attack_reduction);
	if (this->_energy_points < 0)
		this->_energy_points = 0;
	this->shoutPoints();
	return ;
}

void ScavTrap::beRepaired(unsigned int amount)
{
	if ((int)amount <= 0)
		return ;

	std::cout << GREEN << "SC4V-TP " << this->_name << " takes " << amount << " healing points" << C_RES << std::endl;
	this->_energy_points += amount;
	if (this->_energy_points > this->_max_energy_points)
		this->_energy_points = this->_max_energy_points;
	this->shoutPoints();
	return ;
}


void ScavTrap::challTreeClimb(std::string const & target)
{
	std::cout << BROWN << target << " must climb a tree while learning a poem !" << C_RES << std::endl;
	return ;
}

void ScavTrap::challPoemLearn(std::string const & target)
{
	std::cout << BROWN << target << " must learn a poem while singing a song !" << C_RES << std::endl;
	return ;
}

void ScavTrap::challSongSing(std::string const & target)
{
	std::cout << BROWN << target << " must sing a song while climbing a tree !"<< C_RES << std::endl;
	return ;
}

void	ScavTrap::challengeNewcomer(std::string const & target)
{
	std::string chall_names[3] = {"Climb a tree while learning a poem", "Learn a poem while singing a song", "Sing a song while climbing a tree"};
	challenges challenges[] = {
		&ScavTrap::challTreeClimb,
		&ScavTrap::challPoemLearn,
		&ScavTrap::challSongSing
	};

	std::string input;
	int			nb;

	while (1)
	{
		nb = -1;
		std::cout << COLOR(69) << "SC4V-TP " << this->_name << ": " << target << ", you need to choose a hilarious challenge :" << C_RES << std::endl;
		while (++nb < 3)
			std::cout << nb << ". " << chall_names[nb] << std::endl;
		std::cout << std::endl << ">> ";
		std::getline(std::cin, input);
		if (std::cin.eof())
			return ;
		else if (input == "0" || input == "1" || input == "2")
		{
			std::istringstream(input) >> nb;
			(this->*challenges[nb])(target);
			break ;
		}
		else
			std::cout << RED << "Please provide the appropriate challenge number" << std::endl;
	}
	return ;

}