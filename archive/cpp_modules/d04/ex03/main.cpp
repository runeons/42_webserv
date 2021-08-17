# include "AMateria.hpp"
# include "ICharacter.hpp"
# include "Character.hpp"
# include "Ice.hpp"
# include "Cure.hpp"
# include "MateriaSource.hpp"

int main(void)
{
	{
		std::cout << "______________________________ MY MAIN ______________________________" << std::endl;
		std::cout << "_____________________ Create new Characters _____________________" << std::endl;
		ICharacter* jane = new Character("Jane");
		ICharacter* creature = new Character("Creature");
		std::cout << "_____________________ CHAR DEEP COPY _____________________" << std::endl;
		std::cout << "_____________________ Create src && AMateria && equip _____________________" << std::endl;
		Character* john_src = new Character("John");
		AMateria* ice_test = new Ice();
		john_src->equip(ice_test);
		std::cout << "_____________________ Create dst && use its materia _____________________" << std::endl;
		Character* john_dst = new Character(*john_src);
		john_dst->use(0, *john_src);
		std::cout << *john_src << std::endl;
		std::cout << *john_dst << std::endl;
		std::cout << "_____________________ Delete dst and src _____________________" << std::endl;
		delete john_dst;
		delete john_src;
		std::cout << "_____________________ CHAR DEEP ASSIGNATION _____________________" << std::endl;
		std::cout << "_____________________ Create kate_src && equip _____________________" << std::endl;
		Character *kate_src = new Character("Ksrc");
		AMateria* ice_test_src = new Ice();
		AMateria* ice_test_dst = new Ice();
		kate_src->equip(ice_test_src);
		std::cout << "_____________________ Create dst && equip _____________________" << std::endl;
		Character *kate_dst = new Character("Kdst");
		kate_dst->equip(ice_test_dst);
		std::cout << "_____________________ ASSIGN Char_src to Char_dst _____________________" << std::endl;
		*kate_dst = *kate_src;
		std::cout << "_____________________ Print addresses _____________________" << std::endl;
		std::cout << "[src] : " << *kate_src << std::endl;
		std::cout << "[dst] : " << *kate_dst << std::endl;
		std::cout << "_____________________ Delete both _____________________" << std::endl;
		delete kate_dst;
		delete kate_src;
		std::cout << "_____________________ Create x2 new Ice and x3 new Cure _____________________" << std::endl;
		AMateria* ice1 = new Ice();
		AMateria* ice2 = new Ice();
		AMateria* cure3 = new Cure();
		AMateria* cure4 = new Cure();
		AMateria* cure5 = new Cure();
		std::cout << "_____________________ Equip Jane with x5 Ice/Cure _____________________" << std::endl;
		jane->equip(ice1);
		jane->equip(ice2);
		jane->equip(cure3);
		jane->equip(cure4);
		jane->equip(cure5);
		std::cout << "_____________________ Jane uses Ice [0] on Creature x2 _____________________" << std::endl;
		jane->use(0, *creature);
		jane->use(0, *creature);
		std::cout << "_____________________ Jane uses Cure [3] on Creature x2 _____________________" << std::endl;
		jane->use(3, *creature);
		jane->use(3, *creature);
		std::cout << "_____________________ Jane uses non-existing Ice on Creature _____________________" << std::endl;
		jane->use(4, *creature);
		std::cout << "_____________________ Unequip all _____________________" << std::endl;
		jane->unequip(0);
		jane->unequip(3);
		jane->unequip(2);
		jane->unequip(-1);
		jane->unequip(1);
		jane->unequip(0);
		jane->unequip(0);
		std::cout << "_____________________ Jane uses non-existing Ice on Creature _____________________" << std::endl;
		jane->use(0, *creature);
		std::cout << "_____________________ Create new empty MateriaSource _____________________" << std::endl;
		IMateriaSource* tmp_src = new MateriaSource();
		std::cout << "_____________________ MateriaSource learns new Ice x2_____________________" << std::endl;
		tmp_src->learnMateria(new Ice());
		tmp_src->learnMateria(new Ice());
		std::cout << "_____________________ MateriaSource learns new Cure x3_____________________" << std::endl;
		tmp_src->learnMateria(new Cure());
		tmp_src->learnMateria(new Cure());
		tmp_src->learnMateria(new Cure());
		std::cout << "_____________________ Create Ice via createMateria_____________________" << std::endl;
		AMateria* tmp_ice;
		tmp_ice = tmp_src->createMateria("ice");
		std::cout << "_____________________ Create Unknown via createMateria_____________________" << std::endl;
		AMateria* tmp_unk;
		tmp_unk = tmp_src->createMateria("unkown");
		std::cout << "_____________________ Create Cure via createMateria_____________________" << std::endl;
		AMateria* tmp_cur;
		tmp_cur = tmp_src->createMateria("cure");
		std::cout << "_____________________ Equipe Creature with both + unknown_____________________" << std::endl;
		creature->equip(tmp_ice);
		creature->equip(tmp_cur);
		creature->equip(tmp_unk);
		std::cout << "_____________________ Delete all _____________________" << std::endl;
		delete jane;
		delete creature;
		delete ice1;
		delete ice2;
		delete cure3;
		delete cure4;
		delete cure5;
		delete tmp_src;
	}
	{
		std::cout << "______________________________ SUBJECT MAIN ______________________________" << std::endl;
		IMateriaSource* src = new MateriaSource();
		src->learnMateria(new Ice());
		src->learnMateria(new Cure());
		ICharacter* me = new Character("me");
		AMateria* tmp;
		tmp = src->createMateria("ice");
		me->equip(tmp);
		tmp = src->createMateria("cure");
		me->equip(tmp);
		ICharacter* bob = new Character("bob");
		me->use(0, *bob);
		me->use(1, *bob);
		delete bob;
		delete me;
		delete src;
	}
	std::cout << "______________________________ END ______________________________" << std::endl;
	return 0;
}

