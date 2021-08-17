#ifndef CONVERT_HPP
# define CONVERT_HPP

# include <iostream>
# include <iomanip>
# include <stdlib.h>
# include "color.hpp"

class Convert
{
	private:
		double		_value;
		double		_precision;
		std::string	_litteral;
		Convert();

	public:
		Convert(std::string litteral);
		Convert(const Convert & src);
		virtual ~Convert();

		double		getValue(void) const;
		double		getPrecision(void) const;
		std::string	getLitteral(void) const;

		class NotValidFormat : public std::exception
		{
			public:
				virtual const char *what() const throw()
				{ return ("Not a valid format for number"); }
		};

		void		toChar(void);
		void		toInt(void);
		void		toFloat(void);
		void		toDouble(void);

		bool		isNan(void);
		bool		isInf(void);
		bool		isNeg(void);
		void		fillValue(void);
		void		checkInput(void);
		void		convert(void);

		Convert		&operator=(const Convert & src);
};

#endif
