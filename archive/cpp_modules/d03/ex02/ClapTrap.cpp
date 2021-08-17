# include "ClapTrap.hpp"

typedef int(ClapTrap::* attacks) (std::string const & target);

// Default constructor
ClapTrap::ClapTrap(void)
{
	std::srand(time(NULL));
	this->_hit_points = 0;
	this->_max_hit_points = 0;
	this->_energy_points = 0;
	this->_max_energy_points = 0;
	this->_level = 0;
	this->_name = "unknown";
	this->_melee_attack_damage = 0;
	this->_ranged_attack_damage = 0;
	this->_armor_attack_reduction = 0;
	this->_type = "CL4P-TP ";
	std::cout << GREY << this->_type << "Default constructor called" << C_RES << std::endl;
	return ;
}

// Copy constructor
ClapTrap::ClapTrap(const ClapTrap& src)
{
	std::cout << GREY << "CL4P-TP " << "Copy constructor called" << C_RES << std::endl;
	std::srand(time(NULL));
	*this = src;
	return;
}

// Parametric constructor (std::string)
ClapTrap::ClapTrap(std::string name) : _name(name)
{
	this->_hit_points = 0;
	this->_max_hit_points = 0;
	this->_energy_points = 0;
	this->_max_energy_points = 0;
	this->_level = 0;
	this->_melee_attack_damage = 0;
	this->_ranged_attack_damage = 0;
	this->_armor_attack_reduction = 0;
	this->_type = "CL4P-TP ";
	std::cout << GREY << this->_type << name << " Std::string constructor called" << C_RES << std::endl;
	std::srand(time(NULL));
	return ;
}

// Destructor
ClapTrap::~ClapTrap(void)
{
	std::cout << GREY << "CL4P-TP " << this->_name << " Destructor called" << C_RES << std::endl;
	return;
}

// Assignation operator
ClapTrap &	ClapTrap::operator=(const ClapTrap& rhs)
{
	std::cout << GREY << this->_type << "Assignation operator called" << C_RES << std::endl;
	if (this != &rhs)
	{
		this->_hit_points = rhs.getHitPoints();
		this->_energy_points = rhs.getEnergyPoints();
		this->_level = rhs.getLevel();
		this->_hit_points = rhs.getHitPoints();
		this->_max_hit_points = rhs.getMaxHitPoints();
		this->_energy_points = rhs.getEnergyPoints();
		this->_max_energy_points = rhs.getMaxEnergyPoints();
		this->_level = rhs.getLevel();
		this->_name = rhs.getName();
		this->_melee_attack_damage = rhs.getMeleeAttackDamage();
		this->_ranged_attack_damage = rhs.getRangedAttackDamage();
		this->_armor_attack_reduction = rhs.getArmorAttackReduction();
	}
	return (*this);
}

// getters and setters (non static attributes)
int ClapTrap::getHitPoints(void) const
{
	return (this->_hit_points);
}

void ClapTrap::setHitPoints(const int hit_points)
{
	this->_hit_points = hit_points;
	return ;
}

int ClapTrap::getMaxHitPoints(void) const
{
	return (this->_max_hit_points);
}

int ClapTrap::getEnergyPoints(void) const
{
	return (this->_energy_points);
}

void ClapTrap::setEnergyPoints(const int energy_points)
{
	this->_energy_points = energy_points;
	return ;
}

int ClapTrap::getMaxEnergyPoints(void) const
{
	return (this->_max_energy_points);
}

int ClapTrap::getLevel(void) const
{
	return (this->_level);
}

void ClapTrap::setLevel(const int level)
{
	this->_level = level;
	return ;
}

std::string ClapTrap::getName(void) const
{
	return (this->_name);
}

void ClapTrap::setName(const std::string name)
{
	this->_name = name;
	return ;
}

int ClapTrap::getMeleeAttackDamage(void) const
{
	return (this->_melee_attack_damage);
}

int ClapTrap::getRangedAttackDamage(void) const
{
	return (this->_ranged_attack_damage);
}

int ClapTrap::getArmorAttackReduction(void) const
{
	return (this->_armor_attack_reduction);
}

int ClapTrap::rangedAttack(std::string const & target)
{
	std::cout << BROWN << this->_type << this->_name << " attacks " << target << " from a distance, causing " << this->_ranged_attack_damage << " damage points !" << C_RES << std::endl;
	return (this->_ranged_attack_damage);
}

int ClapTrap::meleeAttack(std::string const & target)
{
	std::cout << BROWN << this->_type << this->_name << " closely attacks " << target << ", causing " << this->_melee_attack_damage << " damage points !" << C_RES << std::endl;
	return (this->_melee_attack_damage);
}

void ClapTrap::shoutPoints(void)
{
	if (this->_energy_points == 0)
		std::cout << GREEN_TREE << this->_type << this->_name << " is supposed to be dead !" << C_RES << std::endl;
	else
		std::cout << GREEN_TREE << this->_type << this->_name << " has " << this->_energy_points << " life points" << C_RES << std::endl;

}
void ClapTrap::takeDamage(unsigned int amount)
{
	if (amount == 0)
		return ;
	if ((int)(amount - this->_armor_attack_reduction) <= 0)
	{
		std::cout << CORAIL << this->_type << this->_name << " does not take any damage (armor = " << this->_armor_attack_reduction << ")" << C_RES << std::endl;
		return ;
	}
	std::cout << CORAIL << this->_type << this->_name << " takes " << amount - this->_armor_attack_reduction << " damage points (armor = " << this->_armor_attack_reduction << ")" << C_RES << std::endl;
	this->_energy_points -= (amount - this->_armor_attack_reduction);
	if (this->_energy_points < 0)
		this->_energy_points = 0;
	this->shoutPoints();
	return ;
}

void ClapTrap::beRepaired(unsigned int amount)
{
	if ((int)amount <= 0)
		return ;

	std::cout << GREEN << this->_type << this->_name << " takes " << amount << " healing points" << C_RES << std::endl;
	this->_energy_points += amount;
	if (this->_energy_points > this->_max_energy_points)
		this->_energy_points = this->_max_energy_points;
	this->shoutPoints();
	return ;
}
