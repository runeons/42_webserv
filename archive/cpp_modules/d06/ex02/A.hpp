#ifndef A_HPP
# define A_HPP

# include <iostream>
# include "color.hpp"
# include "Base.hpp"

class A : public Base
{
	private:

	public:
		A();
		A(const A & src);
		virtual ~A();

		A		&operator=(const A & src);
};


#endif
