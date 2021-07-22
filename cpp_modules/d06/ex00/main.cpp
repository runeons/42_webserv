# include "Convert.hpp"

int main(int ac, char *av[])
{
	if (ac != 2)
	{
		std::cout << RED_B << "Error input:" << WHITE_B << " one and only one argument required" << C_RES << std::endl;
		return (-1);
	}
	Convert nb(av[1]);
	nb.convert();
	return 0;
}
