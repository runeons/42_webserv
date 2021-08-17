# include "Bureaucrat.hpp"
# include "Form.hpp"

void	ex00(void)
{
	std::cout << "__________________________________________________" << std::endl;
	std::cout << "______________________ EX00 ______________________" << std::endl;
	std::cout << "__________________________________________________" << std::endl;
	std::cout << std::endl;
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
}

void	ex01()
{
	std::cout << "__________________________________________________" << std::endl;
	std::cout << "______________________ EX01 ______________________" << std::endl;
	std::cout << "__________________________________________________" << std::endl;
	std::cout << std::endl;

}

int main(void)
{
	ex00();
	std::cout << "______________ CONSTRUCTOR ERRORS _______________" << std::endl;
	Form *err1 = new Form("Err", 10, 0);
	Form *err2 = new Form("Err", 10, -1);
	Form *err3 = new Form("Err", 10, 151);
	Form *err4 = new Form("Err", 10, 2147483647);
	Form *err5 = new Form("Err", 10, -2147483648);
	Form *err6 = new Form("Err", 0, 10);
	Form *err7 = new Form("Err", -1, 10);
	Form *err8 = new Form("Err", 151, 10);
	Form *err9 = new Form("Err", 2147483647, 10);
	Form *err10 = new Form("Err", -2147483648, 10);
	Form *err11 = new Form("Err", -1, 151);
	Form *err12 = new Form("Err", 151, -1);
	Form *err13 = new Form("Err", -1, -1);
	Form *err14 = new Form("Err", 151, 151);
	(void)err1;
	(void)err2;
	(void)err3;
	(void)err4;
	(void)err5;
	(void)err6;
	(void)err7;
	(void)err8;
	(void)err9;
	(void)err10;
	(void)err11;
	(void)err12;
	(void)err13;
	(void)err14;
	std::cout << "______________ FORM overload << _______________" << std::endl;
	Form *f = new Form("Register", 2, 3);
	std::cout << *f << std::endl;
	std::cout << "______________ FORM SIGNING _______________" << std::endl;
	Bureaucrat *b1 = new Bureaucrat("Napo", 5);
	std::cout << *b1 << std::endl;
	f->beSigned(*b1);
	std::cout << *f << std::endl;
	b1->incrementGrade();
	f->beSigned(*b1);
	std::cout << *f << std::endl;
	b1->incrementGrade();
	f->beSigned(*b1);
	std::cout << *f << std::endl;
	b1->incrementGrade();
	f->beSigned(*b1);
	std::cout << *f << std::endl;
	b1->incrementGrade();
	f->beSigned(*b1);
	std::cout << *f << std::endl;
	b1->incrementGrade();
	f->beSigned(*b1);
	std::cout << *f << std::endl;
	std::cout << "______________ DELETE ALL _______________" << std::endl;
	delete b1;
	delete f;
	return 0;
}

