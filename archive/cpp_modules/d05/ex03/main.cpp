# include "Bureaucrat.hpp"
# include "Form.hpp"
# include "ShrubberyCreationForm.hpp"
# include "PresidentialPardonForm.hpp"
# include "RobotomyRequestForm.hpp"
# include "Intern.hpp"

void	shruberry(void)
{
	std::cout << std::endl;
	std::cout << "_____________________________________________________________________" << std::endl;
	std::cout << "___________________________ SHRUBBERYFORM ___________________________" << std::endl;
	std::cout << "_____________________________________________________________________" << std::endl;
	std::cout << std::endl;
	std::cout << "______________ SHRUBBERYFORM overload << _______________" << std::endl;
	Form *sh = new ShrubberyCreationForm("maison");
	std::cout << *sh << std::endl;
	std::cout << std::endl;
	std::cout << "______________ SHRUBBERYFORM execute on Bureaucrat[150] - should neither sign nor execute _______________" << std::endl;
	Bureaucrat *b150 = new Bureaucrat("Napo", 150);
	std::cout << *b150 << std::endl;
	sh->execute(*b150);
	delete b150;
	std::cout << std::endl;
	std::cout << "______________ SHRUBBERYFORM execute on Bureaucrat[137] - should sign and execute _______________" << std::endl;
	Bureaucrat *b137 = new Bureaucrat("Napo", 137);
	std::cout << *sh << std::endl;
	std::cout << *b137 << std::endl;
	b137->executeForm(*sh);
	sh->beSigned(*b137);
	b137->executeForm(*sh);
	std::cout << *sh << std::endl;
	std::cout << *b137 << std::endl;
	delete b137;
	std::cout << std::endl;
	std::cout << "______________ SHRUBBERYFORM execute on Bureaucrat[138] - should sign but not execute _______________" << std::endl;
	Form *sh_not_signed = new ShrubberyCreationForm("maison");
	Bureaucrat *b138 = new Bureaucrat("Napo", 138);
	std::cout << *sh_not_signed << std::endl;
	std::cout << *b138 << std::endl;
	b138->executeForm(*sh_not_signed);
	sh_not_signed->beSigned(*b138);
	b138->executeForm(*sh_not_signed);
	std::cout << *sh_not_signed << std::endl;
	std::cout << *b138 << std::endl;
	delete b138;
	std::cout << std::endl;
	std::cout << "______________ DELETE FORMS _______________" << std::endl;
	delete sh_not_signed;
	delete sh;
	std::cout << std::endl;
	return ;
}

void	robotomy(void)
{
	std::cout << std::endl;
	std::cout << "_____________________________________________________________________" << std::endl;
	std::cout << "___________________________ ROBOTOMYFORM ____________________________" << std::endl;
	std::cout << "_____________________________________________________________________" << std::endl;
	std::cout << std::endl;
	std::cout << "______________ ROBOTOMYFORM overload << _______________" << std::endl;
	Form *rb = new RobotomyRequestForm("maison");
	std::cout << *rb << std::endl;
	std::cout << std::endl;
	std::cout << "______________ ROBOTOMYFORM execute on Bureaucrat[150] - should neither sign nor execute _______________" << std::endl;
	Bureaucrat *b150 = new Bureaucrat("Napo", 150);
	std::cout << *b150 << std::endl;
	rb->execute(*b150);
	delete b150;
	std::cout << std::endl;
	std::cout << "______________ ROBOTOMYFORM execute on Bureaucrat[45] - should sign and execute _______________" << std::endl;
	Bureaucrat *b45 = new Bureaucrat("Napo", 45);
	std::cout << *rb << std::endl;
	std::cout << *b45 << std::endl;
	b45->executeForm(*rb);
	rb->beSigned(*b45);
	b45->executeForm(*rb);
	std::cout << *rb << std::endl;
	std::cout << *b45 << std::endl;
	delete b45;
	std::cout << std::endl;
	std::cout << "______________ ROBOTOMYFORM execute on Bureaucrat[50] - should sign but not execute _______________" << std::endl;
	Form *rb_not_signed = new RobotomyRequestForm("maison");
	Bureaucrat *b50 = new Bureaucrat("Napo", 50);
	std::cout << *rb_not_signed << std::endl;
	std::cout << *b50 << std::endl;
	b50->executeForm(*rb_not_signed);
	rb_not_signed->beSigned(*b50);
	b50->executeForm(*rb_not_signed);
	std::cout << *rb_not_signed << std::endl;
	std::cout << *b50 << std::endl;
	delete b50;
	std::cout << std::endl;
	std::cout << "______________ DELETE FORMS _______________" << std::endl;
	delete rb_not_signed;
	delete rb;
	std::cout << std::endl;
	return ;
}

void	presidential(void)
{
	std::cout << std::endl;
	std::cout << "________________________________________________________________________" << std::endl;
	std::cout << "___________________________ PRESIDENTIALFORM ___________________________" << std::endl;
	std::cout << "________________________________________________________________________" << std::endl;
	std::cout << std::endl;
	std::cout << "______________ PRESIDENTIALFORM overload << _______________" << std::endl;
	Form *pr = new PresidentialPardonForm("maison");
	std::cout << *pr << std::endl;
	std::cout << std::endl;
	std::cout << "______________ PRESIDENTIALFORM execute on Bureaucrat[26] - should neither sign nor execute _______________" << std::endl;
	Bureaucrat *b26 = new Bureaucrat("Napo", 26);
	std::cout << *b26 << std::endl;
	pr->execute(*b26);
	delete b26;
	std::cout << std::endl;
	std::cout << "______________ PRESIDENTIALFORM execute on Bureaucrat[5] - should sign and execute _______________" << std::endl;
	Bureaucrat *b5 = new Bureaucrat("Napo", 5);
	std::cout << *pr << std::endl;
	std::cout << *b5 << std::endl;
	b5->executeForm(*pr);
	pr->beSigned(*b5);
	b5->executeForm(*pr);
	std::cout << *pr << std::endl;
	std::cout << *b5 << std::endl;
	delete b5;
	std::cout << std::endl;
	std::cout << "______________ PRESIDENTIALFORM execute on Bureaucrat[12] - should sign but not execute _______________" << std::endl;
	Form *pr_not_signed = new PresidentialPardonForm("maison");
	Bureaucrat *b12 = new Bureaucrat("Napo", 12);
	std::cout << *pr_not_signed << std::endl;
	std::cout << *b12 << std::endl;
	b12->executeForm(*pr_not_signed);
	pr_not_signed->beSigned(*b12);
	b12->executeForm(*pr_not_signed);
	std::cout << *pr_not_signed << std::endl;
	std::cout << *b12 << std::endl;
	delete b12;
	std::cout << std::endl;
	std::cout << "______________ DELETE FORMS _______________" << std::endl;
	delete pr_not_signed;
	delete pr;
	std::cout << std::endl;
	return ;
}

int main(void)
{
	// shruberry();
	// robotomy();
	// presidential();
	Intern *i = new Intern;
	Form* sh;
	Form* rb;
	Form* pr;
	Form* pr2;
	std::cout << "______________ SHRUBERRY _______________" << std::endl;
	sh = i->makeForm("Shruberry", "Bender");
	std::cout << *sh << std::endl;
	std::cout << "______________ ROBOTOMY _______________" << std::endl;
	rb = i->makeForm("Robotomy", "Casual");
	std::cout << *rb << std::endl;
	std::cout << "______________ PRESIDENTIAL X2_______________" << std::endl;
	pr = i->makeForm("Presidential", "Magic");
	pr2 = i->makeForm("Presidential", "Magic2");
	std::cout << *pr << std::endl;
	std::cout << *pr2 << std::endl;
	std::cout << "______________ PRESIDENTIALFORM execute on Bureaucrat[5] - should sign and execute _______________" << std::endl;
	Bureaucrat *b5 = new Bureaucrat("Napo", 5);
	std::cout << *pr << std::endl;
	std::cout << *b5 << std::endl;
	b5->executeForm(*pr);
	pr->beSigned(*b5);
	b5->executeForm(*pr);
	std::cout << *pr << std::endl;
	std::cout << *b5 << std::endl;
	std::cout << std::endl;
	std::cout << "______________ DELETE FORMS _______________" << std::endl;
	delete sh;
	delete rb;
	delete pr;
	delete pr2;
	std::cout << "______________ DELETE INTERN AND BUREAUCRAT _______________" << std::endl;
	delete i;
	delete b5;
	return 0;
}
