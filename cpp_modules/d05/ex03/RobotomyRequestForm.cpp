# include "RobotomyRequestForm.hpp"

// Copy constructor
RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& src) : Form(src), _target(src.getTarget())
{
	return;
}

// Parametric constructor (std::string)
RobotomyRequestForm::RobotomyRequestForm(std::string target) : Form("Robotomy", 72, 45), _target(target)
{
	return ;
}

// Destructor
RobotomyRequestForm::~RobotomyRequestForm(void)
{
	std::cout << CORAIL << "RobotomyRequestFormForm destruction..." << C_RES << std::endl;
	return;
}

// Assignation operator
RobotomyRequestForm &	RobotomyRequestForm::operator=(const RobotomyRequestForm& rhs)
{
	std::cout << GREY << "RobotomyRequestForm Assignation operator called" << C_RES << std::endl;
	if (this != &rhs)
	{
		this->_target = rhs.getTarget();
	}
	return (*this);
}

// getters and setters (non static attributes)
std::string RobotomyRequestForm::getTarget(void) const
{
	return (this->_target);
}

/*
	RobotomyRequestForm (Grades requis : signature 72, execution 45). Action : Fait
	des bruits de perceuses, et annonce que <target> a bien été robotomizée dans 50%
	des cas, ou son echec le reste du temps
*/

void RobotomyRequestForm::action(void) const
{
	std::cout << SKY_BLUE << "*********************************************" << std::endl << C_RES << std::endl;
	std::cout << SKY_BLUE << "* bzzzzzz bzzzzzz bzzzzzz *" << C_RES << std::endl;
	if (this->_target.length() % 2 == 0)
		std::cout << SKY_BLUE << "Great ! " << this->_target << " has been robotized !" << C_RES << std::endl;
	else
		std::cout << SKY_BLUE << "Oh no ! " << this->_target << " has not been robotized !" << C_RES << std::endl;
	std::cout << std::endl << SKY_BLUE << "*********************************************" << C_RES << std::endl;
	return ;
}

Form*		RobotomyRequestForm::create(std::string target)
{
	return (new RobotomyRequestForm(target));
}

// overload de <<
std::ostream &operator<<(std::ostream &os, const RobotomyRequestForm & src)
{
	os << src.getTarget();
	return (os);
}

