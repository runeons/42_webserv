#ifndef D_HPP
# define D_HPP

# include <iostream>
# include "color.hpp"
# include "Base.hpp"

class D : public Base
{
	private:

	public:
		D();
		D(const D & src);
		virtual ~D();

		D		&operator=(const D & src);
};


#endif
