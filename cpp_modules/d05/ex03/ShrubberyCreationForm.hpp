#ifndef SHRUBBERYCREATIONFORM_HPP
# define SHRUBBERYCREATIONFORM_HPP

# include <iostream>
# include <string>
# include <sstream>
# include <fstream>
# include "color.hpp"
# include "Bureaucrat.hpp"
# include "Form.hpp"

class ShrubberyCreationForm : public Form
{
	private:
		ShrubberyCreationForm(void);
		std::string	_target;

	public:
		ShrubberyCreationForm(std::string target);
		ShrubberyCreationForm(const ShrubberyCreationForm & src);
		virtual ~ShrubberyCreationForm();

		std::string	getTarget(void) const;

		void		action(void) const;

		static Form		*create(std::string target);

		ShrubberyCreationForm&operator=(const ShrubberyCreationForm & src);
};

std::ostream	&operator<<(std::ostream & os, const ShrubberyCreationForm & src);

#endif
