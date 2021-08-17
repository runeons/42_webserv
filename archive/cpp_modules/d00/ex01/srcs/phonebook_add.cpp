#include "../includes/phonebook.hpp"

Contact	add(void)
{
	Contact	newContact;
	std::string	first_name;
	std::string	last_name;
	std::string	nickname;
	std::string	login;
	std::string	postal_address;
	std::string	email_address;
	std::string	phone_number;
	std::string	birthday_date;
	std::string	favorite_meal;
	std::string	underwear_color;
	std::string	darkest_secret;

	while (1)
	{
		std::cout << "What's its first_name ?" << std::endl << ">> ";
		std::getline(std::cin, first_name);
		std::cout << std::endl;
		newContact.set_first_name(first_name);
		std::cout << "What's its last_name ?" << std::endl << ">> ";
		std::getline(std::cin, last_name);
		std::cout << std::endl;
		newContact.set_last_name(last_name);
		std::cout << "What's its nickname ?" << std::endl << ">> ";
		std::getline(std::cin, nickname);
		std::cout << std::endl;
		newContact.set_nickname(nickname);
		std::cout << "What's its login ?" << std::endl << ">> ";
		std::getline(std::cin, login);
		std::cout << std::endl;
		newContact.set_login(login);
		std::cout << "What's its postal_address ?" << std::endl << ">> ";
		std::getline(std::cin, postal_address);
		std::cout << std::endl;
		newContact.set_postal_address(postal_address);
		std::cout << "What's its email_address ?" << std::endl << ">> ";
		std::getline(std::cin, email_address);
		std::cout << std::endl;
		newContact.set_email_address(email_address);
		std::cout << "What's its phone_number ?" << std::endl << ">> ";
		std::getline(std::cin, phone_number);
		std::cout << std::endl;
		newContact.set_phone_number(phone_number);
		std::cout << "What's its birthday_date ?" << std::endl << ">> ";
		std::getline(std::cin, birthday_date);
		std::cout << std::endl;
		newContact.set_birthday_date(birthday_date);
		std::cout << "What's its favorite_meal ?" << std::endl << ">> ";
		std::getline(std::cin, favorite_meal);
		std::cout << std::endl;
		newContact.set_favorite_meal(favorite_meal);
		std::cout << "What's its underwear_color ?" << std::endl << ">> ";
		std::getline(std::cin, underwear_color);
		std::cout << std::endl;
		newContact.set_underwear_color(underwear_color);
		std::cout << "What's its darkest_secret ?" << std::endl << ">> ";
		std::getline(std::cin, darkest_secret);
		std::cout << std::endl;
		newContact.set_darkest_secret(darkest_secret);

		std::cout << "Contact added !" << std::endl << std::endl;
		return (newContact);
	}
}
