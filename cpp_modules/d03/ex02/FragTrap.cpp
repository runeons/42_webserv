# include "FragTrap.hpp"

typedef int(FragTrap::* attacks) (std::string const & target);

// Default constructor
FragTrap::FragTrap(void) : ClapTrap()
{
	std::srand(time(NULL));
	this->_hit_points = 100;
	this->_max_hit_points = 100;
	this->_energy_points = 100;
	this->_max_energy_points = 100;
	this->_level = 1;
	this->_name = "unknown";
	this->_melee_attack_damage = 30;
	this->_ranged_attack_damage = 20;
	this->_armor_attack_reduction = 5;
	this->_type = "FR4G-TP ";
	std::cout << GREY << this->_type << "Default constructor called" << C_RES << std::endl;
	return ;
}

// Copy constructor
FragTrap::FragTrap(const FragTrap& src)
{
	std::cout << GREY << this->_type << "Copy constructor called" << C_RES << std::endl;
	std::srand(time(NULL));
	*this = src;
	return;
}

// Parametric constructor (std::string)
FragTrap::FragTrap(std::string name) : ClapTrap(name)
{
	std::srand(time(NULL));
	this->_hit_points = 100;
	this->_max_hit_points = 100;
	this->_energy_points = 100;
	this->_max_energy_points = 100;
	this->_level = 1;
	this->_melee_attack_damage = 30;
	this->_ranged_attack_damage = 20;
	this->_armor_attack_reduction = 5;
	this->_type = "FR4G-TP ";
	std::cout << GREY << this->_type << name << " Std::string constructor called" << C_RES << std::endl;

	return ;
}

// Destructor
FragTrap::~FragTrap(void)
{
	std::cout << GREY << this->_type << this->_name << " Destructor called" << C_RES << std::endl;
	return;
}

int FragTrap::ironyAttack(std::string const & target)
{
	int	damage = 9;
	std::cout << BROWN << this->_type << this->_name << ": I'm trying an ironical joke on you, " << target << ", causing " << damage << " damage points !" << C_RES << std::endl;
	return (damage);
}

int FragTrap::britishAttack(std::string const & target)
{
	int	damage = 2;
	std::cout << BROWN << this->_type << this->_name << ": I'm trying British Humour with you, " << target << ", causing " << damage << " damage points !" << C_RES << std::endl;
	return (damage);
}

int FragTrap::darkAttack(std::string const & target)
{
	int	damage = 4;
	std::cout << BROWN << this->_type << this->_name << ": I'm trying an very very dark joke on you, " << target << ", causing " << damage << " damage points !" << C_RES << std::endl;
	return (damage);
}

int FragTrap::embarrassingAttack(std::string const & target)
{
	int	damage = 5;
	std::cout << BROWN << this->_type << this->_name << ": I'm trying an embarrassing joke on you, " << target << ", causing " << damage << " damage points !" << C_RES << std::endl;
	return (damage);
}

int FragTrap::sarcasmAttack(std::string const & target)
{
	int	damage = 19;
	std::cout << BROWN << this->_type << this->_name << ": I'm trying sarcasm with you, " << target << ", causing " << damage << " damage points !" << C_RES << std::endl;
	return (damage);
}

int	FragTrap::vaulthunter_dot_exe(std::string const & target)
{
	if (this->_energy_points < 25)
	{
		std::cout << COLOR(69) << this->_type << this->_name << " doesn't have enough energy points for the special attack choice !" << C_RES << std::endl;
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
	std::cout << COLOR(69) << this->_type << "......... getting a random special and very funny attack ........." << C_RES << std::endl;
	std::cout << COLOR(69) << this->_type << this->_name << " takes 25 damages for special attacking" << C_RES << std::endl;
	this->_energy_points -= 25;
	if (this->_energy_points < 0)
		this->_energy_points = 0;
	this->shoutPoints();
	return ((this->*attacks[random])(target));
}