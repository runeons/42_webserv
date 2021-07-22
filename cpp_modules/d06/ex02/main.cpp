# include "Base.hpp"
# include "A.hpp"
# include "B.hpp"
# include "C.hpp"
# include "D.hpp"

/* instancie de facon aléatoire A, B ou C et retourne un pointeur de l’instance Base */
Base * generate(void)
{
	Base *x;

	int	i = std::rand() % 3;
	if (i == 0)
		x = new A;
	else if (i == 1)
		x = new B;
	else
		x = new C;
	// return (dynamic_cast<Base *>(x));
	return (x);
}

/* affiche "A", "B" ou "C" selon le type réel de p */
void identify_from_pointer(Base * p)
{
	try
	{
		if (dynamic_cast<A *>(p))
			std::cout << "A" << std::endl;
		else
			throw (std::exception());
	}
	catch (std::exception &e)
	{
		try
		{
			if (dynamic_cast<B *>(p))
				std::cout << "B" << std::endl;
			else
				throw (std::exception());
		}
		catch (std::exception &e)
		{
			try
			{
				if (dynamic_cast<C *>(p))
					std::cout << "C" << std::endl;
				else
					throw (std::exception());
			}
			catch (std::exception &e)
			{
				std::cout << "Error - not A, B, C" << std::endl;
			}
		}
	}
}

/* affiche "A", "B" ou "C" selon le type réel de p */
void identify_from_reference( Base & p)
{
	try
	{
		if (dynamic_cast<A *>(&p))
			std::cout << "A" << std::endl;
		else
			throw (std::exception());
	}
	catch (std::exception &e)
	{
		try
		{
			if (dynamic_cast<B *>(&p))
				std::cout << "B" << std::endl;
			else
				throw (std::exception());
		}
		catch (std::exception &e)
		{
			try
			{
				if (dynamic_cast<C *>(&p))
					std::cout << "C" << std::endl;
				else
					throw (std::exception());
			}
			catch (std::exception &e)
			{
				std::cout << "Error - not A, B, C" << std::endl;
			}
		}
	}

}

void	main_loop(void)
{
	std::cout << GREEN_TREE << "________________________________________________________" << std::endl;
	std::cout << GREEN_TREE << "_____________________ New Instance _____________________" << std::endl;
	std::cout << GREEN_TREE << "________________________________________________________" << std::endl;
	std::cout << std::endl;
	Base *x;
	std::cout << SKY_BLUE << "_____________________ generate ________________________" << std::endl;
	x = generate();
	std::cout  << CORAIL << "_____________________ identify_from_pointer ___________" << std::endl;
	identify_from_pointer(x);
	std::cout << ORANGE <<"_____________________ identify_from_reference __________" << std::endl;
	identify_from_reference(*x);
	std::cout << SKY_BLUE << "_____________________ Delete Base _____________________" << std::endl;
	delete x;
}

int main(void)
{
	std::srand(time(NULL));
	for (size_t i = 0; i < 5; i++)
	{
		main_loop();
		std::cout << std::endl;
	}

	std::cout << GREEN_TREE << "________________________________________________________" << std::endl;
	std::cout << GREEN_TREE << "_____________________ New Instance _____________________" << std::endl;
	std::cout << GREEN_TREE << "________________________________________________________" << std::endl;
	std::cout << std::endl;
	Base *x;
	std::cout << SKY_BLUE << "_____________________ generate ________________________" << std::endl;
	x = new D;
	std::cout  << CORAIL << "_____________________ identify_from_pointer ___________" << std::endl;
	identify_from_pointer(x);
	std::cout << ORANGE <<"_____________________ identify_from_reference __________" << std::endl;
	identify_from_reference(*x);
	std::cout << SKY_BLUE << "_____________________ Delete Base _____________________" << std::endl;
	delete x;

	return 0;
}

