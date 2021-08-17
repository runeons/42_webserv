#ifndef FIXED_HPP
# define FIXED_HPP

#include <iostream>
#include <fstream>
#include <cmath>
#include "color.hpp"

class Fixed
{
	private:
		int 				_rawBits;
		static const int	_fractBits = 8;

	public:
		Fixed();
		Fixed(int n);
		Fixed(const float f);
		Fixed(const Fixed & src);
		~Fixed();

		int				getRawBits(void) const;
		void			setRawBits(int const raw);

		Fixed			&operator=(const Fixed & src);

		float			toFloat(void) const;
		int				toInt(void) const;
};

std::ostream	&operator<<(std::ostream & os, const Fixed & src);

#endif