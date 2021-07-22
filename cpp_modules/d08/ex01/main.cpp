# include "Span.hpp"


void	test_add_range(void)
{
	std::cout << CORAIL << "________________________ TESTS WITH ADD RANGE ________________________" << C_RES << std::endl;
	std::cout << GREEN_TREE << "_____________________________________________________________________" << C_RES << std::endl;
	std::cout << GREEN_TREE << "________________ Add range(9, 21) w/ empty class(20) ________________" << C_RES << std::endl;
	std::cout << GREEN_TREE << "_____________________________________________________________________" << C_RES << std::endl;
	std::cout << std::endl;
	Span e(20);
	std::cout << e << std::endl;
	std::cout << CORAIL << "shortestSpan : " << C_RES; e.shortestSpan();;
	std::cout << CORAIL << "longestSpan : " << C_RES; e.longestSpan();;
	e.addRange(9, 21);
	std::cout << e << std::endl;
	std::cout << CORAIL << "longestSpan : " << e.longestSpan() << C_RES << std::endl;
	std::cout << CORAIL << "shortestSpan : " << e.shortestSpan() << C_RES << std::endl;

	std::cout << GREEN_TREE << "_______________________________________________________________" << C_RES << std::endl;
	std::cout << GREEN_TREE << "________________ Add range(9, 21) w/ class(30) ________________" << C_RES << std::endl;
	std::cout << GREEN_TREE << "_______________________________________________________________" << C_RES << std::endl;
	std::cout << std::endl;
	Span c(30);
	c.addNumber(7);
	c.addNumber(3);
	c.addNumber(1);
	c.addNumber(2);
	std::cout << c << std::endl;
	std::cout << CORAIL << "longestSpan : " << c.longestSpan() << C_RES << std::endl;
	std::cout << CORAIL << "shortestSpan : " << c.shortestSpan() << C_RES << std::endl;
	c.addRange(9, 21);
	std::cout << c << std::endl;
	std::cout << CORAIL << "longestSpan : " << c.longestSpan() << C_RES << std::endl;
	std::cout << CORAIL << "shortestSpan : " << c.shortestSpan() << C_RES << std::endl;
	std::cout << GREEN_TREE << "________________ Add range(0, 0) ________________" << C_RES << std::endl;
	c.addRange(0, 0);
	std::cout << c << std::endl;
	std::cout << GREEN_TREE << "________________ Add range(4, 2) ________________" << C_RES << std::endl;
	c.addRange(4, 2);
	std::cout << c << std::endl;

	std::cout << GREEN_TREE << "________________ Add range(-1, -5) ________________" << C_RES << std::endl;
	c.addRange(-1, -5);
	std::cout << c << std::endl;


	std::cout << GREEN_TREE << "_____________________________________________________________" << C_RES << std::endl;
	std::cout << GREEN_TREE << "________________ Add range(9, 21) w/ class(10) ________________" << C_RES << std::endl;
	std::cout << GREEN_TREE << "_____________________________________________________________" << C_RES << std::endl;
	std::cout << std::endl;
	Span d(10);
	d.addNumber(7);
	d.addNumber(3);
	d.addNumber(1);
	d.addNumber(2);
	std::cout << d << std::endl;
	std::cout << CORAIL << "longestSpan : " << d.longestSpan() << C_RES << std::endl;
	std::cout << CORAIL << "shortestSpan : " << d.shortestSpan() << C_RES << std::endl;
	d.addRange(9, 21);
	std::cout << d << std::endl;
	std::cout << CORAIL << "longestSpan : " << d.longestSpan() << C_RES << std::endl;
	std::cout << CORAIL << "shortestSpan : " << d.shortestSpan() << C_RES << std::endl;

	std::cout << GREEN_TREE << "_____________________________________________________________" << C_RES << std::endl;
	std::cout << GREEN_TREE << "________________ Add range(5, 5) w/ class(5) ________________" << C_RES << std::endl;
	std::cout << GREEN_TREE << "_____________________________________________________________" << C_RES << std::endl;
	std::cout << std::endl;
	Span f(5);
	f.addNumber(7);
	f.addNumber(3);
	f.addNumber(1);
	f.addNumber(2);
	std::cout << f << std::endl;
	std::cout << CORAIL << "longestSpan : " << f.longestSpan() << C_RES << std::endl;
	std::cout << CORAIL << "shortestSpan : " << f.shortestSpan() << C_RES << std::endl;
	f.addRange(5, 5);
	std::cout << f << std::endl;
	std::cout << CORAIL << "longestSpan : " << f.longestSpan() << C_RES << std::endl;
	std::cout << CORAIL << "shortestSpan : " << f.shortestSpan() << C_RES << std::endl;

	std::cout << GREEN_TREE << "_____________________________________________________________" << C_RES << std::endl;
	std::cout << GREEN_TREE << "________________ Add range(5, 6) w/ class(5) ________________" << C_RES << std::endl;
	std::cout << GREEN_TREE << "_____________________________________________________________" << C_RES << std::endl;
	std::cout << std::endl;
	Span g(5);
	g.addNumber(7);
	g.addNumber(3);
	g.addNumber(1);
	g.addNumber(2);
	std::cout << g << std::endl;
	std::cout << CORAIL << "longestSpan : " << g.longestSpan() << C_RES << std::endl;
	std::cout << CORAIL << "shortestSpan : " << g.shortestSpan() << C_RES << std::endl;
	g.addRange(5, 6);
	std::cout << g << std::endl;
	std::cout << CORAIL << "longestSpan : " << g.longestSpan() << C_RES << std::endl;
	std::cout << CORAIL << "shortestSpan : " << g.shortestSpan() << C_RES << std::endl;
}

void	test_basics(void)
{
	std::cout << CORAIL << "________________________ BASIC TESTS ________________________" << C_RES << std::endl;

	std::cout << GREEN_TREE << "________________ Subject example ________________" << std::endl << C_RES << std::endl;
	Span sp = Span(5);
	sp.addNumber(5);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);
	std::cout << sp.shortestSpan() << std::endl;
	std::cout << sp.longestSpan() << std::endl;

	std::cout << GREEN_TREE << "________________ Empty class(3) ________________" << std::endl << C_RES << std::endl;
	Span a(3);
	std::cout << a << std::endl;
	std::cout << CORAIL << "shortestSpan : " << C_RES; a.shortestSpan();;
	std::cout << CORAIL << "longestSpan : " << C_RES; a.longestSpan();;
	std::cout << std::endl;
	std::cout << GREEN_TREE << "________________ addNumber X1 ________________" << std::endl << C_RES << std::endl;
	a.addNumber(7);
	std::cout << a << std::endl;
	std::cout << CORAIL << "shortestSpan : " << C_RES; a.shortestSpan();;
	std::cout << CORAIL << "longestSpan : " << C_RES; a.longestSpan();;
	std::cout << std::endl;
	std::cout << GREEN_TREE << "________________ addNumber X1 ________________" << std::endl << C_RES << std::endl;
	a.addNumber(3);
	std::cout << a << std::endl;
	std::cout << CORAIL << "longestSpan : " << a.longestSpan() << C_RES << std::endl;
	std::cout << CORAIL << "shortestSpan : " << a.shortestSpan() << C_RES << std::endl;
	std::cout << GREEN_TREE << "________________ addNumber X2 ________________" << std::endl << C_RES << std::endl;
	a.addNumber(1);
	a.addNumber(2);
	std::cout << a << std::endl;
	std::cout << CORAIL << "longestSpan : " << a.longestSpan() << C_RES << std::endl;
	std::cout << CORAIL << "shortestSpan : " << a.shortestSpan() << C_RES << std::endl;
	std::cout << GREEN_TREE << "________________ unordered longer shortestSpan ________________" << std::endl << C_RES << std::endl;
	Span b(6);
	b.addNumber(777);
	b.addNumber(7);
	b.addNumber(7777);
	b.addNumber(777777);
	b.addNumber(77);
	b.addNumber(77777);
	std::cout << b << std::endl;
	std::cout << CORAIL << "longestSpan : " << b.longestSpan() << C_RES << std::endl;
	std::cout << CORAIL << "shortestSpan : " << b.shortestSpan() << C_RES << std::endl;
	std::cout << GREEN_TREE << "________________ Test copy ________________" << std::endl << C_RES << std::endl;
	Span src(8);
	src.addNumber(1);
	src.addNumber(3);
	src.addNumber(5);
	src.addNumber(7);
	src.addNumber(9);
	Span cpy(src);
	std::cout << "src : " << src;
	std::cout << CORAIL << "longestSpan : " << src.longestSpan() << C_RES << std::endl;
	std::cout << CORAIL << "shortestSpan : " << src.shortestSpan() << C_RES << std::endl;
	std::cout << "cpy : " << cpy;
	std::cout << CORAIL << "longestSpan : " << cpy.longestSpan() << C_RES << std::endl;
	std::cout << CORAIL << "shortestSpan : " << cpy.shortestSpan() << C_RES << std::endl;
	std::cout << std::endl;
	std::cout << "... add number to src ..." << std::endl;
	src.addNumber(11);
	std::cout << "src : " << src;
	std::cout << "cpy : " << cpy;
	std::cout << GREEN_TREE << "________________ Test assignation ________________" << std::endl << C_RES << std::endl;
	Span ass(2);
	ass = src;
	std::cout << "src : " << src;
	std::cout << CORAIL << "longestSpan : " << src.longestSpan() << C_RES << std::endl;
	std::cout << CORAIL << "shortestSpan : " << src.shortestSpan() << C_RES << std::endl;
	std::cout << "ass : " << ass;
	std::cout << CORAIL << "longestSpan : " << ass.longestSpan() << C_RES << std::endl;
	std::cout << CORAIL << "shortestSpan : " << ass.shortestSpan() << C_RES << std::endl;
	std::cout << std::endl;
	std::cout << "... add number to src ..." << std::endl;
	src.addNumber(13);
	std::cout << "src : " << src;
	std::cout << CORAIL << "longestSpan : " << src.longestSpan() << C_RES << std::endl;
	std::cout << CORAIL << "shortestSpan : " << src.shortestSpan() << C_RES << std::endl;
	std::cout << "ass : " << ass;
	std::cout << CORAIL << "longestSpan : " << ass.longestSpan() << C_RES << std::endl;
	std::cout << CORAIL << "shortestSpan : " << ass.shortestSpan() << C_RES << std::endl;
	std::cout << "cpy : " << cpy;
	std::cout << CORAIL << "longestSpan : " << cpy.longestSpan() << C_RES << std::endl;
	std::cout << CORAIL << "shortestSpan : " << cpy.shortestSpan() << C_RES << std::endl;
}

void	test_long(void)
{
	std::cout << GREEN_TREE << "________________ Empty class(30000) ________________" << std::endl << C_RES << std::endl;
	Span a(30000);
	std::cout << a << std::endl;
	a.addNumber(7);
	a.addNumber(3);
	a.addNumber(1);
	a.addNumber(2);
	std::cout << CORAIL << "longestSpan : " << a.longestSpan() << C_RES << std::endl;
	std::cout << CORAIL << "shortestSpan : " << a.shortestSpan() << C_RES << std::endl;
	std::cout << std::endl;
	std::cout << GREEN_TREE << "________________ addRange(10000, 30000) ________________" << std::endl << C_RES << std::endl;
	a.addRange(10000, 22000);
	std::cout << a << std::endl;
	std::cout << CORAIL << "longestSpan : " << a.longestSpan() << C_RES << std::endl;
	std::cout << CORAIL << "shortestSpan : " << a.shortestSpan() << C_RES << std::endl;
	std::cout << std::endl;
}

int main(void)
{

	test_add_range();
	test_basics();
	// test_long();
	return 0;
}
