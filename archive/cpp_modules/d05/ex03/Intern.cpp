# include "Intern.hpp"

// Default constructor
Intern::Intern(void)
{
	std::cout << GREY << "Intern creation..." << C_RES << std::endl;
	return ;
}

// Copy constructor
Intern::Intern(const Intern& src)
{
	std::cout << GREY << "Intern creation..." << C_RES << std::endl;
	*this = src;
	return;
}

// Destructor
Intern::~Intern(void)
{
	std::cout << CORAIL << "Intern destruction..." << C_RES << std::endl;
	return;
}

// Assignation operator
Intern &	Intern::operator=(const Intern& rhs)
{
	std::cout << GREY << "Intern Assignation operator called" << C_RES << std::endl;
	if (this != &rhs)
	{
	}
	return (*this);
}

std::string Intern::_form_names[3] =
{
	"Shruberry",
	"Robotomy",
	"Presidential"
};

Form* (*Intern::_form_functions[3])(const std::string) =
{
	&ShrubberyCreationForm::create,
	&RobotomyRequestForm::create,
	&PresidentialPardonForm::create
};

Form * Intern::makeForm(std::string name, std::string target)
{
	try
	{
		for (int i = 0; i < 3; ++i)
		{
			if (Intern::_form_names[i] == name)
			{
				Form *new_form = ((*(Intern::_form_functions[i]))(target));
				std::cout << SKY_BLUE << "Intern creates " << new_form->getName() << C_RES << std::endl;
				return (new_form);
			}
			else if (i == 2)
				throw (Intern::FormNotFoundException());
		}
	}
	catch (Intern::FormNotFoundException &e)
	{
		std::cout << RED << "Error (form making) : " << name << " form not found" << C_RES << std::endl;
	}
	return NULL;
}
