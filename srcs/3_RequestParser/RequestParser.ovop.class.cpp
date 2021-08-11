
#include <webserv.hpp>

RequestParser		&RequestParser::operator=(RequestParser const &rhs)
{
	static_cast<void>(rhs);
	return (*this);
}

std::ostream	&operator<<(std::ostream &o, RequestParser const &i)
{
	static_cast<void>(i);
	return (o);
}
