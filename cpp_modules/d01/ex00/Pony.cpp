#include "Pony.hpp"

Pony::Pony(std::string name, std::string race, std::string speed) :
	_name(name), _race(race), _speed(speed) {
	// std::cout << "Appel au constructeur de " << this->_name << std::endl;
	return ;
}

Pony::~Pony(void) {
	// std::cout << "Appel au destructeur de " << this->_name << std::endl;
	return ;
}

void	Pony::set_name(std::string name)
{
	this->_name = name;
}

std::string	Pony::get_name(void)
{
	return (this->_name);
}

void	Pony::set_race(std::string race)
{
	this->_race = race;
}

std::string	Pony::get_race(void)
{
	return (this->_race);
}

void	Pony::set_speed(std::string speed)
{
	this->_speed = speed;
}

std::string	Pony::get_speed(void)
{
	return (this->_speed);
}

void	Pony::move_faster(void)
{
	if (this->get_speed() == "pas")
		this->set_speed("trot");
	else
		this->set_speed("galop");
	this->shout_speed();
}

void	Pony::move_slower(void)
{
	if (this->get_speed() == "galop")
		this->set_speed("trot");
	else
		this->set_speed("pas");
	this->shout_speed();
}

void	Pony::shout_speed()
{
	std::cout << GREEN << "Je suis " << this->get_name() << ", " << this->get_race()  << " et je vais au " << this->get_speed() << C_RES << std::endl;
}

void	Pony::shout_new_speed()
{
	std::cout << YELLOW << "Maintenant, moi, " << this->get_name() << ", vais au " << this->get_speed() << C_RES << std::endl << std::endl;
}
