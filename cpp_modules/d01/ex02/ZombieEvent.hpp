#ifndef ZOMBIE_EVENT_HPP
# define ZOMBIE_EVENT_HPP
# include "Zombie.hpp"

// DECLARATION

class ZombieEvent
{
	private:
		std::string	_type;
	public:
		void	setZombieType(std::string type);
		std::string getZombieType(void);
		Zombie	*newZombie (std::string name);
		Zombie	*randomChump(void);

		ZombieEvent(void);
		~ZombieEvent(void);
};
#endif