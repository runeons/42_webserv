#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

# include <iostream>
# include <string>
# include <sstream>
# include "color.hpp"
# include "Form.hpp"

class Form;

class Bureaucrat
{
	private:
		// does not make sens because no name (it is const)
		Bureaucrat(const Bureaucrat & src);
		Bureaucrat();
		std::string const	_name;
		int					_grade;

	public:
		Bureaucrat(std::string, int grade);
		virtual ~Bureaucrat();

		std::string const	getName(void) const;
		int					getGrade(void) const;

		void				incrementGrade(void);
		void				decrementGrade(void);

		bool				signForm(Form & f) const;
		bool				executeForm(Form const & form) const;
		Bureaucrat			&operator=(const Bureaucrat & src);
};

std::ostream	&operator<<(std::ostream & os, const Bureaucrat & src);

#endif
