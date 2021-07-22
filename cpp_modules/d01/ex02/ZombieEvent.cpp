#include "ZombieEvent.hpp"
#include <cstdlib>
#include <ctime>
#include <sys/time.h>
#include <unistd.h>

ZombieEvent::ZombieEvent(void) {
	this->_type = "";
	return ;
}

ZombieEvent::~ZombieEvent(void) {
	return ;
}

void	ZombieEvent::setZombieType(std::string type)
{
	this->_type = type;
}

std::string	ZombieEvent::getZombieType(void)
{
	return (this->_type);
}

Zombie	*ZombieEvent::newZombie (std::string name)
{
	Zombie	*zombie1 = new Zombie(name, this->_type);
	return (zombie1);
}

unsigned int hash3(unsigned int h1, unsigned int h2, unsigned int h3)
{
	return ((((h1 * 2654435789U) + h2) * 2654435789U) + h3);
}

Zombie	*ZombieEvent::randomChump(void)
{
	std::string		name;
	Zombie			*new_zombie;
	int				randomNumber;
	struct timeval	time;

	gettimeofday(&time, NULL);
	srand(hash3(time.tv_sec, time.tv_usec, getpid()));
	name = "";
	for (int index = 0; index < 10; index++)
	{
		randomNumber = (std::rand() % 26) + 1;
		randomNumber += 64;
		name += (char)randomNumber;
	}
	new_zombie = newZombie(name);
	new_zombie->announce();
	return (new_zombie);
}
