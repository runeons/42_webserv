# include "NinjaTrap.hpp"

// Default constructor
NinjaTrap::NinjaTrap(void) : ClapTrap()
{
	std::srand(time(NULL));
	this->_hit_points = 60;
	this->_max_hit_points = 60;
	this->_energy_points = 120;
	this->_max_energy_points = 120;
	this->_level = 1;
	this->_name = "unknown";
	this->_melee_attack_damage = 50;
	this->_ranged_attack_damage = 5;
	this->_armor_attack_reduction = 0;
	this->_type = "NINJ4-TP ";
	std::cout << GREY << this->_type << "Default constructor called" << C_RES << std::endl;
	return ;
}

// Copy constructor
NinjaTrap::NinjaTrap(const NinjaTrap& src)
{
	std::cout << GREY << "NINJ4-TP " << "Copy constructor called" << C_RES << std::endl;
	std::srand(time(NULL));
	*this = src;
	return;
}

// Parametric constructor (std::string)
NinjaTrap::NinjaTrap(std::string name) : ClapTrap(name)
{
	std::srand(time(NULL));
	this->_hit_points = 60;
	this->_max_hit_points = 60;
	this->_energy_points = 120;
	this->_max_energy_points = 120;
	this->_level = 1;
	this->_melee_attack_damage = 50;
	this->_ranged_attack_damage = 5;
	this->_armor_attack_reduction = 0;
	this->_type = "NINJ4-TP ";
	std::cout << GREY << this->_type << name << " Std::string constructor called" << C_RES << std::endl;

	return ;
}

// Destructor
NinjaTrap::~NinjaTrap(void)
{
	std::cout << GREY << "NINJ4-TP " << this->_name << " Destructor called" << C_RES << std::endl;
	return;
}

int	NinjaTrap::ninjaShoebox(const ClapTrap & claptrap)
{
	int damage = 3;
	std::cout << COLOR(69) << this->_type << this->_name << ": I'm using a very funny shoebox attack, specially for claptraps like you, " << claptrap.getType() << claptrap.getName() << ", causing " << damage << " damage points !!" << C_RES << std::endl;
	return (damage);
}

int	NinjaTrap::ninjaShoebox(const FragTrap & fragtrap)
{
	int damage = 6;
	std::cout << COLOR(69) << this->_type << this->_name << ": I'm using a very funny shoebox attack, specially for fragtraps like you, " << fragtrap.getType() << fragtrap.getName() << ", causing " << damage << " damage points !!" << C_RES << std::endl;
	return (damage);
}

int	NinjaTrap::ninjaShoebox(const ScavTrap & scavtrap)
{
	int damage = 19;
	std::cout << COLOR(69) << this->_type << this->_name << ": I'm using a very funny shoebox attack, specially for scavtraps like you, " << scavtrap.getType() << scavtrap.getName() << ", causing " << damage << " damage points !!" << C_RES << std::endl;
	return (damage);
}

int	NinjaTrap::ninjaShoebox(const NinjaTrap & ninjatrap)
{
	int damage = 14;
	std::cout << COLOR(69) << this->_type << this->_name << ": I'm using a very funny shoebox attack, specially for ninjatraps like you, " << ninjatrap.getType() << ninjatrap.getName() << ", causing " << damage << " damage points !!" << C_RES << std::endl;
	return (damage);
}
