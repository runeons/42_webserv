# include "FragTrap.hpp"

int main(void)
{
	FragTrap jack("Jack");
	FragTrap robotF("RobotF");

	std::cout << std::endl;
	jack.shoutPoints();
	robotF.shoutPoints();
	std::cout << std::endl;

	robotF.takeDamage(jack.rangedAttack(robotF.getName()));
	std::cout << std::endl;

	robotF.takeDamage(jack.meleeAttack(robotF.getName()));
	std::cout << std::endl;

	robotF.takeDamage(jack.vaulthunter_dot_exe(robotF.getName()));
	std::cout << std::endl;

	robotF.beRepaired(15);
	std::cout << std::endl;

	jack.takeDamage(robotF.vaulthunter_dot_exe(jack.getName()));
	std::cout << std::endl;

	jack.takeDamage(robotF.vaulthunter_dot_exe(jack.getName()));
	std::cout << std::endl;

	jack.takeDamage(robotF.vaulthunter_dot_exe(jack.getName()));
	std::cout << std::endl;

	robotF.beRepaired(150);
	std::cout << std::endl;

	return 0;
}
