#ifndef EXCEPTIONS_HPP
# define EXCEPTIONS_HPP

# include "webserv.hpp"

class Exceptions
{
	public :

		class ServerSocket : public std::exception
		{
			public:
				virtual const char *what() const throw()
				{ return ("Error creation server socket"); }
		};

		class BindServer : public std::exception
		{
			public:
				virtual const char *what() const throw()
				{ return ("Failed to bind address and port"); }
		};

		class ServerListen : public std::exception
		{
			public:
				virtual const char *what() const throw()
				{ return ("Server failed to listen"); }
		};

		class InvalidAddress : public std::exception
		{
			public:
				virtual const char *what() const throw()
				{ return ("Invalid address - not supported"); }
		};
};

#endif
