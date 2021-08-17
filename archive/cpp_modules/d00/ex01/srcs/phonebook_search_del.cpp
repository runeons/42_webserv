#include "../includes/phonebook.hpp"

void	display_contact(Contact list[8], int index)
{
	std::cout << std::setw(20) << std::setfill(' ') << "first_name : "<< list[index].get_first_name() << std::endl;
	std::cout << std::setw(20) << std::setfill(' ') << "last_name : "<< list[index].get_last_name() << std::endl;
	std::cout << std::setw(20) << std::setfill(' ') << "nickname : "<< list[index].get_nickname() << std::endl;
	std::cout << std::setw(20) << std::setfill(' ') << "login : "<< list[index].get_login() << std::endl;
	std::cout << std::setw(20) << std::setfill(' ') << "postal_address : "<< list[index].get_postal_address() << std::endl;
	std::cout << std::setw(20) << std::setfill(' ') << "email_address : "<< list[index].get_email_address() << std::endl;
	std::cout << std::setw(20) << std::setfill(' ') << "phone_number : "<< list[index].get_phone_number() << std::endl;
	std::cout << std::setw(20) << std::setfill(' ') << "birthday_date : "<< list[index].get_birthday_date() << std::endl;
	std::cout << std::setw(20) << std::setfill(' ') << "favorite_meal : "<< list[index].get_favorite_meal() << std::endl;
	std::cout << std::setw(20) << std::setfill(' ') << "underwear_color : "<< list[index].get_underwear_color() << std::endl;
	std::cout << std::setw(20) << std::setfill(' ') << "darkest_secret : "<< list[index].get_darkest_secret() << std::endl;
}

std::string truncate(std::string str, size_t width)
{
	if (str.length() > width)
		return (str.substr(0, width - 1) + ".");
	return (str);
}

void	show_contacts(Contact list[8], int nb_contacts)
{
	std::string	str;
	int			i;

	i = -1;
	while (++i < nb_contacts)
	{
		std::cout << std::setw(10) << std::setfill(' ') << i << " | ";
		str = list[i].get_first_name();
		std::cout << std::setw(10) << std::setfill(' ') << truncate(str, 10) << " | ";
		str = list[i].get_last_name();
		std::cout << std::setw(10) << std::setfill(' ') << truncate(str, 10) << " | ";
		str = list[i].get_nickname();
		std::cout << std::setw(10) << std::setfill(' ') << truncate(str, 10) << std::endl;
	}
}

void	show_cancel_and_prompt(int nb_contacts)
{
	std::cout << std::endl << "         " << nb_contacts << " | CANCEL" << std::endl << std::endl << ">> ";
}

void	search(Contact list[8], int nb_contacts)
{
	std::string	input;
	int			number;

	while (1)
	{
		print("Which contact should I display ?", 1);
		print("Please, provide the appropriate index", 2);
		show_contacts(list, nb_contacts);
		show_cancel_and_prompt(nb_contacts);
		std::getline(std::cin, input);
		std::cout << std::endl;
		std::stringstream ss(input);
		if (ss >> number)
		{
			if (ss.eof())
			{
				if (number < 0)
					print("Error: I don't know this contact - I need a number part of the above list", 2);
				else if (number < nb_contacts)
				{
					display_contact(list, number);
					break;
				}
				else if (number == nb_contacts)
				{
					print("Operation cancelled", 2);
					break;
				}
				else
					std::cout << "Error: The number shouldn't be higher than " << nb_contacts << std::endl << std::endl;
			}
			else if (!number)
				print("Error: I don't know this contact - I need a number", 2);
		}
		else
			print("Error: I don't know this contact - I need a number !", 2);
	}
}

int		del(Contact list[8], int nb_contacts)
{
	std::string	input;
	int			number;

	while (1)
	{
		std::cout << "Which contact should I delete ?" << std::endl;
		show_contacts(list, nb_contacts);
		show_cancel_and_prompt(nb_contacts);
		std::getline(std::cin, input);
		std::cout << std::endl;
		std::stringstream ss(input);
		if (ss >> number)
		{
			if (ss.eof())
			{
				if (number < 0)
					print("Error: I don't know this contact - I need a number part of the above list", 2);
				else if (number < nb_contacts)
				{
					if (number < nb_contacts - 1)
					{
						while (number < nb_contacts - 1)
						{
							list[number].set_first_name(list[number + 1].get_first_name());
							list[number].set_last_name(list[number + 1].get_last_name());
							list[number].set_nickname(list[number + 1].get_nickname());
							list[number].set_login(list[number + 1].get_login());
							list[number].set_postal_address(list[number + 1].get_postal_address());
							list[number].set_email_address(list[number + 1].get_email_address());
							list[number].set_phone_number(list[number + 1].get_phone_number());
							list[number].set_birthday_date(list[number + 1].get_birthday_date());
							list[number].set_favorite_meal(list[number + 1].get_favorite_meal());
							list[number].set_underwear_color(list[number + 1].get_underwear_color());
							list[number].set_darkest_secret(list[number + 1].get_darkest_secret());
							number++;
						}
					}
					nb_contacts--;
					print("Contact deleted !", 2);
					break;
				}
				else if (number == nb_contacts)
				{
					print("Operation cancelled", 2);
					break;
				}
				else
					std::cout << "Error: The number shouldn't be higher than " << nb_contacts << std::endl << std::endl;
			}
			else if (!number)
				print("Error: I don't know this contact - I need a number", 2);
		}
		else
			print("Error: I don't know this contact - I need a number !", 2);
	}
	return (nb_contacts);
}
