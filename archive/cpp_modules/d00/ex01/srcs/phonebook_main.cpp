#include "../includes/phonebook.hpp"

void	print(std::string msg, int after)
{
	int	i;

	std::cout << msg;
	i = -1;
	while (++i < after)
		std::cout << std::endl;
}

void	clear(int *nb_contacts)
{
	std::string	input;

	if (*nb_contacts == 0)
	{
		print("Nothing to clear : your Awesome Phonebook is empty.", 2);
		return ;
	}
	print("Are you sure you want to clear your Awesome Phonebook ? yes / no", 1);
	std::getline(std::cin, input);
	if (input == "yes")
	{
		(*nb_contacts) = 0;
		print("Awesome Phonebook has been cleared !", 2);
	}
	else if (input == "no")
		print("OK ! Going back to main menu", 2);
}

std::string	initial_prompt(void)
{
	std::string input[6] = {"ADD", "SEARCH", "DELETE", "AUTOFILL", "CLEAR", "EXIT"};
	std::string nb;
	int			i;

	while (1)
	{
		i = -1;
		std::cout << std::endl << std::setw(42) << std::setfill('*') << "*"<< std::endl;
		print(" What would you like to do ? ", 2);
		while (++i < 6)
			std::cout << i << ". " << input[i] << std::endl;
		std::cout << std::endl << ">> ";
		std::getline(std::cin,nb);
		if (std::cin.eof())
			return (input[5]);
		else if (nb == "0" || nb == "1" || nb == "2" || nb == "3" || nb == "4" || nb == "5")
		{
			std::istringstream(nb) >> i;
			return (input[i]);
		}
		else
			print("Sorry, I didn't understand.", 2);
	}
}


int		phonebook(Contact list[8])
{
	std::string	input;
	int			nb_contacts;

	nb_contacts = 0;
	while ((input = initial_prompt()) != "EXIT")
	{
		if (input == "ADD")
		{
			if (nb_contacts < 8)
			{
				print("Great, let's ADD a contact !", 2);
				list[nb_contacts++] = add();
			}
			else
			{
				print("Your Awesome Phonebook is full.", 1);
				print("Please delete a contact before adding a new one.", 2);
			}
		}
		else if (input == "SEARCH")
		{
			if (nb_contacts > 0)
			{
				print("Great, let's SEARCH a contact !", 2);
				search(list, nb_contacts);
			}
			else
				print("Nothing to display : your Awesome Phonebook is empty.", 2);
		}
		else if (input == "DELETE")
		{
			if (nb_contacts > 0)
			{
				print("Great, let's DELETE a contact !", 2);
				nb_contacts = del(list, nb_contacts);
			}
			else
				print("Nothing to delete : your Awesome Phonebook is empty.", 2);
		}
		else if (input == "AUTOFILL")
			autofill(list, &nb_contacts);
		else if (input == "CLEAR")
			clear(&nb_contacts);
	}
	return (0);
}

int		main (void)
{
	Contact list[8];

	std::cout << std::endl;

	std::cout << std::setw(42) << std::setfill('*') << "*" << std::endl;
	std::cout << "*    Welcome to your Awesome Phonebook   *" << std::endl;
	std::cout << std::setw(42) << std::setfill('*') << "*" << std::endl << std::endl;
	phonebook(list);
	std::cout << std::setw(42) << std::setfill('*') << "*" << std::endl;
	std::cout << "*               Bye Bye !                *" << std::endl;
	std::cout << std::setw(42) << std::setfill('*') << "*" << std::endl;
	return (0);
}