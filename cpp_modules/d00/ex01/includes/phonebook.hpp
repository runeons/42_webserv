#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include <iostream>
# include <sstream>
# include <iomanip>
# include <string>
# include "Contact_class.hpp"

typedef struct		s_filled
{
	std::string		first_name;
	std::string		last_name;
	std::string		nickname;
	std::string		login;
	std::string		postal_address;
	std::string		email_address;
	std::string		phone_number;
	std::string		birthday_date;
	std::string		favorite_meal;
	std::string		underwear_color;
	std::string		darkest_secret;
}					t_filled;

void	search(Contact list[8], int nb_contacts);
int		del(Contact list[8], int nb_contacts);
void	autofill(Contact list[8], int *nb_contacts);
Contact	add(void);
void	print(std::string msg, int after);
#endif