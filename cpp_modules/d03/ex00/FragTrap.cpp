# include "FragTrap.hpp"

typedef int(FragTrap::* attacks) (std::string const & target);

// Default constructor
FragTrap::FragTrap(void)
{
	std::cout << GREY << "FR4G-TP " << "Default constructor called" << C_RES << std::endl;
	std::srand(time(NULL));
	this->_hit_points = 100;
	this->_energy_points = 100;
	this->_level = 1;
	return ;
}

// Copy constructor
FragTrap::FragTrap(const FragTrap& src)
{
	std::cout << GREY << "FR4G-TP " << "Copy constructor called" << C_RES << std::endl;
	std::srand(time(NULL));
	*this = src;
	return;
}

// Parametric constructor (std::string)
FragTrap::FragTrap(std::string name)
{
	std::cout << GREY << "FR4G-TP " << name << " Std::string constructor called" << C_RES << std::endl;
	std::srand(time(NULL));
	this->setName(name);
	this->_hit_points = 100;
	this->_energy_points = 100;
	this->_level = 1;
	return ;
}

// Destructor
FragTrap::~FragTrap(void)
{
	std::cout << GREY << "FR4G-TP " << this->_name << " Destructor called" << C_RES << std::endl;
	return;
}

// Assignation operator
FragTrap &	FragTrap::operator=(const FragTrap& rhs)
{
	std::cout << GREY << "FR4G-TP " << "Assignation operator called" << C_RES << std::endl;
	if (this != &rhs)
	{
		this->_hit_points = rhs.getHitPoints();
		this->_energy_points = rhs.getEnergyPoints();
		this->_level = rhs.getLevel();
	}
	return (*this);
}

// getters and setters (non static attributes)
int FragTrap::getHitPoints(void) const
{
	return (this->_hit_points);
}

void FragTrap::setHitPoints(const int hit_points)
{
	this->_hit_points = hit_points;
	return ;
}

int FragTrap::getMaxHitPoints(void) const
{
	return (this->_max_hit_points);
}

int FragTrap::getEnergyPoints(void) const
{
	return (this->_energy_points);
}

void FragTrap::setEnergyPoints(const int energy_points)
{
	this->_energy_points = energy_points;
	return ;
}

int FragTrap::getMaxEnergyPoints(void) const
{
	return (this->_max_energy_points);
}

int FragTrap::getLevel(void) const
{
	return (this->_level);
}

void FragTrap::setLevel(const int level)
{
	this->_level = level;
	return ;
}

std::string FragTrap::getName(void) const
{
	return (this->_name);
}

void FragTrap::setName(const std::string name)
{
	this->_name = name;
	return ;
}

int FragTrap::getMeleeAttackDamage(void) const
{
	return (this->_melee_attack_damage);
}

int FragTrap::getRangedAttackDamage(void) const
{
	return (this->_ranged_attack_damage);
}

int FragTrap::getArmorAttackReduction(void) const
{
	return (this->_armor_attack_reduction);
}

int FragTrap::rangedAttack(std::string const & target)
{
	std::cout << BROWN << "FR4G-TP " << this->_name << " attacks " << target << " from a distance, causing " << this->_ranged_attack_damage << " damage points !" << C_RES << std::endl;
	return (this->_ranged_attack_damage);
}

int FragTrap::meleeAttack(std::string const & target)
{
	std::cout << BROWN << "FR4G-TP " << this->_name << " closely attacks " << target << ", causing " << this->_melee_attack_damage << " damage points !" << C_RES << std::endl;
	return (this->_melee_attack_damage);
}

void FragTrap::shoutPoints(void)
{
	if (this->_energy_points == 0)
		std::cout << GREEN_TREE << "FR4G-TP " << this->_name << " is supposed to be dead !" << C_RES << std::endl;
	else
		std::cout << GREEN_TREE << "FR4G-TP " << this->_name << " has " << this->_energy_points << " life points" << C_RES << std::endl;

}
void FragTrap::takeDamage(unsigned int amount)
{
	if (amount == 0)
		return ;
	if ((int)(amount - this->_armor_attack_reduction) <= 0)
	{
		std::cout << CORAIL << "FR4G-TP " << this->_name << " does not take any damage (armor = " << this->_armor_attack_reduction << ")" << C_RES << std::endl;
		return ;
	}
	std::cout << CORAIL << "FR4G-TP " << this->_name << " takes " << amount - this->_armor_attack_reduction << " damage points (armor = " << this->_armor_attack_reduction << ")" << C_RES << std::endl;
	this->_energy_points -= (amount - this->_armor_attack_reduction);
	if (this->_energy_points < 0)
		this->_energy_points = 0;
	this->shoutPoints();
	return ;
}

void FragTrap::beRepaired(unsigned int amount)
{
	if ((int)amount <= 0)
		return ;

	std::cout << GREEN << "FR4G-TP " << this->_name << " takes " << amount << " healing points" << C_RES << std::endl;
	this->_energy_points += amount;
	if (this->_energy_points > this->_max_energy_points)
		this->_energy_points = this->_max_energy_points;
	this->shoutPoints();
	return ;
}

int FragTrap::ironyAttack(std::string const & target)
{
	int	damage = 9;
	std::cout << BROWN << "FR4G-TP " << this->_name << ": I'm trying an ironical joke on you, " << target << ", causing " << damage << " damage points !" << C_RES << std::endl;
	return (damage);
}

int FragTrap::britishAttack(std::string const & target)
{
	int	damage = 2;
	std::cout << BROWN << "FR4G-TP " << this->_name << ": I'm trying British Humour with you, " << target << ", causing " << damage << " damage points !" << C_RES << std::endl;
	return (damage);
}

int FragTrap::darkAttack(std::string const & target)
{
	int	damage = 4;
	std::cout << BROWN << "FR4G-TP " << this->_name << ": I'm trying an very very dark joke on you, " << target << ", causing " << damage << " damage points !" << C_RES << std::endl;
	return (damage);
}

int FragTrap::embarrassingAttack(std::string const & target)
{
	int	damage = 5;
	std::cout << BROWN << "FR4G-TP " << this->_name << ": I'm trying an embarrassing joke on you, " << target << ", causing " << damage << " damage points !" << C_RES << std::endl;
	return (damage);
}

int FragTrap::sarcasmAttack(std::string const & target)
{
	int	damage = 19;
	std::cout << BROWN << "FR4G-TP " << this->_name << ": I'm trying sarcasm with you, " << target << ", causing " << damage << " damage points !" << C_RES << std::endl;
	return (damage);
}

int	FragTrap::vaulthunter_dot_exe(std::string const & target)
{
	if (this->_energy_points < 25)
	{
		std::cout << COLOR(69) << "FR4G-TP " << this->_name << " doesn't have enough energy points for the special attack choice !" << C_RES << std::endl;
		return 0;
	}
	int	random = std::rand() % 5;
	attacks attacks[] = {
		&FragTrap::ironyAttack,
		&FragTrap::britishAttack,
		&FragTrap::darkAttack,
		&FragTrap::embarrassingAttack,
		&FragTrap::sarcasmAttack
	};
	std::cout << COLOR(69) << "FR4G-TP " << "......... getting a random special and very funny attack ........." << C_RES << std::endl;
	std::cout << COLOR(69) << "FR4G-TP " << this->_name << " takes 25 damages for special attacking" << C_RES << std::endl;
	this->_energy_points -= 25;
	if (this->_energy_points < 0)
		this->_energy_points = 0;
	this->shoutPoints();
	return ((this->*attacks[random])(target));
}