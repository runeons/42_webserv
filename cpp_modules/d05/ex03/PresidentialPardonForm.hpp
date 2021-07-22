#ifndef PRESIDENTIALPARDONFORM_HPP
# define PRESIDENTIALPARDONFORM_HPP

# include <iostream>
# include <string>
# include <sstream>
# include "color.hpp"
# include "Bureaucrat.hpp"
# include "Form.hpp"

class PresidentialPardonForm : public Form
{
	private:
		PresidentialPardonForm(void);
		std::string	_target;

	public:
		PresidentialPardonForm(std::string target);
		PresidentialPardonForm(const PresidentialPardonForm & src);
		virtual ~PresidentialPardonForm();

		std::string	getTarget(void) const;

		void		action(void) const;

		static Form		*create(std::string target);

		PresidentialPardonForm&operator=(const PresidentialPardonForm & src);
};

std::ostream	&operator<<(std::ostream & os, const PresidentialPardonForm & src);

#endif
