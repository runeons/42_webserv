#include <iostream>

int	main(void)
{
	std::string	brain = "HI THIS IS BRAIN";

	std::string	*brain_ptr = &brain;
	std::string	&brain_ref = brain;

	std::cout << "brain_ptr : "<< *brain_ptr << std::endl;
	std::cout << "brain_ref : "<< brain_ref << std::endl;
	return (0);
}