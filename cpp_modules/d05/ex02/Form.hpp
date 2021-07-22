#ifndef FORM_HPP
# define FORM_HPP

# include <iostream>
# include <string>
# include <sstream>
# include "color.hpp"
# include "Bureaucrat.hpp"

class Bureaucrat;

class Form
{
	private:
		Form(void);
		const std::string	_name;
		bool				_isSigned;
		const int			_toSign;
		const int			_toExec;

	public:
		Form(const Form & src);
		Form(std::string name, int toSign, int toExec);
		virtual ~Form();

		class GradeTooHighException : public std::exception
		{
			public:
				virtual const char *what() const throw()
				{ return ("Grade is too high"); }
		};
		class GradeTooLowException : public std::exception
		{
			public:
				virtual const char *what() const throw()
				{ return ("Grade is too low"); }
		};

		std::string			getName(void) const;
		bool				getSigned(void) const;
		int					getToSign(void) const;
		int					getToExec(void) const;

		void				beSigned(Bureaucrat & b);
		void				execute(Bureaucrat const & executor) const;
		virtual void		action(void) const = 0;

		Form				&operator=(const Form & src);
};

std::ostream	&operator<<(std::ostream & os, const Form & src);

#endif
