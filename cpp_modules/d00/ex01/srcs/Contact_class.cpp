#include "../includes/phonebook.hpp"

// DEFINITION

Contact::Contact(void) {
	this->_first_name = "";
	this->_last_name = "";
	this->_nickname = "";
	this->_login = "";
	this->_postal_address = "";
	this->_email_address = "";
	this->_phone_number = "";
	this->_birthday_date = "";
	this->_favorite_meal = "";
	this->_underwear_color = "";
	this->_darkest_secret = "";
	return ;
}

Contact::~Contact(void) {
	return ;
}

void	Contact::set_first_name(std::string first_name)
{
	this->_first_name = first_name;
}

std::string	Contact::get_first_name(void)
{
	return (this->_first_name);
}

void	Contact::set_last_name(std::string last_name)
{
	this->_last_name = last_name;
}

std::string	Contact::get_last_name(void)
{
	return (this->_last_name);
}

void	Contact::set_nickname(std::string nickname)
{
	this->_nickname = nickname;
}

std::string	Contact::get_nickname(void)
{
	return (this->_nickname);
}

void	Contact::set_login(std::string login)
{
	this->_login = login;
}

std::string	Contact::get_login(void)
{
	return (this->_login);
}

void	Contact::set_postal_address(std::string postal_address)
{
	this->_postal_address = postal_address;
}

std::string	Contact::get_postal_address(void)
{
	return (this->_postal_address);
}

void	Contact::set_email_address(std::string email_address)
{
	this->_email_address = email_address;
}

std::string	Contact::get_email_address(void)
{
	return (this->_email_address);
}

void	Contact::set_phone_number(std::string phone_number)
{
	this->_phone_number = phone_number;
}

std::string	Contact::get_phone_number(void)
{
	return (this->_phone_number);
}

void	Contact::set_birthday_date(std::string birthday_date)
{
	this->_birthday_date = birthday_date;
}

std::string	Contact::get_birthday_date(void)
{
	return (this->_birthday_date);
}

void	Contact::set_favorite_meal(std::string favorite_meal)
{
	this->_favorite_meal = favorite_meal;
}

std::string	Contact::get_favorite_meal(void)
{
	return (this->_favorite_meal);
}

void	Contact::set_underwear_color(std::string underwear_color)
{
	this->_underwear_color = underwear_color;
}

std::string	Contact::get_underwear_color(void)
{
	return (this->_underwear_color);
}

void	Contact::set_darkest_secret(std::string darkest_secret)
{
	this->_darkest_secret = darkest_secret;
}

std::string	Contact::get_darkest_secret(void)
{
	return (this->_darkest_secret);
}
