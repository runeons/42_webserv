#include "Pony.hpp"

void	shout_new_speed(Pony pony_x)
{
	std::cout << YELLOW << "Maintenant, moi, " << (pony_x).get_name() << ", vais au " << (pony_x).get_speed() << C_RES << std::endl << std::endl;
}

Pony	ponyOnTheStack(std::string name, std::string race, std::string speed)
{
	Pony pony_stack = Pony(name, race, speed);

	return (pony_stack);
}

Pony	*ponyOnTheHeap(std::string name, std::string race, std::string speed)
{
	Pony	*pony_heap = new Pony(name, race, speed);

	return (pony_heap);
}

int		main(void)
{
	Pony*	pony_heap;

	Pony pony_stack = ponyOnTheStack("Spirit", "etalon", "trot");
	pony_stack.shout_speed();
	pony_stack.move_faster();
	pony_stack.move_slower();

	pony_heap = ponyOnTheHeap("Takh", "cheval de Przewalski", "pas");
	pony_heap->shout_speed();
	pony_heap->move_faster();
	pony_heap->move_slower();

	delete(pony_heap);
	return (0);
}