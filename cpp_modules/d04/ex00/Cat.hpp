#ifndef CAT_HPP
# define CAT_HPP

# include <iostream>
# include <string>
# include <sstream>
# include "color.hpp"
# include "Victim.hpp"

class Cat : public Victim
{
	private:
		Cat();

	public:
		Cat(std::string);
		Cat(const Cat & src);
		virtual ~Cat();

		Cat			&operator=(const Cat & src);
};

std::ostream	&operator<<(std::ostream & os, const Cat & src);

#endif
