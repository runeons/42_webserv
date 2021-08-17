# include "Data.hpp"

int	getRandomAlNum(void)
{
	int j = 0;
	j = std::rand() % 62;
	return RANDOM_ALNUM[j];
}

void * serialize(void)
{
	Data *ptr = new Data();

	ptr->s2.resize(8);
	ptr->s1.resize(8);
	for (size_t i = 0; i < 8; i++)
	{
		ptr->s1[i] = getRandomAlNum();
		ptr->s2[i] = getRandomAlNum();
	}
	ptr->s1[8] = '\0';
	ptr->s2[8] = '\0';
	ptr->n = std::rand() % 2147483647;
	return (ptr);
}

Data * deserialize(void * raw)
{
	return (reinterpret_cast<Data *>(raw));
}

int main(void)
{
	std::srand(time(NULL));
	Data *ptr;

	ptr = deserialize(serialize());
	// ptr = reinterpret_cast<Data *>(serialize());
	std::cout << GREEN_TREE << "________________________________________________________" << std::endl;
	std::cout << "s1 : [" << ptr->s1 << "] (size : " << sizeof(ptr->s1) << ")" << std::endl;
	std::cout << CORAIL << "n  : [" << ptr->n << "] (size : " << sizeof(ptr->n) << ")" << std::endl;
	std::cout << SKY_BLUE << "s2 : [" << ptr->s2 << "] (size : " << sizeof(ptr->s2) << ")" << std::endl;
	std::cout << GREEN_TREE << "________________________________________________________" << std::endl;
	std::cout << "sizeof all struct (*ptr) : " << sizeof(*ptr) << std::endl;
	std::cout << "sizeof all struct (ptr) : " << sizeof(ptr) << std::endl;
	std::cout << "________________________________________________________" << C_RES << std::endl;

	delete ptr;
	return 0;
}

