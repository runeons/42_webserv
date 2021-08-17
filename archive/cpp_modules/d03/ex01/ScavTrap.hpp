#ifndef SCAVTRAP_HPP
# define SCAVTRAP_HPP

# include <iostream>
# include <string>
# include <sstream>
# include "color.hpp"

class ScavTrap
{
	private:
		int						_hit_points;
		static const int		_max_hit_points = 100;
		int						_energy_points;
		static const int		_max_energy_points = 50;
		int						_level;
		std::string				_name;
		static const int		_melee_attack_damage = 20;
		static const int		_ranged_attack_damage = 15;
		static const int		_armor_attack_reduction = 3;


	public:
		ScavTrap();
		ScavTrap(std::string);
		ScavTrap(const ScavTrap & src);
		~ScavTrap();

		int						getHitPoints(void) const;
		void					setHitPoints(const int hit_points);
		int						getMaxHitPoints(void) const;
		void					setMaxHitPoints(const int max_hit_points);
		int						getEnergyPoints(void) const;
		void					setEnergyPoints(const int energy_points);
		int						getMaxEnergyPoints(void) const;
		void					setMaxEnergyPoints(const int max_energy_points);
		int						getLevel(void) const;
		void					setLevel(const int level);
		std::string				getName(void) const;
		void					setName(const std::string name);
		int						getMeleeAttackDamage(void) const;
		void					setMeleeAttackDamage(const int melee_attack_damage);
		int						getRangedAttackDamage(void) const;
		void					setRangedAttackDamage(const int ranged_attack_damage);
		int						getArmorAttackReduction(void) const;
		void					setArmorAttackReduction(const int armor_attack_reduction);

		int						rangedAttack(std::string const & target);
		int						meleeAttack(std::string const & target);
		void					takeDamage(unsigned int amount);
		void					beRepaired(unsigned int amount);
		void					shoutPoints(void);

		void					challTreeClimb(std::string const & target);
		void					challPoemLearn(std::string const & target);
		void					challSongSing(std::string const & target);
		void					challengeNewcomer(std::string const & target);

		ScavTrap				&operator=(const ScavTrap & src);
};


#endif
