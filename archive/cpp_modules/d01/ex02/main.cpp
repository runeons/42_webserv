#include "ZombieEvent.hpp"

int		main (void)
{
	Zombie*		zombie1;
	Zombie*		zombie2;
	Zombie*		zombie3;
	Zombie*		zombie4;
	Zombie*		zombie5;
	Zombie*		zombie6;
	Zombie*		zombie7;
	Zombie*		zombie8;
	ZombieEvent	zombie_event;

	std::cout << std::endl << "________________________ create a zombie via simple \'new\' ________________________" << std::endl << std::endl;
	zombie1 = new Zombie("n1", "social");
	zombie1->announce();

	std::cout << std::endl;
	std::cout << std::endl << "_____________________ create Zombie2 via ZombieEvent newZombie _____________________" << std::endl << std::endl;
	zombie2 = zombie_event.newZombie("n2");
	zombie1->announce();
	zombie2->announce();

	std::cout << std::endl;
	std::cout << std::endl << "__________________________________ set event type __________________________________" << std::endl << std::endl;
	zombie_event.setZombieType("toxic");

	std::cout << std::endl << "_____________________ create Zombie3 via ZombieEvent newZombie _____________________" << std::endl << std::endl;
	zombie3 = zombie_event.newZombie("n3");
	zombie1->announce();
	zombie2->announce();
	zombie3->announce();

	std::cout << std::endl;
	std::cout << std::endl << "_____________________ create Zombie4 via ZombieEvent newZombie _____________________" << std::endl << std::endl;
	zombie4 = zombie_event.newZombie("n4");
	zombie1->announce();
	zombie2->announce();
	zombie3->announce();
	zombie4->announce();

	std::cout << std::endl;
	std::cout << std::endl << "___________________________________ update type ____________________________________" << std::endl << std::endl;
	zombie_event.setZombieType("psychiatric");

	std::cout << std::endl << "_____________________ create Zombie5 via ZombieEvent newZombie _____________________" << std::endl << std::endl;
	zombie5 = zombie_event.newZombie("n5");
	zombie1->announce();
	zombie2->announce();
	zombie3->announce();
	zombie4->announce();
	zombie5->announce();

	std::cout << std::endl;
	std::cout << std::endl << "_____________________ create Zombie6 via ZombieEvent newZombie _____________________" << std::endl << std::endl;
	zombie6 = zombie_event.newZombie("n6");
	zombie1->announce();
	zombie2->announce();
	zombie3->announce();
	zombie4->announce();
	zombie5->announce();
	zombie6->announce();

	std::cout << std::endl;
	std::cout << std::endl << "______________ create Zombie7 and Zombie8 via ZombieEvent randomChump ______________" << std::endl << std::endl;
	zombie1->announce();
	zombie2->announce();
	zombie3->announce();
	zombie4->announce();
	zombie5->announce();
	zombie6->announce();
	zombie7 = zombie_event.randomChump();
	zombie8 = zombie_event.randomChump();

	std::cout << std::endl;
	delete(zombie1);
	delete(zombie2);
	delete(zombie3);
	delete(zombie4);
	delete(zombie5);
	delete(zombie6);
	delete(zombie7);
	delete(zombie8);
	return (0);
}