#include "../includes/phonebook.hpp"

t_filled			g_exemple[8] =
{
	{ "Marie-Antoinette"   , "d'Autriche"   , "Archiduchesse", "madautriche"   , "Chateau de Versailles"          , "madautriche@student.42.fr"   , "N/A", "02/11/1755", "cafe"       , "white"     , "was scared before dying" },
	{ "Allan"   , "Ansen"    , "Rollo Greb"    , "rgreb"    , "New York"       , "rgreb@student.42.fr"    , "XVIII", "23/01/1922", "alcohol"    , "N/A"    , "has read the Machinum Apocryphum" },
	{ "Virginie", "Despentes" , "N/A"   , "vdespentes" , "Empire State Building", "vdespentesu@student.42.fr" , "0495321248", "13/06/1969", "chips", "dark green", "saved many lives" },
	{ "Francois-Marie", "Arouet" , "Voltaire"     , "fmarouet" , "Chateau de Ferney-Voltaire"  , "fmarouet@student.42.fr" , "06 22 15 12 20", "21/11/1694", "vegetables", "purple"     , "thought to be free" },
	{ "Violaine" , "Huisman"  , "La fugitive"   , "vhuisman"  , "New York, USA" , "vhuisman@student.42.fr"  , "0611919834", "Unknown", "salade d'endives"  , "dark cyan"  , "poet" },
	{ "Thomas", "Chatterton"  , "Rowley" , "tchatterton"  , "Holborn, London"   , "tchatterton@student.42.fr"  , "0789-933-6607", "20/11/1752", "arsenic"   , "blue"   , "didn't want to die from hunger" },
	{ "Beatrice" , "Cabarrou"  , "Beatrice Dalle" , "bdalle"  , "Paris" , "bdalle@student.42.fr"  , "07.36.24.XX.XX", "19/12/1964", "sugar"  , "carmen red" , "..." },
	{ "Gabriel" , "Tallent", "My Absolute Darling", "gtallent", "Salt Lake City" , "N/A", "N/A", "1987", "water"  , "transparent" , "couldn't find any information" },
};

void			autofill(Contact list[8], int *nb_contacts)
{
	std::string	input;
	int			i;

	while (1)
	{
		if (*nb_contacts == 8)
		{
			print("Nothing to autofill : your Awesome Phonebook is full.", 2);
			return ;
		}
		print("Are you sure you want to autofill your Awesome Phonebook ? yes / no", 1);
		std::getline(std::cin, input);
		if (input == "yes")
		{
			i = 0;
			while ((*nb_contacts) < 8)
			{
				list[*nb_contacts].set_first_name(g_exemple[i].first_name);
				list[*nb_contacts].set_last_name(g_exemple[i].last_name);
				list[*nb_contacts].set_nickname(g_exemple[i].nickname);
				list[*nb_contacts].set_login(g_exemple[i].login);
				list[*nb_contacts].set_postal_address(g_exemple[i].postal_address);
				list[*nb_contacts].set_email_address(g_exemple[i].email_address);
				list[*nb_contacts].set_phone_number(g_exemple[i].phone_number);
				list[*nb_contacts].set_birthday_date(g_exemple[i].birthday_date);
				list[*nb_contacts].set_favorite_meal(g_exemple[i].favorite_meal);
				list[*nb_contacts].set_underwear_color(g_exemple[i].underwear_color);
				list[*nb_contacts].set_darkest_secret(g_exemple[i].darkest_secret);
				i++;
				(*nb_contacts)++;
			}
			print("Awesome Phonebook has been autofilled !", 2);
			return ;
		}
		else if (input == "no")
		{
			print("OK ! Going back to main menu", 2);
			return ;
		}
		else
		{
			print("Sorry, I didn't understand", 2);
			continue ;
		}
	}
}
