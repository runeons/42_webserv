/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exceptions.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantoni <tsantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 18:42:42 by tsantoni          #+#    #+#             */
/*   Updated: 2021/08/03 14:20:39 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXCEPTIONS_HPP
# define EXCEPTIONS_HPP

# include <webserv.hpp>

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

		class RecvFailure : public std::exception
		{
			public:
				virtual const char *what() const throw()
				{ return ("Failed to receive request"); }
		};

		class SendFailure : public std::exception
		{
			public:
				virtual const char *what() const throw()
				{ return ("Failed to send response"); }
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
