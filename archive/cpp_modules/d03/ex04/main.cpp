# include "FragTrap.hpp"
# include "ScavTrap.hpp"
# include "ClapTrap.hpp"
# include "NinjaTrap.hpp"
# include "SuperTrap.hpp"

int main(void)
{
	ClapTrap robotC("RobotC");
	FragTrap jack("Jack");
	FragTrap unknownF;
	FragTrap robotF("RobotF");
	ScavTrap robotS("RobotS");
	ScavTrap unknownS;
	NinjaTrap robotN("RobotN");
	SuperTrap robotSup("RobotSup");

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

	std::cout << "- - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
	robotF.shoutPoints();
	robotS.shoutPoints();
	unknownF.shoutPoints();
	unknownS.shoutPoints();
	jack.shoutPoints();
	robotN.shoutPoints();
	robotSup.shoutPoints();

	std::cout << std::endl;
	jack.takeDamage(robotSup.ninjaShoebox(jack));
	std::cout << std::endl;
	jack.takeDamage(robotSup.ninjaShoebox(jack));
	std::cout << std::endl;
	jack.takeDamage(robotSup.vaulthunter_dot_exe(jack.getName()));
	std::cout << std::endl;
	robotS.takeDamage(robotSup.vaulthunter_dot_exe("robotS"));
	std::cout << std::endl;
	robotF.takeDamage(robotSup.vaulthunter_dot_exe(robotF.getName()));
	std::cout << std::endl;

	std::cout << "- - melee attacks - -" << std::endl;
	robotSup.takeDamage(robotF.meleeAttack(jack.getName()));
	std::cout << std::endl;
	robotSup.takeDamage(robotN.meleeAttack(jack.getName()));
	std::cout << std::endl;
	jack.takeDamage(robotSup.meleeAttack(jack.getName()));
	std::cout << std::endl;

	std::cout << "- - ranged attacks - -" << std::endl;
	robotSup.takeDamage(robotF.rangedAttack(jack.getName()));
	std::cout << std::endl;
	robotSup.takeDamage(robotN.rangedAttack(jack.getName()));
	std::cout << std::endl;
	jack.takeDamage(robotSup.rangedAttack(jack.getName()));
	std::cout << std::endl;


	return 0;
}
