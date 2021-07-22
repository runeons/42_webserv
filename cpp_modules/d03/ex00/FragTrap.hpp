#ifndef FRAGTRAP_HPP
# define FRAGTRAP_HPP

# include <iostream>
# include <string>
# include <sstream>
# include <cstdlib>
# include "color.hpp"

class FragTrap
{
	private:
		int						_hit_points;
		static const int		_max_hit_points = 100;
		int						_energy_points;
		static const int		_max_energy_points = 100;
		int						_level;
		std::string				_name;
		static const int		_melee_attack_damage = 30;
		static const int		_ranged_attack_damage = 20;
		static const int		_armor_attack_reduction = 5;

	public:
		FragTrap();
		FragTrap(std::string);
		FragTrap(const FragTrap & src);
		~FragTrap();

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

		int						ironyAttack(std::string const & target);
		int						britishAttack(std::string const & target);
		int						darkAttack(std::string const & target);
		int						embarrassingAttack(std::string const & target);
		int						sarcasmAttack(std::string const & target);
		int						vaulthunter_dot_exe(std::string const & target);

		FragTrap				&operator=(const FragTrap & src);
};


#endif
