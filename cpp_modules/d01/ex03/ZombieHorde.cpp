#include <cstdlib>
#include <ctime>
#include <sys/time.h>
#include <unistd.h>
#include "ZombieHorde.hpp"

ZombieHorde::ZombieHorde(long n) {
	long	i;

	if (n < 0 || n > 2147483647)
	{
		std::cout << YELLOW << "Je ne peux pas créer une horde de " << n << " zombies" << C_RES << std::endl;
		n = 0;
	}
	this->_horde = new Zombie[n];
	this->_nb_zombies = n;
	std::cout << GREEN << "Appel au constructeur d'une horde de " << n << " zombies" << C_RES << std::endl;
	i = -1;
	while (++i < n)
		this->_horde[i].set_name(randomName());
	return ;
}

ZombieHorde::~ZombieHorde(void) {
	std::cout << RED << "Appel au destructeur d'une horde de " << this->_nb_zombies << " zombies" << C_RES << std::endl;
	delete [] this->_horde;
	return ;
}

unsigned int hash3(unsigned int h1, unsigned int h2, unsigned int h3)
{
	return ((((h1 * 2654435789U) + h2) * 2654435789U) + h3);
}

std::string	ZombieHorde::randomName(void)
{
	std::string		name;
	int				randomNumber;
	struct timeval	time;

	gettimeofday(&time, NULL);
	srand(hash3(time.tv_sec, time.tv_usec, getpid()));
	name = "";
	for (int index = 0; index < 10; index++)
	{
		usleep(1);
		randomNumber = (std::rand() % 26) + 1;
		randomNumber += 64;
		name += (char)randomNumber;
	}
	return (name);
}

void	ZombieHorde::announce(void)
{
	int	i;

	i = -1;
	while (++i < this->_nb_zombies)
	{
		this->_horde[i].announce();
	}
}
