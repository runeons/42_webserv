#ifndef ITER_HPP
# define ITER_HPP

# include <iostream>
# include "color.hpp"

template <typename T>
void	print(T x)
{
	std::cout << SKY_BLUE << x << C_RES << std::endl;
}

template <typename T>
void	iter(T * array, int size, void f(T elem))
{
	for (int i = 0; i < size; i++)
	{
		f(array[i]);
	}
	return ;
}
#endif
