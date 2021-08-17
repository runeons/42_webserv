# include "ISquad.hpp"
# include "ISpaceMarine.hpp"
# include "Squad.hpp"
# include "TacticalMarine.hpp"
# include "AssaultTerminator.hpp"

int main(void)
{
	std::cout << "______________________________ MY MAIN ______________________________" << std::endl;
	std::cout << "_____________________ Create Tactical Marine 1 && cry _____________________" << std::endl;
	ISpaceMarine* unit1 = new TacticalMarine ;
	unit1->battleCry();
	std::cout << "_____________________ Create Tactical Marine 2 && cry _____________________" << std::endl;
	ISpaceMarine* unit2 = new TacticalMarine;
	unit2->battleCry();
	std::cout << "_____________________ Create Squad && getUnit(0) _____________________" << std::endl;
	ISquad* squad = new Squad;
	if (squad->getUnit(0))
		squad->getUnit(0)->battleCry();
	std::cout << "_____________________ Push unit1 to Squad && getCount && getUnit(0) _____________________" << std::endl;
	squad->push(unit1);
	std::cout << ORANGE << "There are " << squad->getCount() << " unit(s) in this squad" << C_RES << std::endl;
	squad->getUnit(0)->battleCry();
	std::cout << "_____________________ Push unit2 to Squad && getCount && getUnit(1) _____________________" << std::endl;
	squad->push(unit2);
	std::cout << ORANGE << "There are " << squad->getCount() << " unit(s) in this squad" << C_RES << std::endl;
	squad->getUnit(1)->battleCry();
	std::cout << "_____________________ Create Assault Terminator 1 && cry _____________________" << std::endl;
	ISpaceMarine* unitA = new AssaultTerminator;
	unit2->battleCry();
	std::cout << "_____________________ Push it to Squad && getCount && getUnit(0) _____________________" << std::endl;
	squad->push(unitA);
	std::cout << ORANGE << "There are " << squad->getCount() << " unit(s) in this squad" << C_RES << std::endl;
	std::cout << "_____________________ Push unit2 AGAIN to Squad && getCount _____________________" << std::endl;
	squad->push(unit2);
	std::cout << ORANGE << "There are " << squad->getCount() << " unit(s) in this squad" << C_RES << std::endl;
	std::cout << "_____________________ Push NULL to Squad && getCount _____________________" << std::endl;
	squad->push(NULL);
	std::cout << ORANGE << "There are " << squad->getCount() << " unit(s) in this squad" << C_RES << std::endl;
	std::cout << "_____________________ getUnit(-2147483648) - out of boundaries_____________________" << std::endl;
	squad->getUnit(-1);
	std::cout << "_____________________ getUnit(-1) - out of boundaries_____________________" << std::endl;
	squad->getUnit(-1);
	std::cout << "_____________________ getUnit(getCount()) - out of boundaries_____________________" << std::endl;
	squad->getUnit(squad->getCount());
	std::cout << "_____________________ getUnit(-2147483647) - out of boundaries_____________________" << std::endl;
	squad->getUnit(-1);
	std::cout << "_____________________ Print Squad _____________________" << std::endl;
	for (int i = 0; i < squad->getCount(); ++i)
	{
		ISpaceMarine* cur = squad->getUnit(i);
		cur->battleCry();
		cur->rangedAttack();
		cur->meleeAttack();
	}
	std::cout << "_____________________ DEEP COPY -- Create and fill Squad_src and copy to Squad_dst _____________________" << std::endl;
	std::cout << "_____________________ Create unitY _____________________" << std::endl;
	ISpaceMarine* unitY = new TacticalMarine ;
	std::cout << "_____________________ Create unitZ _____________________" << std::endl;
	ISpaceMarine* unitZ = new AssaultTerminator;
	std::cout << "_____________________ Create unitX _____________________" << std::endl;
	ISpaceMarine* unitX = new AssaultTerminator;
	std::cout << "_____________________ Create squad_src _____________________" << std::endl;
	Squad *squad_src = new Squad;
	std::cout << "_____________________ Push 2 units _____________________" << std::endl;
	squad_src->push(unitY);
	squad_src->push(unitZ);
	std::cout << "_____________________ CREATE Squad_dst VIA COPY _____________________" << std::endl;
	Squad *squad_dst = new Squad(*squad_src);
	std::cout << "[src] : " << *squad_src << std::endl;
	std::cout << "[dst] : " << *squad_dst << std::endl;
	std::cout << "_____________________ Push one to Squad_src and compare src and dst _____________________" << std::endl;
	squad_src->push(unitX);
	std::cout << "src : " << squad_src->getCount() << std::endl;
	std::cout << "dst : " << squad_dst->getCount() << std::endl;
	std::cout << "_____________________ Delete both squads _____________________" << std::endl;
	delete squad_dst;
	delete squad_src;

	std::cout << "_____________________ DEEP ASSIGN - Assign [src] Squad to [dst] Squad3 _____________________" << std::endl;
	std::cout << "_____________________ Create unitK _____________________" << std::endl;
	ISpaceMarine* unitK = new TacticalMarine ;
	std::cout << "_____________________ Create unitL _____________________" << std::endl;
	ISpaceMarine* unitL = new AssaultTerminator;
	std::cout << "_____________________ Create unitM _____________________" << std::endl;
	ISpaceMarine* unitM = new AssaultTerminator;
	std::cout << "_____________________ Create unitDest _____________________" << std::endl;
	ISpaceMarine* unitDst = new TacticalMarine ;
	std::cout << "_____________________ Create squad_src _____________________" << std::endl;
	Squad *squad_src2 = new Squad;
	std::cout << "_____________________ Push 2 units to Src_____________________" << std::endl;
	squad_src2->push(unitK);
	squad_src2->push(unitL);
	std::cout << "_____________________ Create Squad_dst _____________________" << std::endl;
	Squad *squad_dst2 = new Squad;
	std::cout << "_____________________ Push 1 unit to Squad_dst _____________________" << std::endl;
	squad_dst2->push(unitDst);
	std::cout << "_____________________ ASSIGN Squad_src to Squad_dst _____________________" << std::endl;
	*squad_dst2 = *squad_src2;
	std::cout << "[src] : " << *squad_src2 << std::endl;
	std::cout << "[dst] : " << *squad_dst2 << std::endl;
	std::cout << "_____________________ Push one to Squad_src and compare src and dst _____________________" << std::endl;
	squad_src2->push(unitM);
	std::cout << "src : " << squad_src2->getCount() << std::endl;
	std::cout << "dst : " << squad_dst2->getCount() << std::endl;
	std::cout << "_____________________ Delete both squads _____________________" << std::endl;
	delete squad_dst2;
	delete squad_src2;

	std::cout << "_____________________ Clone Tactical Marine && print _____________________" << std::endl;
	ISpaceMarine* unit3 = unit1->clone() ;
	std::cout << "src address : " << unit1 << std::endl;
	unit1->battleCry();
	unit1->rangedAttack();
	unit1->meleeAttack();
	std::cout << "dst address : " << unit3 << std::endl;
	unit3->battleCry();
	unit3->rangedAttack();
	unit3->meleeAttack();
	std::cout << "_____________________ Push clone to Squad && getCount _____________________" << std::endl;
	squad->push(unit3);
	std::cout << ORANGE << "There are " << squad->getCount() << " unit(s) in this squad" << C_RES << std::endl;
	std::cout << "_____________________ Create TacticalMarine via copy constructor _____________________" << std::endl;
	std::cout << ORANGE << "There are " << squad->getCount() << " unit(s) in this squad" << C_RES << std::endl;
	TacticalMarine* unit4 = new TacticalMarine;
	TacticalMarine* unit5 = new TacticalMarine(*unit4);
	unit4->battleCry();
	unit5->battleCry();
	std::cout << "src address : " << unit4 << std::endl;
	std::cout << "dst address : " << unit5 << std::endl;
	std::cout << "_____________________ Push both to Squad && getCount _____________________" << std::endl;
	squad->push(unit4);
	squad->push(unit5);
	std::cout << ORANGE << "There are " << squad->getCount() << " unit(s) in this squad" << C_RES << std::endl;
	std::cout << "_____________________ Delete Squad _____________________" << std::endl;
	delete squad;
	{
		std::cout << "______________________________ SUBJECT MAIN ______________________________" << std::endl;
		ISpaceMarine* bob = new TacticalMarine;
		ISpaceMarine* jim = new AssaultTerminator;
		ISquad* vlc = new Squad;
		vlc->push(bob);
		vlc->push(jim);
		for (int i = 0; i < vlc->getCount(); ++i)
		{
				ISpaceMarine* cur = vlc->getUnit(i);
				cur->battleCry();
				cur->rangedAttack();
				cur->meleeAttack();
			}
		delete vlc;
	}
	return 0;
}

