# include "Sorcerer.hpp"
# include "Victim.hpp"
# include "Peon.hpp"
# include "Sheep.hpp"
# include "Cat.hpp"

int main()
{
	{
		std::cout << "______________________________ SUBJECT MAIN ______________________________" << std::endl;
		Sorcerer robert("Robert", "the Magnificent");
		Victim jim("Jimmy");
		Peon joe("Joe");

		std::cout << robert << jim << joe;
		robert.polymorph(jim);
		robert.polymorph(joe);
	}
	std::cout << std::endl << std::endl;
	{
		std::cout << "______________________________ MY MAIN ______________________________" << std::endl;
		std::cout << "_____________________ Create Sorcerer && (<<) _____________________" << std::endl;
		Sorcerer merlin("Merlin", "the Mage");
		std::cout << merlin;
		std::cout << "_____________________ Create Victim _____________________" << std::endl;
		Victim v("Victim");
		std::cout << "_____________________ Create Peon _____________________" << std::endl;
		Peon p("Peon");
		std::cout << "_____________________ Create Sheep _____________________" << std::endl;
		Sheep s("Sheep");
		std::cout << "_____________________ Create Cat _____________________" << std::endl;
		Cat c("Cat");
		std::cout << "_____________________ Introduce (<<) Victim before assignation _____________________" << std::endl;
		std::cout << v;
		std::cout << "_____________________ Introduce (<<) Peon _____________________" << std::endl;
		std::cout << p;
		std::cout << "_____________________ Introduce (<<) Sheep _____________________" << std::endl;
		std::cout << s;
		std::cout << "_____________________ Introduce (<<) Cat _____________________" << std::endl;
		std::cout << c;
		std::cout << "_____________________ Assign Cat to Victim _____________________" << std::endl;
		v = c;
		std::cout << "_____________________ Introduce Victim after assignation _____________________" << std::endl;
		std::cout << v;
		std::cout << "_____________________ Polymorphing Victim (now Cat) _____________________" << std::endl;
		merlin.polymorph(v);
		std::cout << "_____________________ Polymorphing Peon _____________________" << std::endl;
		merlin.polymorph(p);
		std::cout << "_____________________ Polymorphing Sheep _____________________" << std::endl;
		merlin.polymorph(s);
		std::cout << "_____________________ Polymorphing Cat _____________________" << std::endl;
		merlin.polymorph(c);
		std::cout << "_____________________ End _____________________" << std::endl;
	}
	return 0;
}
