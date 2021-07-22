# include "MutantStack.hpp"
# include <list>

void	test_subject(void)
{
	std::cout << GREEN_TREE << std::endl << "________________ SUBJECT MAIN ________________" << std::endl << C_RES << std::endl;
	MutantStack<int> mstack;
	mstack.push(5);
	mstack.push(17);
	std::cout << mstack.top() << std::endl;
	mstack.pop();
	std::cout << mstack.size() << std::endl;
	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	//[...]
	mstack.push(0);
	MutantStack<int>::iterator it = mstack.begin();
	MutantStack<int>::iterator ite = mstack.end();
	++it;
	--it;
	while (it != ite)
	{
		std::cout << *it << std::endl;
		++it;
	}
	std::stack<int> s(mstack);
	std::cout << GREEN_TREE << std::endl << "________________ OUTPUT W/ LIST ________________" << std::endl << C_RES << std::endl;
	std::list<int> lststack;
	lststack.push_back(5);
	lststack.push_back(17);
	std::cout << lststack.back() << std::endl;
	lststack.pop_back();
	std::cout << lststack.size() << std::endl;
	lststack.push_back(3);
	lststack.push_back(5);
	lststack.push_back(737);
	//[...]
	lststack.push_back(0);
	std::list<int>::iterator it_lst = lststack.begin();
	std::list<int>::iterator ite_lst = lststack.end();
	++it_lst;
	--it_lst;
	while (it_lst != ite_lst)
	{
		std::cout << *it_lst << std::endl;
		++it_lst;
	}
}

void	test_int(void)
{
	std::cout << CORAIL << std::endl << "______________________________________________" << C_RES;
	std::cout << CORAIL << std::endl << "________________ TESTS W/ INT ________________" << C_RES;
	std::cout << CORAIL << std::endl << "______________________________________________" << C_RES << std::endl;
	std::cout << GREEN_TREE << std::endl << "________________ BASIC TESTS _________________" << std::endl << C_RES << std::endl;
	std::cout << "... create empty mstack ..." << std::endl;
	MutantStack<int> m1;
	MutantStack<int>::iterator it1;
	MutantStack<int>::iterator itend1;

	std::cout << "... check if empty ..." << std::endl;
	if (m1.empty())
		std::cout << CORAIL << "Empty" << std::endl << C_RES;
	else
		std::cout << SKY_BLUE << "Not empty" << std::endl << C_RES;
	std::cout << "... get size ..." << std::endl;
	std::cout << BROWN << "Size : " << m1.size() << std::endl << C_RES;

	std::cout << std::endl << "... push one (1) ..." << std::endl;
	m1.push(1);
	std::cout << "... check if empty ..." << std::endl;
	if (m1.empty())
		std::cout << CORAIL << "Empty" << std::endl << C_RES;
	else
		std::cout << SKY_BLUE << "Not empty" << std::endl << C_RES;
	std::cout << "... get size ..." << std::endl;
	std::cout << BROWN << "Size : " << m1.size() << std::endl << C_RES;
	std::cout << "... get top one ..." << std::endl;
	std::cout << BROWN << "Top : " << m1.top() << std::endl << C_RES;


	std::cout << std::endl << "... pop one ..." << std::endl;
	m1.pop();
	std::cout << "... check if empty ..." << std::endl;
	if (m1.empty())
		std::cout << CORAIL << "Empty" << std::endl << C_RES;
	else
		std::cout << SKY_BLUE << "Not empty" << std::endl << C_RES;
	std::cout << "... get size ..." << std::endl;
	std::cout << BROWN << "Size : " << m1.size() << std::endl << C_RES;

	std::cout << std::endl << "... push five ..." << std::endl;
	m1.push(1);
	m1.push(2);
	m1.push(3);
	m1.push(4);
	m1.push(5);
	std::cout << GREY << "... display ..." << C_RES << std::endl;
	itend1 = m1.end();
	for (it1 = m1.begin(); it1 != itend1; it1++)
		std::cout << BROWN << *it1 << C_RES << " ";
	std::cout << std::endl;
	std::cout << "... check if empty ..." << std::endl;
	if (m1.empty())
		std::cout << CORAIL << "Empty" << std::endl << C_RES;
	else
		std::cout << SKY_BLUE << "Not empty" << std::endl << C_RES;
	std::cout << "... get size ..." << std::endl;
	std::cout << BROWN << "Size : " << m1.size() << std::endl << C_RES;
	std::cout << "... get top one ..." << std::endl;
	std::cout << BROWN << "Top : " << m1.top() << std::endl << C_RES;
	std::cout << GREEN_TREE << std::endl << "________________ ASSIGNATION TESTS _________________" << std::endl << C_RES << std::endl;
	std::cout << "... create empty mstack ..." << std::endl;
	MutantStack<int> dst;
	std::cout << "... assign src to dst ..." << std::endl;
	dst = m1;
	std::cout << GREY << "... display dst ..." << C_RES << std::endl;
	itend1 = dst.end();
	for (it1 = dst.begin(); it1 != itend1; it1++)
		std::cout << BROWN << *it1 << C_RES << " ";
	std::cout << std::endl;
	std::cout << GREY << "... display src ..." << C_RES << std::endl;
	itend1 = m1.end();
	for (it1 = m1.begin(); it1 != itend1; it1++)
		std::cout << BROWN << *it1 << C_RES << " ";
	std::cout << std::endl;
	std::cout << "... push x1 to src ..." << std::endl;
	m1.push(9);
	std::cout << "... pop  x1 from dst ..." << std::endl;
	dst.pop();
	std::cout << GREY << "... display dst ..." << C_RES << std::endl;
	itend1 = dst.end();
	for (it1 = dst.begin(); it1 != itend1; it1++)
		std::cout << BROWN << *it1 << C_RES << " ";
	std::cout << std::endl;
	std::cout << GREY << "... display src ..." << C_RES << std::endl;
	itend1 = m1.end();
	for (it1 = m1.begin(); it1 != itend1; it1++)
		std::cout << BROWN << *it1 << C_RES << " ";
	std::cout << std::endl;

	std::cout << GREEN_TREE << std::endl << "________________ COPY TESTS _________________" << std::endl << C_RES << std::endl;
	std::cout << "... create copy from src ..." << std::endl;
	MutantStack<int> cpy(m1);
	std::cout << GREY << "... display cpy ..." << C_RES << std::endl;
	itend1 = cpy.end();
	for (it1 = cpy.begin(); it1 != itend1; it1++)
		std::cout << BROWN << *it1 << C_RES << " ";
	std::cout << std::endl;
	std::cout << GREY << "... display src ..." << C_RES << std::endl;
	itend1 = m1.end();
	for (it1 = m1.begin(); it1 != itend1; it1++)
		std::cout << BROWN << *it1 << C_RES << " ";
	std::cout << std::endl;
	std::cout << "... push x1 to src ..." << std::endl;
	m1.push(17);
	std::cout << "... pop  x1 from cpy ..." << std::endl;
	cpy.pop();
	std::cout << GREY << "... display cpy ..." << C_RES << std::endl;
	itend1 = cpy.end();
	for (it1 = cpy.begin(); it1 != itend1; it1++)
		std::cout << BROWN << *it1 << C_RES << " ";
	std::cout << std::endl;
	std::cout << GREY << "... display src ..." << C_RES << std::endl;
	itend1 = m1.end();
	for (it1 = m1.begin(); it1 != itend1; it1++)
		std::cout << BROWN << *it1 << C_RES << " ";
	std::cout << std::endl;
	MutantStack<int>::reverse_iterator it_r;
	MutantStack<int>::reverse_iterator itend_r;
	std::cout << SKY_BLUE << "... display reverse cpy ..." << C_RES << std::endl;
	itend_r = cpy.rend();
	for (it_r = cpy.rbegin(); it_r != itend_r; it_r++)
		std::cout << BROWN << *it_r << C_RES << " ";
	std::cout << std::endl;
	std::cout << SKY_BLUE << "... display reverse src ..." << C_RES << std::endl;
	itend_r = m1.rend();
	for (it_r = m1.rbegin(); it_r != itend_r; it_r++)
		std::cout << BROWN << *it_r << C_RES << " ";
	std::cout << std::endl;
}

void	test_str(void)
{
	std::cout << CORAIL << std::endl << "__________________________________________________" << C_RES;
	std::cout << CORAIL << std::endl << "________________ TESTS W/ STRINGS ________________" << C_RES;
	std::cout << CORAIL << std::endl << "__________________________________________________" << C_RES << std::endl;
	std::cout << GREEN_TREE << std::endl << "________________ BASIC TESTS _________________" << std::endl << C_RES << std::endl;
	MutantStack<std::string>::iterator it1;
	MutantStack<std::string>::iterator itend1;
	std::cout << "... create empty mstack ..." << std::endl;
	MutantStack<std::string> m1;
	std::cout << "... check if empty ..." << std::endl;
	if (m1.empty())
		std::cout << CORAIL << "Empty" << std::endl << C_RES;
	else
		std::cout << SKY_BLUE << "Not empty" << std::endl << C_RES;
	std::cout << "... get size ..." << std::endl;
	std::cout << BROWN << "Size : " << m1.size() << std::endl << C_RES;

	std::cout << std::endl << "... push one (1) ..." << std::endl;
	m1.push("abc");
	std::cout << "... check if empty ..." << std::endl;
	if (m1.empty())
		std::cout << CORAIL << "Empty" << std::endl << C_RES;
	else
		std::cout << SKY_BLUE << "Not empty" << std::endl << C_RES;
	std::cout << "... get size ..." << std::endl;
	std::cout << BROWN << "Size : " << m1.size() << std::endl << C_RES;
	std::cout << "... get top one ..." << std::endl;
	std::cout << BROWN << "Top : " << m1.top() << std::endl << C_RES;


	std::cout << std::endl << "... pop one ..." << std::endl;
	m1.pop();
	std::cout << "... check if empty ..." << std::endl;
	if (m1.empty())
		std::cout << CORAIL << "Empty" << std::endl << C_RES;
	else
		std::cout << SKY_BLUE << "Not empty" << std::endl << C_RES;
	std::cout << "... get size ..." << std::endl;
	std::cout << BROWN << "Size : " << m1.size() << std::endl << C_RES;

	std::cout << std::endl << "... push five ..." << std::endl;
	m1.push("abc");
	m1.push("def");
	m1.push("ghi");
	m1.push("jkl");
	m1.push("mnop");
	std::cout << GREY << "... display ..." << C_RES << std::endl;
	itend1 = m1.end();
	for (it1 = m1.begin(); it1 != itend1; it1++)
		std::cout << BROWN << *it1 << C_RES << " ";
	std::cout << std::endl;

	std::cout << "... check if empty ..." << std::endl;
	if (m1.empty())
		std::cout << CORAIL << "Empty" << std::endl << C_RES;
	else
		std::cout << SKY_BLUE << "Not empty" << std::endl << C_RES;
	std::cout << "... get size ..." << std::endl;
	std::cout << BROWN << "Size : " << m1.size() << std::endl << C_RES;
	std::cout << "... get top one ..." << std::endl;
	std::cout << BROWN << "Top : " << m1.top() << std::endl << C_RES;
	std::cout << GREEN_TREE << std::endl << "________________ ASSIGNATION TESTS _________________" << std::endl << C_RES << std::endl;
	std::cout << "... create empty mstack ..." << std::endl;
	MutantStack<std::string> dst;
	std::cout << "... assign src to dst ..." << std::endl;
	dst = m1;
	std::cout << GREY << "... display dst ..." << C_RES << std::endl;
	itend1 = dst.end();
	for (it1 = dst.begin(); it1 != itend1; it1++)
		std::cout << BROWN << *it1 << C_RES << " ";
	std::cout << std::endl;
	std::cout << GREY << "... display src ..." << C_RES << std::endl;
	itend1 = m1.end();
	for (it1 = m1.begin(); it1 != itend1; it1++)
		std::cout << BROWN << *it1 << C_RES << " ";
	std::cout << std::endl;
	std::cout << "... push x1 to src ..." << std::endl;
	m1.push("xyz");
	std::cout << "... pop  x1 from dst ..." << std::endl;
	dst.pop();
	std::cout << GREY << "... display dst ..." << C_RES << std::endl;
	itend1 = dst.end();
	for (it1 = dst.begin(); it1 != itend1; it1++)
		std::cout << BROWN << *it1 << C_RES << " ";
	std::cout << std::endl;
	std::cout << GREY << "... display src ..." << C_RES << std::endl;
	itend1 = m1.end();
	for (it1 = m1.begin(); it1 != itend1; it1++)
		std::cout << BROWN << *it1 << C_RES << " ";
	std::cout << std::endl;

	std::cout << GREEN_TREE << std::endl << "________________ COPY TESTS _________________" << std::endl << C_RES << std::endl;
	std::cout << "... create copy from src ..." << std::endl;
	MutantStack<std::string> cpy(m1);
	std::cout << GREY << "... display cpy ..." << C_RES << std::endl;
	itend1 = cpy.end();
	for (it1 = cpy.begin(); it1 != itend1; it1++)
		std::cout << BROWN << *it1 << C_RES << " ";
	std::cout << std::endl;
	std::cout << GREY << "... display src ..." << C_RES << std::endl;
	itend1 = m1.end();
	for (it1 = m1.begin(); it1 != itend1; it1++)
		std::cout << BROWN << *it1 << C_RES << " ";
	std::cout << std::endl;
	std::cout << "... push x1 to src ..." << std::endl;
	m1.push("ABCD");
	std::cout << "... pop  x1 from cpy ..." << std::endl;
	cpy.pop();
	std::cout << GREY << "... display cpy ..." << C_RES << std::endl;
	itend1 = cpy.end();
	for (it1 = cpy.begin(); it1 != itend1; it1++)
		std::cout << BROWN << *it1 << C_RES << " ";
	std::cout << std::endl;
	std::cout << GREY << "... display src ..." << C_RES << std::endl;
	itend1 = m1.end();
	for (it1 = m1.begin(); it1 != itend1; it1++)
		std::cout << BROWN << *it1 << C_RES << " ";
	std::cout << std::endl;
	MutantStack<std::string>::reverse_iterator it_r;
	MutantStack<std::string>::reverse_iterator itend_r;
	std::cout << SKY_BLUE << "... display reverse cpy ..." << C_RES << std::endl;
	itend_r = cpy.rend();
	for (it_r = cpy.rbegin(); it_r != itend_r; it_r++)
		std::cout << BROWN << *it_r << C_RES << " ";
	std::cout << std::endl;
	std::cout << SKY_BLUE << "... display reverse src ..." << C_RES << std::endl;
	itend_r = m1.rend();
	for (it_r = m1.rbegin(); it_r != itend_r; it_r++)
		std::cout << BROWN << *it_r << C_RES << " ";
	std::cout << std::endl;
}

void	test_float(void)
{
	std::cout << CORAIL << std::endl << "________________________________________________" << C_RES;
	std::cout << CORAIL << std::endl << "________________ TESTS W/ FLOAT ________________" << C_RES;
	std::cout << CORAIL << std::endl << "________________________________________________" << C_RES << std::endl;
	std::cout << GREEN_TREE << std::endl << "________________ BASIC TESTS _________________" << std::endl << C_RES << std::endl;
	std::cout << "... create empty mstack ..." << std::endl;
	MutantStack<float> m1;
	MutantStack<float>::iterator it1;
	MutantStack<float>::iterator itend1;

	std::cout << "... check if empty ..." << std::endl;
	if (m1.empty())
		std::cout << CORAIL << "Empty" << std::endl << C_RES;
	else
		std::cout << SKY_BLUE << "Not empty" << std::endl << C_RES;
	std::cout << "... get size ..." << std::endl;
	std::cout << BROWN << "Size : " << m1.size() << std::endl << C_RES;

	std::cout << std::endl << "... push one (1) ..." << std::endl;
	m1.push(1.01);
	std::cout << "... check if empty ..." << std::endl;
	if (m1.empty())
		std::cout << CORAIL << "Empty" << std::endl << C_RES;
	else
		std::cout << SKY_BLUE << "Not empty" << std::endl << C_RES;
	std::cout << "... get size ..." << std::endl;
	std::cout << BROWN << "Size : " << m1.size() << std::endl << C_RES;
	std::cout << "... get top one ..." << std::endl;
	std::cout << BROWN << "Top : " << m1.top() << std::endl << C_RES;


	std::cout << std::endl << "... pop one ..." << std::endl;
	m1.pop();
	std::cout << "... check if empty ..." << std::endl;
	if (m1.empty())
		std::cout << CORAIL << "Empty" << std::endl << C_RES;
	else
		std::cout << SKY_BLUE << "Not empty" << std::endl << C_RES;
	std::cout << "... get size ..." << std::endl;
	std::cout << BROWN << "Size : " << m1.size() << std::endl << C_RES;

	std::cout << std::endl << "... push five ..." << std::endl;
	m1.push(1.1);
	m1.push(2.2);
	m1.push(3);
	m1.push(4.04);
	m1.push(5.50);
	std::cout << GREY << "... display ..." << C_RES << std::endl;
	itend1 = m1.end();
	for (it1 = m1.begin(); it1 != itend1; it1++)
		std::cout << BROWN << *it1 << C_RES << " ";
	std::cout << std::endl;
	std::cout << "... check if empty ..." << std::endl;
	if (m1.empty())
		std::cout << CORAIL << "Empty" << std::endl << C_RES;
	else
		std::cout << SKY_BLUE << "Not empty" << std::endl << C_RES;
	std::cout << "... get size ..." << std::endl;
	std::cout << BROWN << "Size : " << m1.size() << std::endl << C_RES;
	std::cout << "... get top one ..." << std::endl;
	std::cout << BROWN << "Top : " << m1.top() << std::endl << C_RES;
	std::cout << GREEN_TREE << std::endl << "________________ ASSIGNATION TESTS _________________" << std::endl << C_RES << std::endl;
	std::cout << "... create empty mstack ..." << std::endl;
	MutantStack<float> dst;
	std::cout << "... assign src to dst ..." << std::endl;
	dst = m1;
	std::cout << GREY << "... display dst ..." << C_RES << std::endl;
	itend1 = dst.end();
	for (it1 = dst.begin(); it1 != itend1; it1++)
		std::cout << BROWN << *it1 << C_RES << " ";
	std::cout << std::endl;
	std::cout << GREY << "... display src ..." << C_RES << std::endl;
	itend1 = m1.end();
	for (it1 = m1.begin(); it1 != itend1; it1++)
		std::cout << BROWN << *it1 << C_RES << " ";
	std::cout << std::endl;
	std::cout << "... push x1 to src ..." << std::endl;
	m1.push(9.9);
	std::cout << "... pop  x1 from dst ..." << std::endl;
	dst.pop();
	std::cout << GREY << "... display dst ..." << C_RES << std::endl;
	itend1 = dst.end();
	for (it1 = dst.begin(); it1 != itend1; it1++)
		std::cout << BROWN << *it1 << C_RES << " ";
	std::cout << std::endl;
	std::cout << GREY << "... display src ..." << C_RES << std::endl;
	itend1 = m1.end();
	for (it1 = m1.begin(); it1 != itend1; it1++)
		std::cout << BROWN << *it1 << C_RES << " ";
	std::cout << std::endl;

	std::cout << GREEN_TREE << std::endl << "________________ COPY TESTS _________________" << std::endl << C_RES << std::endl;
	std::cout << "... create copy from src ..." << std::endl;
	MutantStack<float> cpy(m1);
	std::cout << GREY << "... display cpy ..." << C_RES << std::endl;
	itend1 = cpy.end();
	for (it1 = cpy.begin(); it1 != itend1; it1++)
		std::cout << BROWN << *it1 << C_RES << " ";
	std::cout << std::endl;
	std::cout << GREY << "... display src ..." << C_RES << std::endl;
	itend1 = m1.end();
	for (it1 = m1.begin(); it1 != itend1; it1++)
		std::cout << BROWN << *it1 << C_RES << " ";
	std::cout << std::endl;
	std::cout << "... push x1 to src ..." << std::endl;
	m1.push(17.3451);
	std::cout << "... pop  x1 from cpy ..." << std::endl;
	cpy.pop();
	std::cout << GREY << "... display cpy ..." << C_RES << std::endl;
	itend1 = cpy.end();
	for (it1 = cpy.begin(); it1 != itend1; it1++)
		std::cout << BROWN << *it1 << C_RES << " ";
	std::cout << std::endl;
	std::cout << GREY << "... display src ..." << C_RES << std::endl;
	itend1 = m1.end();
	for (it1 = m1.begin(); it1 != itend1; it1++)
		std::cout << BROWN << *it1 << C_RES << " ";
	std::cout << std::endl;
	MutantStack<float>::reverse_iterator it_r;
	MutantStack<float>::reverse_iterator itend_r;
	std::cout << SKY_BLUE << "... display reverse cpy ..." << C_RES << std::endl;
	itend_r = cpy.rend();
	for (it_r = cpy.rbegin(); it_r != itend_r; it_r++)
		std::cout << BROWN << *it_r << C_RES << " ";
	std::cout << std::endl;
	std::cout << SKY_BLUE << "... display reverse src ..." << C_RES << std::endl;
	itend_r = m1.rend();
	for (it_r = m1.rbegin(); it_r != itend_r; it_r++)
		std::cout << BROWN << *it_r << C_RES << " ";
	std::cout << std::endl;
}

int main(void)
{
	test_subject();
	test_int();
	test_str();
	test_float();
	return 0;
}
