#ifndef ARRAY_HPP
# define ARRAY_HPP

# include <iostream>
# include "color.hpp"

template <typename T>
class Array
{
	private:
		T *				_array;
		unsigned int	_size;

	public:
		Array() {
			this->_array = new T[0];
			this->_size = 0;
			return ;
		};
		Array(unsigned int n) {
			this->_array = new T[n];
			this->_size = n;
			return ;
		};
		Array(const Array & src)
		{
			this->_size = src._size;
			this->_array = NULL;
			this->operator=(src);
			// *this = src;
			return ;
		};
		virtual ~Array() { delete [] this->_array; return ; };

		class OutOfBoundaries : public std::exception
		{
			public:
				virtual const char *what() const throw()
				{ return ("index is out of boundaries"); }
		};

		unsigned int	size(void) const 					{ return (this->_size); } ;
		T &operator[](int i) const {
			if (static_cast<unsigned int>(i) >= this->_size || i < 0)
				throw Array::OutOfBoundaries();
			else
				return (this->_array[i]);
		};
		Array	&operator=(const Array & src)
		{
			if (this != &src)
			{
				if (this->_array)
					this->~Array();
				this->_size = src._size;
				this->_array = new T[this->_size];
				for (unsigned int i = 0; i < this->_size; i++)
					this->_array[i] = src._array[i];
			}
			return (*this);
		};
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const Array < T > & src)
{
	if (src.size() == 0)
	{
		os << SKY_BLUE << "[]";
		return (os);
	}
	os << SKY_BLUE << "[ ";
	for (unsigned int i = 0; i < src.size() - 1; i++)
		os << src[i] << " - ";
	os << src[src.size() - 1] << " ]" << C_RES;
	return (os);
}

#endif
