#ifndef B_HPP
# define B_HPP

# include <iostream>
# include "color.hpp"
# include "Base.hpp"

class B : public Base
{
	private:

	public:
		B();
		B(const B & src);
		virtual ~B();

		B		&operator=(const B & src);
};


#endif
