# include "Bureaucrat.hpp"

// Default constructor
Bureaucrat::Bureaucrat(void)
{
	// std::cout << GREY << "Bureaucrat creation..." << C_RES << std::endl;
	return ;
}

// Copy constructor
Bureaucrat::Bureaucrat(const Bureaucrat& src)
{
	std::cout << GREY << "Bureaucrat creation..." << C_RES << std::endl;
	*this = src;
	return;
}

// Bureaucrat::Bureaucrat(std::string name, int grade) : _name(name), _grade(grade)
Bureaucrat::Bureaucrat(std::string name, int grade) : _name(name)
{
	// std::cout << GREY << "Parametric Bureaucrat creation..." << C_RES << std::endl;
	try
	{
		if (grade > 150 || grade < 1)
			throw std::exception();
		else
			this->_grade = grade;
	}
	catch (std::exception & e)
	{
		std::cout << RED << "Error (construction) : grade must be between [1 - 150] ... deleting Bureaucrat ..." <<  C_RES << std::endl;
		delete this;
	}
	return ;
}

// Destructor
Bureaucrat::~Bureaucrat(void)
{
	std::cout << CORAIL << "Bureaucrat destruction..." << C_RES << std::endl;
	return;
}

// Assignation operator
Bureaucrat &	Bureaucrat::operator=(const Bureaucrat& rhs)
{
	std::cout << GREY << "Bureaucrat Assignation operator called" << C_RES << std::endl;
	if (this != &rhs)
	{
		this->_grade = rhs.getGrade();
	}
	return (*this);
}

// getters and setters (non static attributes)
std::string const Bureaucrat::getName(void) const
{
	return (this->_name);
}

int Bureaucrat::getGrade(void) const
{
	return (this->_grade);
}

void Bureaucrat::incrementGrade(void)
{
	try
	{
		if (this->_grade == 1)
			throw std::exception();
		else
		{
			this->_grade--;
			std::cout << GREEN_TREE << this->_name << " is going up to grade " << this->_grade << C_RES << std::endl;
		}
	}
	catch (std::exception & e)
	{
		std::cout << RED << "Error (incrementation) : " << this->_name << " is already at grade " << this->_grade << C_RES << std::endl;
	}
	return ;
}

void Bureaucrat::decrementGrade(void)
{
	try
	{
		if (this->_grade == 150)
			throw std::exception();
		else
		{
			this->_grade++;
			std::cout << ORANGE << this->_name << " is going down to grade " << this->_grade << C_RES << std::endl;
		}
	}
	catch (std::exception & e)
	{
		std::cout << RED << "Error (decrementation) : " << this->_name << " is already at grade " << this->_grade << C_RES << std::endl;
	}
	return ;

}

bool Bureaucrat::signForm(Form & f) const
{
	if (this->_grade <= f.getToSign())
	{
		std::cout << SKY_BLUE << this->_name << " signs form " << f.getName() << C_RES << std::endl;
		return 0;
	}
	else
	{
		std::cout << SKY_BLUE << this->_name << " can't sign form " << f.getName() << " (grade required : " << f.getToSign() << ", actual grade : " << this->_grade << ")" << C_RES << std::endl;
		return 1;
	}
}

// overload de <<
std::ostream &operator<<(std::ostream &os, const Bureaucrat & src)
{
	os << SKY_BLUE << src.getName() << ", bureaucrat grade " << src.getGrade() << C_RES;
	return (os);
}

