#ifndef SPAN_HPP
# define SPAN_HPP

# include <iostream>
# include <string>
# include <vector>
# include <list>
# include <algorithm>
# include <exception>
# include "color.hpp"

class Span
{
	private:
		unsigned int			_n;
		std::vector<int>		_vector;
		Span();

	public:
		Span(unsigned int);
		Span(const Span & src);
		virtual ~Span();

		unsigned int			getN(void) const;
		std::vector<int>		getVector(void) const;

		void					addNumber(int n);
		void					addRange(int first, int last);
		int						shortestSpan(void);
		int						longestSpan(void);

		class NoSpanException : public std::exception
		{
			public:
				virtual const char *what() const throw()
				{ return ("No span - nb int < 2"); }
		};
		class FullClassException : public std::exception
		{
			public:
				virtual const char *what() const throw()
				{ return ("Class is full - can't add another number"); }
		};
		Span					&operator=(const Span & src);
};

std::ostream	&operator<<(std::ostream & os, const Span & src);

#endif
