#ifndef CLAPTRAP_HPP
# define CLAPTRAP_HPP

# include <iostream>
# include <string>
# include <cstdlib>
# include <sstream>
# include "color.hpp"

class ClapTrap
{
	protected:
		int				_hit_points;
		int				_max_hit_points;
		int				_energy_points;
		int				_max_energy_points;
		int				_level;
		std::string		_name;
		int				_melee_attack_damage;
		int				_ranged_attack_damage;
		int				_armor_attack_reduction;
		std::string		_type;

	public:
		ClapTrap();
		ClapTrap(std::string name);
		ClapTrap(const ClapTrap & src);
		~ClapTrap();

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
		std::string				getType(void) const;
		void					setType(const std::string type);

		int						rangedAttack(std::string const & target);
		int						meleeAttack(std::string const & target);

		void					takeDamage(unsigned int amount);
		void					beRepaired(unsigned int amount);
		void					shoutPoints(void);

		ClapTrap				&operator=(const ClapTrap & src);
};


#endif
