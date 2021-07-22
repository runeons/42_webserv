#ifndef ROBOTOMYREQUESTFORM_HPP
# define ROBOTOMYREQUESTFORM_HPP

# include <iostream>
# include <string>
# include <sstream>
# include "color.hpp"
# include "Bureaucrat.hpp"
# include "Form.hpp"

class RobotomyRequestForm : public Form
{
	private:
		RobotomyRequestForm(void);
		std::string	_target;

	public:
		RobotomyRequestForm(std::string target);
		RobotomyRequestForm(const RobotomyRequestForm & src);
		virtual ~RobotomyRequestForm();

		std::string	getTarget(void) const;

		void		action(void) const;

		static Form		*create(std::string target);

		RobotomyRequestForm&operator=(const RobotomyRequestForm & src);
};

std::ostream	&operator<<(std::ostream & os, const RobotomyRequestForm & src);

#endif
