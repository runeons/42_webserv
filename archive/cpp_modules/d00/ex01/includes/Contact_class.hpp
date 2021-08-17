#ifndef CONTACT_CLASS_HPP
# define CONTACT_CLASS_HPP
#include "phonebook.hpp"

// DECLARATION

class Contact
{
	private:
		std::string	_first_name;
		std::string	_last_name;
		std::string	_nickname;
		std::string	_login;
		std::string	_postal_address;
		std::string	_email_address;
		std::string	_phone_number;
		std::string	_birthday_date;
		std::string	_favorite_meal;
		std::string	_underwear_color;
		std::string	_darkest_secret;
	public:
		std::string get_first_name(void);
		std::string get_last_name(void);
		std::string get_nickname(void);
		std::string get_login(void);
		std::string	get_postal_address(void);
		std::string	get_email_address(void);
		std::string	get_phone_number(void);
		std::string	get_birthday_date(void);
		std::string	get_favorite_meal(void);
		std::string	get_underwear_color(void);
		std::string	get_darkest_secret(void);

		void set_first_name(std::string first_name);
		void set_last_name(std::string last_name);
		void set_nickname(std::string nickname);
		void set_login(std::string login);
		void set_postal_address(std::string postal_address);
		void set_email_address(std::string email_address);
		void set_phone_number(std::string phone_number);
		void set_birthday_date(std::string birthday_date);
		void set_favorite_meal(std::string favorite_meal);
		void set_underwear_color(std::string underwear_color);
		void set_darkest_secret(std::string darkest_secret);

		Contact(void);
		~Contact(void);
};
#endif