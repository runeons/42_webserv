# include "whatever.hpp"

class Awesome {

public:

Awesome( int n ) : _n( n ) {}

bool operator==( Awesome const & rhs ) { return (this->_n == rhs._n); }
bool operator!=( Awesome const & rhs ) { return (this->_n != rhs._n); }
bool operator>( Awesome const & rhs ) { return (this->_n > rhs._n); }
bool operator<( Awesome const & rhs ) { return (this->_n < rhs._n); }
bool operator>=( Awesome const & rhs ) { return (this->_n >= rhs._n); }
bool operator<=( Awesome const & rhs ) { return (this->_n <= rhs._n); }
int	getN(void) const { return this->_n; } ;

private:

int _n;
};

std::ostream &operator<<(std::ostream &os, const Awesome & src)
{
	os << src.getN();
	return (os);
}

int main(void)
{
	std::cout << std::endl;
	std::cout << GREEN_TREE << "_________________________________________________________" << std::endl;
	std::cout << GREEN_TREE << "_____________________ Test with int _____________________" << std::endl;
	std::cout << GREEN_TREE << "_________________________________________________________" << std::endl;
	std::cout << C_RES << std::endl;
	int a = 2;
	int b = 3;
	::swap( a, b );
	std::cout << "a = " << a << ", b = " << b << std::endl;
	std::cout << "min( a, b ) = " << ::min( a, b ) << std::endl;
	std::cout << "max( a, b ) = " << ::max( a, b ) << std::endl;
	std::cout << std::endl;
	std::cout << GREEN_TREE << "_________________________________________________________" << std::endl;
	std::cout << GREEN_TREE << "____________________ Test with string ___________________" << std::endl;
	std::cout << GREEN_TREE << "_________________________________________________________" << std::endl;
	std::cout << C_RES << std::endl;
	std::string c = "chaine1";
	std::string d = "chaine2";
	::swap(c, d);
	std::cout << "c = " << c << ", d = " << d << std::endl;
	std::cout << "min( c, d ) = " << ::min( c, d ) << std::endl;
	std::cout << "max( c, d ) = " << ::max( c, d ) << std::endl;
	std::cout << std::endl;
	std::cout << GREEN_TREE << "_________________________________________________________" << std::endl;
	std::cout << GREEN_TREE << "____________________ Test with class ____________________" << std::endl;
	std::cout << GREEN_TREE << "_________________________________________________________" << std::endl;
	std::cout << C_RES << std::endl;
	Awesome g(3);
	Awesome h(4);
	::swap(g, h);
	std::cout << "g = " << g << ", h = " << h << std::endl;
	std::cout << "min( g, h ) = " << ::min( g, h ) << std::endl;
	std::cout << "max( g, h ) = " << ::max( g, h ) << std::endl;
	std::cout << std::endl;

	return 0;
}

