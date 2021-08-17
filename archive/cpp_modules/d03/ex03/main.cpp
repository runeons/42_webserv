# include "FragTrap.hpp"
# include "ScavTrap.hpp"
# include "ClapTrap.hpp"
# include "NinjaTrap.hpp"

int main(void)
{
	ClapTrap robotC("RobotC");
	FragTrap jack("Jack");
	FragTrap unknownF;
	FragTrap robotF("RobotF");
	ScavTrap robotS("RobotS");
	ScavTrap unknownS;
	NinjaTrap robotN("RobotN");

	std::cout << std::endl;
	jack.shoutPoints();
	robotF.shoutPoints();
	unknownF.shoutPoints();
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
	unknownF.shoutPoints();
	unknownS.shoutPoints();
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

	std::cout << "- - - - - - - - - - - - - - - - - - - - - - -" << std::endl;

	robotF.shoutPoints();
	robotS.shoutPoints();
	unknownF.shoutPoints();
	unknownS.shoutPoints();
	jack.shoutPoints();
	robotN.shoutPoints();
	std::cout << std::endl;
	jack.takeDamage(robotN.ninjaShoebox(jack));
	robotC.takeDamage(robotN.ninjaShoebox(robotC));
	robotF.takeDamage(robotN.ninjaShoebox(robotF));
	robotS.takeDamage(robotN.ninjaShoebox(robotS));
	robotN.takeDamage(robotN.ninjaShoebox(robotN));
	std::cout << std::endl;

	return 0;
}
