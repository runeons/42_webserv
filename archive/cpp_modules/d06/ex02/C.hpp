#ifndef C_HPP
# define C_HPP

# include <iostream>
# include "color.hpp"
# include "Base.hpp"

class C : public Base
{
	private:

	public:
		C();
		C(const C & src);
		virtual ~C();

		C		&operator=(const C & src);
};


#endif
