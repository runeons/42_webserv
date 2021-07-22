# include "Span.hpp"

Span::Span(const Span& src)
{
	*this = src;
	return;
}

Span::Span(unsigned int n) : _n(n)
{
	return ;
}

Span::~Span(void)
{
	return;
}

Span &	Span::operator=(const Span& rhs)
{
	if (this != &rhs)
	{
		this->_n = rhs.getN();
		this->_vector = rhs.getVector();
	}
	return (*this);
}

unsigned int Span::getN(void) const
{
	return (this->_n);
}

std::vector<int> Span::getVector(void) const
{
	return (this->_vector);
}

void Span::addNumber(int n)
{
	try
	{
		if (this->_vector.size() >= this->_n)
			throw Span::FullClassException();
		else
			this->_vector.push_back(n);
	}
	catch (Span::FullClassException & e)
	{
		std::cout << RED_B << "Error:" << WHITE_B << " class is full - can't add another number" <<  C_RES << std::endl;
	}
	return ;
}

/*
	template <class InputIterator>
	void insert (iterator position, InputIterator first, InputIterator last);
*/

void Span::addRange(int first, int last)
{
	std::cout << GREY << "... adding range ..." << std::endl;
	/// CREATE NEW VECTOR //////////////////////////////////////////////
	unsigned int new_v_size;
	unsigned int final_v_size;
	int	reverse = 0;
	if (first > last)
	{
		reverse = 1;
		std::swap(first, last);
	}
	new_v_size = last - first + 1;
	final_v_size = new_v_size + static_cast<unsigned int>(this->_vector.size());
	if (final_v_size > this->_n)
		new_v_size = this->_n - static_cast<unsigned int>(this->_vector.size());
	std::vector<int> new_v(new_v_size);
	for (unsigned long i = 0; i < new_v.size(); i++)
		new_v[i] = first + i;
	if (reverse == 1)
		std::reverse(new_v.begin(), new_v.end());
	//// INSERT TO MY VECTOR ///////////////////////////////////////////
	std::vector<int>::iterator itpos = this->_vector.end();
	std::vector<int>::iterator itfirst = new_v.begin();
	std::vector<int>::iterator itlast = new_v.end();

	this->_vector.insert(itpos, itfirst, itlast);
	try
	{
		if (final_v_size > this->_n)
			throw Span::FullClassException();
	}
	catch (Span::FullClassException & e)
	{
		std::cout << RED_B << "Error:" << WHITE_B << " class is full - can't add another number" <<  C_RES << std::endl;
	}
	return;
}

int Span::shortestSpan(void)
{
	try
	{
		if (this->_vector.size() < 2)
			throw Span::NoSpanException();
		else
		{
			int diff = Span::longestSpan();
			std::vector<int> tmp = this->_vector;
			std::sort(tmp.begin(), tmp.end());

			std::vector<int>::iterator it;
			std::vector<int>::iterator itend = tmp.end();
			for (it = tmp.begin(); it != (itend - 1); it++)
			{
				if (std::abs(*it - *(it + 1)) < diff)
					diff = std::abs(*it - *(it + 1));
			}
			return diff;
		}
	}
	catch (Span::NoSpanException & e)
	{
		std::cout << RED_B << "Error:" << WHITE_B << " no span (nb int < 2)" <<  C_RES << std::endl;
		return (0);
	}
}

int Span::longestSpan(void)
{
	try
	{
		if (this->_vector.size() < 2)
			throw Span::NoSpanException();
		else
		{
			int min = *(std::min_element(this->_vector.begin(), this->_vector.end()));
			int max = *(std::max_element(this->_vector.begin(), this->_vector.end()));
			return (max - min);
		}
	}
	catch (Span::NoSpanException & e)
	{
		std::cout << RED_B << "Error:" << WHITE_B << " no span (nb int < 2)" <<  C_RES << std::endl;
		return (0);
	}
}

std::ostream &operator<<(std::ostream &os, const Span & src)
{
	std::vector<int> vec;
	vec = src.getVector();
	if (vec.size() == 0)
	{
		os << BROWN << "[]" << std::endl;
		return (os);
	}
	std::vector<int>::iterator it;
	std::vector<int>::iterator itend = vec.end();
	os << BROWN << "[ ";
	for (it = vec.begin(); it != (itend - 1); it++)
		os << *it << " ";
	os << *it << " ]" << C_RES << std::endl;
	return (os);
}
