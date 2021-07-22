# include "iter.hpp"

/*
	Écrivez un fonction template iter qui prend 3 paramètres et ne renvoie rien.

	Le premier paramètre correspond à l’adresse d’un array, le second sa taille,
	et la troisième une fonction de type void, à appeler sur chaque élément de l’array.

	Rendez un main prouvant que votre iter marche avec n’importe quel type d’array et/ou
	avec une instance de fonction template en 3ème paramètre.
*/

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

void	display(int i)
{
	std::cout << i << std::endl;
}

void	display(std::string s)
{
	std::cout << s << std::endl;
}

void	display(Awesome a)
{
	std::cout << a << std::endl;
}

int main(void)
{
	int arr_int[4] = { 0, 1, 2, 3 };
	std::string arr_str[3] = { "abc", "def", "ghi" };
	Awesome arr_class[5] = { Awesome(7), Awesome(8), Awesome(9), Awesome(10), Awesome(11) };

	std::cout << CORAIL << std::endl;
	std::cout << "____________ TESTS WITHOUT TEMPLATE FONCTION ____________" << C_RES;

	std::cout << GREEN_TREE << std::endl;
	std::cout << "_________________________________________________________" << std::endl;
	std::cout << "___________________ Iter display(int) ___________________" << std::endl;
	std::cout << "_________________________________________________________" << std::endl;
	std::cout << C_RES << std::endl;
	iter(arr_int, 4, display);

	std::cout << GREEN_TREE << std::endl;
	std::cout << "_________________________________________________________" << std::endl;
	std::cout << "_______________ Iter display(std::string) _______________" << std::endl;
	std::cout << "_________________________________________________________" << std::endl;
	std::cout << C_RES << std::endl;
	iter(arr_str, 3, display);

	std::cout << GREEN_TREE << std::endl;
	std::cout << "_________________________________________________________" << std::endl;
	std::cout << "__________________ Iter display(class) __________________" << std::endl;
	std::cout << "_________________________________________________________" << std::endl;
	std::cout << C_RES << std::endl;
	iter(arr_class, 5, display);

	std::cout << CORAIL << std::endl;
	std::cout << "______________ TESTS WITH TEMPLATE FONCTION _____________" << C_RES;

	std::cout << GREEN_TREE << std::endl;
	std::cout << "_________________________________________________________" << std::endl;
	std::cout << "______________________ Iter print(T) ____________________" << std::endl;
	std::cout << "_________________________________________________________" << std::endl;
	std::cout << C_RES << std::endl;
	iter(arr_int, 4, print);

	std::cout << GREEN_TREE << std::endl;
	std::cout << "_________________________________________________________" << std::endl;
	std::cout << "______________________ Iter print(T) ____________________" << std::endl;
	std::cout << "_________________________________________________________" << std::endl;
	std::cout << C_RES << std::endl;
	iter(arr_str, 3, print);

	std::cout << GREEN_TREE << std::endl;
	std::cout << "_________________________________________________________" << std::endl;
	std::cout << "____________________ Iter print(class) __________________" << std::endl;
	std::cout << "_________________________________________________________" << std::endl;
	std::cout << C_RES << std::endl;
	iter(arr_class, 5, print);

	std::cout << std::endl;
	return 0;
}
