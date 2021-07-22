#ifndef ZOMBIE_HORDE_HPP
# define ZOMBIE_HORDE_HPP
# include "Zombie.hpp"

// DECLARATION
class ZombieHorde
{
	private:
		Zombie	*_horde;
		int		_nb_zombies;
	public:
		std::string	randomName(void);
		void	announce(void);
		ZombieHorde(long n);
		~ZombieHorde();
};
#endif