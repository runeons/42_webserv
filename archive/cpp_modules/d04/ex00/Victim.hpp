#ifndef VICTIM_HPP
# define VICTIM_HPP

# include <iostream>
# include <string>
# include <sstream>
# include "color.hpp"

class Victim
{
	private:

	protected:
		std::string	_name;
		std::string	_polym_msg;
		Victim();

	public:
		Victim(std::string);
		Victim(const Victim & src);
		virtual ~Victim();

		std::string		getName(void) const;
		void			setName(const std::string name);

		virtual void	getPolymorphed(void) const;
		std::string		introduce(void) const;

		Victim			&operator=(const Victim & src);
};

std::ostream	&operator<<(std::ostream & os, const Victim & src);

#endif
