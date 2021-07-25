/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestParser.class.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 15:33:57 by tharchen          #+#    #+#             */
/*   Updated: 2021/07/23 01:53:22 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUESTPARSER_CLASS_HPP
# define REQUESTPARSER_CLASS_HPP
# include "webserv.hpp"

# define STRABS(X) (X == '\t' ? 't' : X == '\n' ? 'n' : X == '\r' ? 'r' : X == '\v' ? 'v' : X == '\f' ? 'f' : X)
# define SSTRABS(X) (X == '\t' ? '\\' : X == '\n' ? '\\' : X == '\r' ? '\\' : X == '\v' ? '\\' : X == '\f' ? '\\' : '\0')

# define PAT_SP		" "
# define PAT_HTAB	"\t"
# define PAT_CR		"\r"
# define PAT_LF		"\n"
# define PAT_DOT	"."
# define PAT_DDOT	":"
# define PAT_HYPHEN	"-"
# define PAT_SLASH	"/"
# define PAT_CRLF	PAT_CR""PAT_LF


typedef enum		e_methods
{
	// default
	METHOD_NONE,
	// implemented
	METHOD_GET,
	METHOD_POST,
	METHOD_DELETE,
	// none implemented
	METHOD_COPY,
	METHOD_OPTIONS,
	METHOD_HEAD,
	METHOD_LINK,
	METHOD_MOVE,
	METHOD_PUT,
	METHOD_PATCH,
	METHOD_TRACE,
	METHOD_UNLINK,
	METHOD_WRAPPED
}					t_methods;

class RequestParser
{
	typedef std::map<std::string, std::string>::iterator headers_iterator;
	typedef std::vector<std::string>::iterator vector_iterator;
	protected:
		// PROTECTED MEMBERS ATRIBUTE : PROMA

		// PROTECTED MEMBERS FUNCTION : PROMF

	private:
		// PRIVATE MEMBERS ATRIBUTE : PRIMA
		std::string		_request_raw;
		size_t			_head;
		size_t			_head_last_digest;

		enum e_methods	_method;
		std::string		_resource;
		std::string		_http_version;
		std::string		_body;
		std::map<std::string, std::string>	_header_fields;
		// PRIVATE MEMBERS FUNCTION : PRIMF
		RequestParser(void);  // constructor

		int			eat(std::string to_eat);
		int			eat(int to_eat);
		int			eat_no_casesensitive(std::string to_eat);
		int			eatall(void);
		std::string	digest(void);

		int		DOT(void);
		int		SLASH(void);
		int		SP(void);
		int		HTAB(void);
		int		CR(void);
		int		LF(void);
		int		DDOT(void);
		int		HYPHEN(void);
		int		CRLF(void);
		int		ALPHA(void);
		int		DIGIT(void);
		int		ALPHA_DIGIT_HYPHEN(void);
		int		group_ALPHA_DIGIT_HYPHEN(void);
		int		TEXT(void);
		int		OWS(void);
		int		VCHAR(void);
		int		ANYTEXT(void);
		int		implemented_headfield_data(void);
		int		unimplemented_headfield_data(void);
		// header
		int		host(void);
		int		accept_Charset(void);
		int		accept_Encoding(void);
		int		accept_Language(void);
		int		authorization(void);
		int		from(void);
		int		accept(void);
		int		if_Modified_Since(void);
		int		proxy_Authorization(void);
		int		range(void);
		int		referer(void);
		int		unless(void);
		int		user_Agent(void);

		int		unimplemented_headfield(void);
		int		implemented_headfield(void);
		int		headfield(void);
		int		group_headfield(void);
		int		group_content(void);
		int		method(void);
		int		request_target(void);
		int		HTTP_version(void);
		int		line_request(void);
		int		full_request(void);
		int		request(void);

		void	debug(void)
		{
			printf("[");
			for (size_t i = 0; this->_request_raw[i]; i++)
			{
				if (this->_head == i)
					printf("H");
				else
					printf(" ");
				if (this->_request_raw[i] == '\t'
					|| this->_request_raw[i] == '\n'
					|| this->_request_raw[i] == '\r'
					|| this->_request_raw[i] == '\v'
					|| this->_request_raw[i] == '\f')
					printf(" ");
			}
			printf("]\n[");
			printf(C_G_GRAY);
			for (size_t i = 0; this->_request_raw[i]; i++)
				printf("%c%c", SSTRABS(this->_request_raw[i]), STRABS(this->_request_raw[i]));
			printf(C_RES"]\n");
		}
	public:
		class EattingBadPatternException: public std::exception
		{
			public:
				EattingBadPatternException(int eno, std::string msg): _msg(msg) { this->_eno = eno; }
				virtual ~EattingBadPatternException() throw() {}
				const char	*what() const throw () {
					return (this->_msg.c_str());
				}
			private:
				int				_eno;
				std::string		_msg;
		};
		// CONSTRUCTOR / DESTRUCTOR : CD
		RequestParser(std::string request_raw);  // constructor
		RequestParser(const RequestParser &src);  // constructor by copy
		virtual ~RequestParser(void); // destructor
		// OVERLOADED OPERATORS : OVOP
		RequestParser	&operator=(const RequestParser &rhs);
		// GETTERS / SETTERS : GS
		enum e_methods	get__method(void) const;
		std::string		get__resource(void) const;
		std::string		get__http_version(void) const;
		std::string		get__body(void) const;
		// PUBLIC MEMBERS ATRIBUTE : PUMA

		// PUBLIC MEMBERS FUNCTION : PUMF
		void		print_request_info(void);
		std::string	get_method_name(void);

		void	init_parser_for_test(std::string request_test);
		void	tester(void);
};

std::ostream	&operator<<(std::ostream &o, const RequestParser &i);
#endif


/*
** ***********************************************
** ******************* METHODS *******************
**
** ***************** implemented *****************
** GET
** POST
** DELETE
** *************** none implemented **************
** COPY
** OPTIONS
** HEAD
** LINK
** MOVE
** PUT
** PATCH
** TRACE
** UNLINK
** WRAPPED
**
**
** ******************* HEADERS *******************
**
** **************** General-Header ***************
** Cache-Control
** Connection
** Date
** Forwarded
** Keep-Alive
** MIME-Version
** Pragma
** Upgrade
**
** **************** Request-Header ***************
** Accept
** Accept-Charset
** Accept-Encoding
** Accept-Language
** Authorization
** From
** Host
** If-Modified-Since
** Proxy-Authorization
** Range
** Referer
** Unless
** User-Agent
**
** ***************** Entity-Header ***************
** Allow
** Content-Encoding
** Content-Language
** Content-Length
** Content-MD5
** Content-Range
** Content-Type
** Content-Version
** Derived-From
** Expires
** Last-Modified
** Link
** Title
** Transfer-Encoding
** URI-header
** ***********************************************
*/