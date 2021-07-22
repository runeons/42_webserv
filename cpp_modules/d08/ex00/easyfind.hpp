#ifndef EASYFIND_HPP
# define EASYFIND_HPP

# include <iostream>
# include <algorithm>
# include <list>
# include <vector>
# include "color.hpp"

template <typename T>
int easyfind(T int_cont, int to_find)
{
	typedef typename T::iterator iterator;
	iterator it = std::find(int_cont.begin(), int_cont.end(), to_find);

	if (it != int_cont.end())
		return (*it);
	else
		return (-1);
}

#endif
