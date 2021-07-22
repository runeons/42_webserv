#ifndef INTERN_HPP
# define INTERN_HPP

# include <iostream>
# include <string>
# include "color.hpp"
# include "Bureaucrat.hpp"
# include "Form.hpp"
# include "ShrubberyCreationForm.hpp"
# include "RobotomyRequestForm.hpp"
# include "PresidentialPardonForm.hpp"


class Intern
{
	private :
		static std::string _form_names[3];
		static Form *(*_form_functions[3])(const std::string target);

	public:
		Intern();
		Intern(const Intern & src);
		virtual ~Intern();

		class FormNotFoundException : public std::exception
		{
			public:
				virtual const char *what() const throw()
				{ return ("Form not found"); }
		};
		Form *		makeForm(std::string name, std::string target);

		Intern		&operator=(const Intern & src);
};

#endif
