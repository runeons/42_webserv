# include "SuperTrap.hpp"

// Default constructor
SuperTrap::SuperTrap(void) : ClapTrap()
{
	NinjaTrap tmpN("tmpN");
	FragTrap tmpF("tmpF");

	std::srand(time(NULL));
	this->_hit_points = tmpF.getHitPoints();
	this->_max_hit_points = tmpF.getMaxHitPoints();
	this->_energy_points = tmpN.getEnergyPoints();
	this->_max_energy_points = tmpN.getMaxEnergyPoints();
	this->_level = 1;
	this->_name = "unknown";
	this->_melee_attack_damage = tmpN.getMeleeAttackDamage();
	this->_ranged_attack_damage = tmpF.getRangedAttackDamage();
	this->_armor_attack_reduction = tmpF.getArmorAttackReduction();
	this->_type = "SUP3R-TP ";
	std::cout << GREY << this->_type << "Default constructor called" << C_RES << std::endl;
	return ;
}

// Copy constructor
SuperTrap::SuperTrap(const SuperTrap& src)
{
	std::cout << GREY << "SUP3R-TP " << "Copy constructor called" << C_RES << std::endl;
	std::srand(time(NULL));
	*this = src;
	return;
}


// Parametric constructor (std::string)
SuperTrap::SuperTrap(std::string name) : ClapTrap(name), FragTrap(name), NinjaTrap(name)
{
	NinjaTrap tmpN("tmpN");
	FragTrap tmpF("tmpF");

	std::srand(time(NULL));
	this->_hit_points = tmpF.getHitPoints();
	this->_max_hit_points = tmpF.getMaxHitPoints();
	this->_energy_points = tmpN.getEnergyPoints();
	this->_max_energy_points = tmpN.getMaxEnergyPoints();
	this->_level = 1;
	this->_melee_attack_damage = tmpN.getMeleeAttackDamage();
	this->_ranged_attack_damage = tmpF.getRangedAttackDamage();
	this->_armor_attack_reduction = tmpF.getArmorAttackReduction();
	this->_type = "SUP3R-TP ";
	std::cout << GREY << this->_type << name << " Std::string constructor called" << C_RES << std::endl;
	return ;
}

// Destructor
SuperTrap::~SuperTrap(void)
{
	std::cout << GREY << "SUP3R-TP " << this->_name << " Destructor called" << C_RES << std::endl;
	return;
}

int SuperTrap::rangedAttack(std::string const &target)
{
	return (FragTrap::rangedAttack(target));
}

int SuperTrap::meleeAttack(std::string const &target)
{
	return (NinjaTrap::meleeAttack(target));
}