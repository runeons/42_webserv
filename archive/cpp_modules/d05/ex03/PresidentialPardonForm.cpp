# include "PresidentialPardonForm.hpp"

// Copy constructor
PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm& src) : Form(src), _target(src.getTarget())
{
	return;
}

// Parametric constructor (std::string)
PresidentialPardonForm::PresidentialPardonForm(std::string target) : Form("Presidential", 25, 5), _target(target)
{
	return ;
}

// Destructor
PresidentialPardonForm::~PresidentialPardonForm(void)
{
	std::cout << CORAIL << "PresidentialPardonFormForm destruction..." << C_RES << std::endl;
	return;
}

// Assignation operator
PresidentialPardonForm &	PresidentialPardonForm::operator=(const PresidentialPardonForm& rhs)
{
	std::cout << GREY << "PresidentialPardonForm Assignation operator called" << C_RES << std::endl;
	if (this != &rhs)
	{
		this->_target = rhs.getTarget();
	}
	return (*this);
}

// getters and setters (non static attributes)
std::string PresidentialPardonForm::getTarget(void) const
{
	return (this->_target);
}

/*
	PresidentialPardonForm (Grades requis : signature 25, execution 5). Action :
	Nous annonce que <target> a été pardonnée par Zafod Beeblebrox.
*/

void PresidentialPardonForm::action(void) const
{
	std::cout << SKY_BLUE << "*********************************************" << std::endl << C_RES << std::endl;
	std::cout << SKY_BLUE << this->_target << " has been forgiven by Zafod Beeblebrox !" << C_RES << std::endl;
	std::cout << std::endl << SKY_BLUE << "*********************************************" << C_RES << std::endl;
	return ;
}

Form*		PresidentialPardonForm::create(std::string target)
{
	return (new PresidentialPardonForm(target));
}


// overload de <<
std::ostream &operator<<(std::ostream &os, const PresidentialPardonForm & src)
{
	os << src.getTarget();
	return (os);
}

