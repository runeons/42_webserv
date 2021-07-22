# include "AWeapon.hpp"
# include "PlasmaRifle.hpp"
# include "PowerFist.hpp"
# include "Enemy.hpp"
# include "SuperMutant.hpp"
# include "RadScorpion.hpp"
# include "Character.hpp"
# include "Knife.hpp"
# include "Beast.hpp"

int main(void)
{
	{
		std::cout << "______________________________ MY MAIN ______________________________" << std::endl;
		std::cout << "_____________________ Create PlasmaR _____________________" << std::endl;
		AWeapon* pr = new PlasmaRifle();
		std::cout << "_____________________ Create PowerF _____________________" << std::endl;
		AWeapon* pf = new PowerFist();
		std::cout << "_____________________ Create Knife _____________________" << std::endl;
		AWeapon* kn = new Knife();
		std::cout << "_______________________________________________________________________________" << std::endl;
		std::cout << "______________________________ ASSIGNATION TEST 1______________________________" << std::endl;
		std::cout << "_______________________________________________________________________________" << std::endl;
		std::cout << "_____________________ Create PowerFDest _____________________" << std::endl;
		AWeapon* pfDest = new PowerFist();
		pfDest->attack();
		std::cout << "_____________________ PowerFDest attacks and << before assignation _____________________" << std::endl;
		std::cout << *pf << std::endl;
		std::cout << "_____________________ Assign PlasmaR to PowerFDest _____________________" << std::endl;
		*pfDest = *pr;
		std::cout << "_____________________ PowerFDest attacks and << after assignation _____________________" << std::endl;
		pfDest->attack();
		std::cout << *pfDest << std::endl;
		std::cout << "_____________________ Delete PowerFDest _____________________" << std::endl;
		delete pfDest;
		std::cout << std::endl << std::endl;
		std::cout << "_______________________________________________________________________________" << std::endl;
		std::cout << "______________________________ ASSIGNATION TEST 2______________________________" << std::endl;
		std::cout << "_______________________________________________________________________________" << std::endl;
		std::cout << "_____________________ Create PlasmaRDest _____________________" << std::endl;
		PlasmaRifle* prDest = new PlasmaRifle();
		std::cout << "_____________________ Create PlasmaRSrc _____________________" << std::endl;
		PlasmaRifle* prSrc = new PlasmaRifle();
		std::cout << "_____________________ Assign PlasmaRSrc to PlasmaRSrc _____________________" << std::endl;
		*prSrc = *prDest;
		std::cout << "_____________________ Delete PlasmaRSrc _____________________" << std::endl;
		delete prSrc;
		std::cout << "_____________________ Delete PlasmaRDest _____________________" << std::endl;
		delete prDest;
		std::cout << std::endl << std::endl;
		std::cout << "_______________________________________________________________________________" << std::endl;
		std::cout << "_________________________________ MAIN TESTS __________________________________" << std::endl;
		std::cout << "_______________________________________________________________________________" << std::endl;
		std::cout << "_____________________ Uses PlasmaR << _____________________" << std::endl;
		std::cout << *pr << std::endl;
		std::cout << "_____________________ Uses PowerF << _____________________" << std::endl;
		std::cout << *pf << std::endl;
		std::cout << "_____________________ PlasmaR attacks _____________________" << std::endl;
		pr->attack();
		std::cout << "_____________________ PowerF attacks _____________________" << std::endl;
		pf->attack();
		std::cout << "_____________________ Create basic Enemy and take 4 damage _____________________" << std::endl;
		Enemy* b = new Enemy(50, "Basic");
		b->takeDamage(4);
		std::cout << "_____________________ Delete Basic Enemy _____________________" << std::endl;
		delete b;
		std::cout << "_____________________ Create Super Mutant and take damage _____________________" << std::endl;
		Enemy* c = new SuperMutant();
		c->takeDamage(4);
		std::cout << "_____________________ Super Mutant take more damage than hit points_____________________" << std::endl;
		c->takeDamage(180);
		std::cout << "_____________________ Create Rad Scorpion and take 18 damage _____________________" << std::endl;
		Enemy* d = new RadScorpion();
		d->takeDamage(18);
		std::cout << "_____________________ Create Character _____________________" << std::endl;
		Character* player = new Character("Player");
		std::cout << "_____________________ Create Beast and take 8 damage _____________________" << std::endl;
		Enemy* bst = new Beast();
		c->takeDamage(8);
		std::cout << "_____________________ Display (uses Character overload <<) _____________________" << std::endl;
		std::cout << *player;
		std::cout << "_____________________ Equip with PowerF and attack Rad Scorpion_____________________" << std::endl;
		player->equip(pf);
		std::cout << *player;
		player->attack(d);
		std::cout << "_____________________ Equip with Knife and attack Beast_____________________" << std::endl;
		player->equip(kn);
		std::cout << *player;
		player->attack(bst);
		std::cout << "_____________________ Equip with PlasmaR and attack Rad Scorpion until death _____________________" << std::endl;
		player->equip(pr);
		std::cout << *player;
		player->attack(d);
		std::cout << "_____________________ Player tries to attack SuperMutant with Knife _____________________" << std::endl;
		player->equip(kn);
		player->attack(c);
		std::cout << "_____________________ Player recover and attacks SuperMutant until death _____________________" << std::endl;
		player->recoverAP();
		player->recoverAP();
		player->recoverAP();
		player->recoverAP();
		std::cout << *player;
		player->attack(c);
		std::cout << *player;

		std::cout << std::endl << std::endl;
		std::cout << "_____________________ Delete PlasmaR _____________________" << std::endl;
		delete pr;
		std::cout << "_____________________ Delete PowerF _____________________" << std::endl;
		delete pf;
		std::cout << "_____________________ Delete Knife _____________________" << std::endl;
		delete kn;
		std::cout << "_____________________ Delete Beast _____________________" << std::endl;
		delete bst;
		std::cout << "_____________________ Delete Super Mutant _____________________" << std::endl;
		std::cout << "Super Mutant previously deleted" << std::endl;
		std::cout << "_____________________ Delete Rad Scorpion _____________________" << std::endl;
		std::cout << "Rad Scorpion previously deleted" << std::endl;
		std::cout << "_____________________ Delete Character _____________________" << std::endl;
		delete player;
	}
	{
		std::cout << std::endl << "______________________________ SUBJECT MAIN ______________________________" << std::endl;
		Character* me = new Character("me");

		std::cout << *me;

		Enemy* b = new RadScorpion();
		AWeapon* pr = new PlasmaRifle();
		AWeapon* pf = new PowerFist();

		me->equip(pr);
		std::cout << *me;

		me->equip(pf);
		me->attack(b);
		std::cout << *me;

		me->equip(pr);
		std::cout << *me;

		me->attack(b);
		std::cout << *me;

		me->attack(b);
		std::cout << *me;

		delete pr;
		delete pf;
		delete me;
	}
	std::cout << "_____________________ End _____________________" << std::endl;
	return 0;
}

