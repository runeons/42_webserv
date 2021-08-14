
#ifndef EXCEPTIONS_HPP
# define EXCEPTIONS_HPP

# include <webserv.hpp>

class Exceptions
{
	public :

		class ServerException: public std::exception
		{
			private:
				std::string _msg;
			public:
				ServerException(std::string msg): _msg(msg) {}
				virtual ~ServerException(void) throw() {}
				virtual const char *what() const throw() {
					return (this->_msg.c_str());
				}
		};

		class ClientException: public std::exception
		{
			private:
				std::string _msg;
			public:
				ClientException(std::string msg): _msg(msg) {}
				virtual ~ClientException(void) throw() {}
				virtual const char *what() const throw() {
					return (this->_msg.c_str());
				}
		};

		class LexerException: public std::exception
		{
			private:
				std::string _msg;
			public:
				LexerException(std::string msg): _msg(msg) {/*std::cout << "LexerException: " << this->_msg << std::endl;*/}  // constructor
				virtual ~LexerException(void) throw() {} // destructor
				virtual const char *what() const throw() {
					std::cout << "LexerException: " << this->_msg << std::endl;
					return (this->_msg.c_str());
				}
		};

		class ParserException: public std::exception
		{
			private:
				std::string _msg;
			public:
				ParserException(std::string msg): _msg(msg) {/*std::cout << "ParserException: " << this->_msg << std::endl;*/}  // constructor
				virtual ~ParserException(void) throw() {} // destructor
				virtual const char *what() const throw() {
					std::cout << "ParserException: " << this->_msg << std::endl;
					return (this->_msg.c_str());
				}
		};

		class HTTP_ErrorStatusException: public std::exception
		{
			private:
				int _status_code;
			public:
				HTTP_ErrorStatusException(int status_code): _status_code(status_code) {}  // constructor
				virtual ~HTTP_ErrorStatusException(void) throw() {} // destructor
				virtual const char *what() const throw() {
					std::cout << _status_code << std::endl;
					return ("error http generated");
				}
				int get__status(void) const
				{
					return (_status_code);
				}
		};

};

#endif
