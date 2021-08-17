# include "FragTrap.hpp"
# include "ScavTrap.hpp"

int main(void)
{
	FragTrap jack("Jack");
	FragTrap robotF("RobotF");
	ScavTrap robotS("RobotS");

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

	std::cout << "- - - - - - - - - - - - - - - - - - - - - - -" << std::endl;

	robotF.shoutPoints();
	robotS.shoutPoints();
	jack.shoutPoints();
	std::cout << std::endl;

	robotS.takeDamage(robotF.rangedAttack(robotS.getName()));
	std::cout << std::endl;

	jack.takeDamage(robotS.rangedAttack(jack.getName()));
	std::cout << std::endl;

	robotS.challengeNewcomer(jack.getName());
	std::cout << std::endl;

	robotS.takeDamage(jack.rangedAttack(robotS.getName()));
	std::cout << std::endl;

	robotS.takeDamage(jack.meleeAttack(robotS.getName()));
	std::cout << std::endl;

	return 0;
}
