#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

# include <iostream>
# include <algorithm>
# include <stack>
# include <deque>
# include "color.hpp"

// template <class T, class Container = deque<T> > class stack;
template < typename T >
class MutantStack : public std::stack<T>
{
	private:

	public:
		typedef typename std::stack<T>::container_type::iterator iterator;
		typedef typename std::stack<T>::container_type::reverse_iterator reverse_iterator;

		iterator begin() { return std::stack<T>::c.begin(); }
		iterator end() { return std::stack<T>::c.end(); }
		reverse_iterator rbegin() { return std::stack<T>::c.rbegin(); }
		reverse_iterator rend() { return std::stack<T>::c.rend(); }

		MutantStack() : std::stack<T>() {};
		MutantStack(const MutantStack & src) : std::stack<T>(src) {};
		virtual ~MutantStack() {};

		MutantStack&operator=(const MutantStack & src)
		{
			std::stack<T>::operator=(src);
			return (*this);
		};
};

#endif
