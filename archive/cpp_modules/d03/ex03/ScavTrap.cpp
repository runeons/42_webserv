# include "ScavTrap.hpp"

typedef void(ScavTrap::* challenges) (std::string const & target);

// Default constructor
ScavTrap::ScavTrap(void) : ClapTrap()
{
	std::srand(time(NULL));
	this->_hit_points = 100;
	this->_max_hit_points = 100;
	this->_energy_points = 50;
	this->_max_energy_points = 50;
	this->_level = 1;
	this->_name = "unknown";
	this->_melee_attack_damage = 20;
	this->_ranged_attack_damage = 15;
	this->_armor_attack_reduction = 3;
	this->_type = "SC4V-TP ";
	std::cout << GREY << this->_type << "Default constructor called" << C_RES << std::endl;
	return ;
}

// Copy constructor
ScavTrap::ScavTrap(const ScavTrap& src)
{
	std::cout << GREY << "SC4V-TP " << "Copy constructor called" << C_RES << std::endl;
	std::srand(time(NULL));
	*this = src;
	return;
}

// Parametric constructor (std::string)
ScavTrap::ScavTrap(std::string name) : ClapTrap(name)
{
	std::srand(time(NULL));
	this->_hit_points = 100;
	this->_max_hit_points = 100;
	this->_energy_points = 50;
	this->_max_energy_points = 50;
	this->_level = 1;
	this->_melee_attack_damage = 20;
	this->_ranged_attack_damage = 15;
	this->_armor_attack_reduction = 3;
	this->_type = "SC4V-TP ";
	std::cout << GREY << this->_type << name << " Std::string constructor called" << C_RES << std::endl;

	return ;
}

// Destructor
ScavTrap::~ScavTrap(void)
{
	std::cout << GREY << this->_type << this->_name << " Destructor called" << C_RES << std::endl;
	return;
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