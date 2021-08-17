#ifndef ENEMY_HPP
# define ENEMY_HPP

# include <iostream>
# include <string>
# include <sstream>
# include "color.hpp"

class Enemy
{
	protected:
		Enemy();
		int			_hp;
		std::string	_type;
		std::string	_birth_msg;
		std::string	_death_msg;

	public:
		Enemy(int hp, std::string const & type);
		Enemy(const Enemy & src);
		virtual ~Enemy();

		int			getHp(void) const;
		void		setHp(const int hp);
		std::string	getType(void) const;
		void		setType(const std::string type);
		std::string	getBirthMsg(void) const;
		void		setBirthMsg(const std::string birth_msg);
		std::string	getDeathMsg(void) const;
		void		setDeathMsg(const std::string death_msg);

		virtual void	takeDamage(int damage);

		Enemy		&operator=(const Enemy & src);
};

std::ostream	&operator<<(std::ostream & os, const Enemy & src);

#endif
