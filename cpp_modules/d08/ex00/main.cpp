# include "easyfind.hpp"

void	displayInt(int i)
{
	std::cout << SKY_BLUE << i << std::endl;
}

int main(void)
{
	std::cout << GREEN_TREE << std::endl << "________________ EASY FIND ________________" << std::endl << C_RES << std::endl;
	int	to_find = 42;
	int arr[] = { 1, 4, 67, 12, 42, 92, 7 };

	std::cout << GREEN_TREE << std::endl << "________________ W/ VECTOR ________________" << std::endl << C_RES << std::endl;
	std::vector<int> v1(arr, arr + 7);
	std::cout << WHITE << "... display initial container ..." << std::endl;
	std::for_each(v1.begin(), v1.end(), displayInt);
	std::cout << CORAIL << "Return 42's first occurence in container : " << easyfind(v1, to_find) << std::endl;

	std::cout << WHITE << "... remove 42 from container ..." << std::endl;
	v1.erase(v1.begin() + 4);
	std::for_each(v1.begin(), v1.end(), displayInt);
	std::cout << CORAIL << "Return 42's first occurence in container : " << easyfind(v1, to_find) << std::endl;

	std::cout << WHITE << "... insert 42 at front ..." << std::endl;
	v1.insert(v1.begin(), 42);
	std::for_each(v1.begin(), v1.end(), displayInt);
	std::cout << CORAIL << "Return 42's first occurence in container : " << easyfind(v1, to_find) << std::endl;

	std::cout << GREEN_TREE << std::endl << "________________ W/ LIST __________________" << std::endl << C_RES << std::endl;
	std::list<int> lst1(arr, arr + 7);
	std::cout << WHITE << "... display initial container ..." << std::endl;
	std::for_each(lst1.begin(), lst1.end(), displayInt);
	std::cout << CORAIL << "Return 42's first occurence in container : " << easyfind(lst1, to_find) << std::endl;

	std::cout << WHITE << "... remove 42 from container ..." << std::endl;
	std::list<int>::iterator index = std::find(lst1.begin(), lst1.end(), 42);
	lst1.erase(index);
	std::for_each(lst1.begin(), lst1.end(), displayInt);
	std::cout << CORAIL << "Return 42's first occurence in container : " << easyfind(lst1, to_find) << std::endl;

	std::cout << WHITE << "... insert 42 at front ..." << std::endl;
	lst1.insert(lst1.begin(), 42);
	std::for_each(lst1.begin(), lst1.end(), displayInt);
	std::cout << CORAIL << "Return 42's first occurence in container : " << easyfind(lst1, to_find) << C_RES << std::endl << std::endl;
	return 0;
}
