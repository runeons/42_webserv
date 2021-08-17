# include "Bureaucrat.hpp"

int main(void)
{
	std::cout << "______________ CONSTRUCTOR ERRORS _______________" << std::endl;
	Bureaucrat *err1 = new Bureaucrat("Napo", 0);
	Bureaucrat *err2 = new Bureaucrat("Napo", -1);
	Bureaucrat *err3 = new Bureaucrat("Napo", 151);
	Bureaucrat *err4 = new Bureaucrat("Napo", 2147483647);
	Bureaucrat *err5 = new Bureaucrat("Napo", -2147483648);
	(void)err1;
	(void)err2;
	(void)err3;
	(void)err4;
	(void)err5;
	std::cout << "______________ BUREAUCRAT GRADE 1 _______________" << std::endl;
	Bureaucrat *b1 = new Bureaucrat("Napo", 1);
	std::cout << *b1 << std::endl;
	b1->incrementGrade();
	b1->decrementGrade();
	b1->incrementGrade();
	std::cout << "______________ BUREAUCRAT GRADE 150 _______________" << std::endl;
	Bureaucrat *b150 = new Bureaucrat("Napo", 150);
	std::cout << *b150 << std::endl;
	b150->decrementGrade();
	b150->incrementGrade();
	b150->decrementGrade();
	std::cout << "______________ BUREAUCRAT GRADE 10 _______________" << std::endl;
	Bureaucrat *b10 = new Bureaucrat("Napo", 10);
	std::cout << *b10 << std::endl;
	b10->incrementGrade();
	b10->incrementGrade();
	b10->incrementGrade();
	b10->incrementGrade();
	b10->incrementGrade();
	b10->incrementGrade();
	b10->incrementGrade();
	b10->incrementGrade();
	b10->incrementGrade();
	b10->incrementGrade();
	b10->incrementGrade();
	b10->decrementGrade();
	b10->decrementGrade();
	b10->decrementGrade();
	b10->decrementGrade();
	b10->decrementGrade();
	b10->decrementGrade();
	b10->decrementGrade();
	b10->decrementGrade();
	b10->decrementGrade();
	std::cout << "______________ DELETE ALL _______________" << std::endl;
	delete b1;
	delete b10;
	delete b150;
	return 0;
}

