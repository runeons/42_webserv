/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestParser.class.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 19:36:15 by tharchen          #+#    #+#             */
/*   Updated: 2021/07/22 11:48:45 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../webserv.hpp"

// PROTECTED MEMBERS FUNCTION : PROMF

/* ************************************************************************** */
/* ************************************************************************** */

// PRIVATE MEMBERS FUNCTION : PRIMF

static std::string		stolo(std::string s)
{
	for (int i = 0; s[i]; i++)
	{
		if (s[i] >= 'A' && s[i] <= 'Z')
			s[i] += 32;
	}
	return (s);
}

std::string		RequestParser::get_method_name(void)
{
	switch (this->_method) {
		case METHOD_NONE		: return (std::string("NONE"));
		case METHOD_GET			: return (std::string("GET"));
		case METHOD_POST		: return (std::string("POST"));
		case METHOD_DELETE		: return (std::string("DELETE"));
		case METHOD_COPY		: return (std::string("COPY"));
		case METHOD_OPTIONS		: return (std::string("OPTIONS"));
		case METHOD_HEAD		: return (std::string("HEAD"));
		case METHOD_LINK		: return (std::string("LINK"));
		case METHOD_MOVE		: return (std::string("MOVE"));
		case METHOD_PUT			: return (std::string("PUT"));
		case METHOD_PATCH		: return (std::string("PATCH"));
		case METHOD_TRACE		: return (std::string("TRACE"));
		case METHOD_UNLINK		: return (std::string("UNLINK"));
		case METHOD_WRAPPED		: return (std::string("WRAPPED"));
		default					: return (std::string("_NOMATCH_"));
	}
}

void			RequestParser::print_request_info(void)
{
	std::cout << "request info:" << std::endl;
	std::cout << "    method          : " << this->get_method_name() << std::endl;
	std::cout << "    path            : " << "[" << this->_resource << "]" << std::endl;
	std::cout << "    http_version    : " << this->_http_version << std::endl;
	std::cout << "    body            : " << "NOT IMPLEMENTED YET (sorry bb)" << std::endl;
	std::cout << "    headers         : " << std::endl;
	for (headers_iterator it = this->_header_fields.begin();
		it != this->_header_fields.end(); it++)
	{
		std::cout << "        [" << it->first << "] -> [" << it->second << "]" << std::endl;
	}

}

int				RequestParser::eat(std::string to_eat)
{
	std::cout << "[ " << __FUNCTION__ << " string ] ";
	if (this->_request_raw.compare(this->_head, to_eat.length(), to_eat) == 0)
	{
		std::cout << "eatten: \'" << to_eat << "\'" << std::endl;
		this->_head += to_eat.length();
		return (SUCCESS);
	}
	else
	{
		std::cout << "\'" << to_eat << "\' not found !" << std::endl;
		return (FAILURE);
	}
}

int				RequestParser::eat_no_casesensitive(std::string to_eat)
{
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ] --- head on: [" << SSTRABS(this->_request_raw[this->_head]) << STRABS(this->_request_raw[this->_head]) << "] (" << this->_head << ") ";
	std::string tmp;
	try
	{
		// printf("[ "C_G_RED"DEBUG"C_RES" ] %lu - %lu < %lu\n", this->_request_raw.length(), this->_head, to_eat.length());
		if (this->_request_raw.length() - this->_head < to_eat.length())
		{
			std::cout << "\'" << to_eat << "\' not found !" << std::endl;
			return (FAILURE);
		}
		tmp = stolo(this->_request_raw.substr(this->_head, to_eat.length()));
	}
	catch (std::exception & e)
	{
		std::cout << "error: " << e.what() << std::endl;
	}
	if (this->_request_raw.compare(this->_head, tmp.length(), tmp) == 0)
	{
		std::cout << "eatten: \'" << to_eat << "\'" << std::endl;
		this->_head += to_eat.length();
		return (SUCCESS);
	}
	else
	{
		std::cout << "\'" << to_eat << "\' not found !" << std::endl;
		return (FAILURE);
	}
}

int				RequestParser::eat(int to_eat)
{
	// std::cout << "[ " << __FUNCTION__ << " char ] ";
	if (this->_request_raw[this->_head] == to_eat)
	{
		// std::cout << "eatten: \'" << static_cast<char>(to_eat) << "\'" << std::endl;
		this->_head++;
		return (SUCCESS);
	}
	else
	{
		// std::cout << "\'" << static_cast<char>(to_eat) << "\' not found !" << std::endl;
		return (FAILURE);
	}
}

int				RequestParser::eatall(void)
{
	debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	this->_head = this->_request_raw.find(PAT_CRLF""PAT_CRLF, this->_head, 4);
	// this->_head = this->_request_raw.length() - 1;
	return (SUCCESS);
}

std::string		RequestParser::digest(void)
{
	debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	std::string ret;
	try
	{
		ret = this->_request_raw.substr(this->_head_last_digest, this->_head - this->_head_last_digest);
	}
	catch (std::exception & e)
	{
		std::cout << "error: " << e.what() << std::endl;
	}
	this->_head_last_digest = this->_head;
	return (ret);
}

// DOT					: '.'
// 						;
int		RequestParser::DOT(void)
{
	debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	if (eat(PAT_DOT) == FAILURE)
		throw (RequestParser::EattingBadPatternException(0, std::string(__FUNCTION__)));
	return (SUCCESS);
}

// SLASH				: '/'
// 						;
int		RequestParser::SLASH(void)
{
	debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	if (eat(PAT_SLASH) == FAILURE)
		throw (RequestParser::EattingBadPatternException(0, std::string(__FUNCTION__)));
	return (SUCCESS);
}

// SP					: ' '
// 						;
int		RequestParser::SP(void)
{
	debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	if (eat(PAT_SP) == FAILURE)
		throw (RequestParser::EattingBadPatternException(0, std::string(__FUNCTION__)));
	return (SUCCESS);
}

// HTAB					: '\t'
// 						;
int		RequestParser::HTAB(void)
{
	debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	if (eat(PAT_HTAB) == FAILURE)
		throw (RequestParser::EattingBadPatternException(0, std::string(__FUNCTION__)));
	return (SUCCESS);
}
// CR					: '\r'
// 						;
int		RequestParser::CR(void)
{
	debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	if (eat(PAT_CR) == FAILURE)
		throw (RequestParser::EattingBadPatternException(0, std::string(__FUNCTION__)));
	return (SUCCESS);
}
// LF					: '\n'
// 						;
int		RequestParser::LF(void)
{
	debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	if (eat(PAT_LF) == FAILURE)
		throw (RequestParser::EattingBadPatternException(0, std::string(__FUNCTION__)));
	return (SUCCESS);
}

// DDOT					: ':'
// 						;
int		RequestParser::DDOT(void)
{
	debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	if (eat(PAT_DDOT) == FAILURE)
		throw (RequestParser::EattingBadPatternException(0, std::string(__FUNCTION__)));
	return (SUCCESS);
}

// HYPHEN				: '-'
// 						;
int		RequestParser::HYPHEN(void)
{
	debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	if (eat(PAT_HYPHEN) == FAILURE)
		throw (RequestParser::EattingBadPatternException(0, std::string(__FUNCTION__)));
	return (SUCCESS);
}

// CRLF					: CR LF
// 						;
int		RequestParser::CRLF(void)
{
	debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	CR();
	LF();
	return (SUCCESS);
}

int		RequestParser::ALPHA(void)
{
	debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	for (int i = 'a'; i <= 'z'; i++)
	{
		if (eat(i) == SUCCESS)
			return (SUCCESS);
	}
	for (int i = 'A'; i <= 'Z'; i++)
	{
		if (eat(i) == SUCCESS)
			return (SUCCESS);
	}
	throw (RequestParser::EattingBadPatternException(0, std::string(__FUNCTION__)));

	debug();
 std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;	return (FAILURE);
}

int		RequestParser::DIGIT(void)
{
	debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	for (int i = '0'; i <= '9'; i++)
	{
		if (eat(i) == SUCCESS)
			return (SUCCESS);
	}
	throw (RequestParser::EattingBadPatternException(0, std::string(__FUNCTION__)));

	debug();
 std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;	return (FAILURE);
}

// ALPHA_DIGIT_HYPHEN		: ALPHA
// 							| DIGIT
// 							| HYPHEN
// 							;

int		RequestParser::ALPHA_DIGIT_HYPHEN(void)
{
	debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	try { ALPHA(); }
	catch (std::exception &) {
		try { DIGIT(); }
		catch (std::exception &) {
			try { HYPHEN(); }
			catch (std::exception &) {
				return (FAILURE);
			}
		}
	}
	return (SUCCESS);
}

// group_ALPHA_DIGIT_HYPHEN	:
// 							| ALPHA_DIGIT_HYPHEN
// 							;

int		RequestParser::group_ALPHA_DIGIT_HYPHEN(void)
{
	debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	try {
		if (ALPHA_DIGIT_HYPHEN() == SUCCESS)
			group_ALPHA_DIGIT_HYPHEN();
	}
	catch (std::exception &) {
		return (SUCCESS);
	}
	return (SUCCESS);
}

// TEXT /[a-zA-z][a-zA-Z0-9-]{0,252}[a-zA-Z0-9]/

int		RequestParser::TEXT(void)
{
	debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	ALPHA();
	try { group_ALPHA_DIGIT_HYPHEN(); }
	catch (std::exception &) { return (SUCCESS); }
	try { ALPHA(); }
	catch (std::exception &) {
		try { DIGIT(); }
		catch (std::exception &) { return (FAILURE); }
	}
	return (SUCCESS);
}

// OWS					:
// 						| SP OWS
// 						| HTAB OWS
// 						;

int		RequestParser::OWS(void)
{
	debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	try {
		if (SP() == SUCCESS)
			OWS();
	}
	catch (std::exception &) {
		try {
			if (HTAB() == SUCCESS)
				OWS();
		}
		catch (std::exception &) {
			return (SUCCESS);
		}
	}
	return (SUCCESS);
}

int		RequestParser::ASCII_PRINTABLE(void)
{
	debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	for (int i = 32; i <= 126; i++)
	{
		if (eat(i) == SUCCESS)
			return (SUCCESS);
	}
	throw (RequestParser::EattingBadPatternException(0, std::string(__FUNCTION__)));

	debug();
 std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;	return (FAILURE);
}

int		RequestParser::ANYTEXT(void)
{
	debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	ASCII_PRINTABLE();
	try {
		if (ASCII_PRINTABLE() == SUCCESS)
			ANYTEXT();
	}
	catch (std::exception &) {
		return (SUCCESS);
	}
	return (SUCCESS);
}

int		RequestParser::unimplemented_headfield_data(void)
{
	debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	std::string key(digest());
	DDOT();
	OWS();
	digest();
	ANYTEXT();
	std::map<std::string, std::string>::iterator it = this->_header_fields.begin();
	this->_header_fields.insert (it, std::pair<std::string, std::string>(key, digest()));
	OWS();
	return (SUCCESS);
}

int		RequestParser::implemented_headfield_data(void)
{
	debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	std::string key(digest());
	DDOT();
	OWS();
	digest();
	TEXT();
	std::map<std::string, std::string>::iterator it = this->_header_fields.begin();
	this->_header_fields.insert (it, std::pair<std::string, std::string>(key, digest()));
	OWS();
	return (SUCCESS);
}

// host					: "Host" DDOT OWS TEXT OWS

int		RequestParser::host(void)
{
	debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	if (eat_no_casesensitive("Host") == FAILURE)
		throw (RequestParser::EattingBadPatternException(0, std::string(__FUNCTION__)));

	implemented_headfield_data();
	return (SUCCESS);
}

// accept_Charset			: "Accept-Charset" DDOT OWS ANYTEXT OWS

int		RequestParser::accept_Charset(void)
{
	debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	if (eat_no_casesensitive("Accept-Charset") == FAILURE)
		throw (RequestParser::EattingBadPatternException(0, std::string(__FUNCTION__)));

	unimplemented_headfield_data();
	return (SUCCESS);
}

// accept_Encoding			: "Accept-Encoding" DDOT OWS ANYTEXT OWS

int		RequestParser::accept_Encoding(void)
{
	debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	if (eat_no_casesensitive("Accept-Encoding") == FAILURE)
		throw (RequestParser::EattingBadPatternException(0, std::string(__FUNCTION__)));

	unimplemented_headfield_data();
	return (SUCCESS);
}

// accept_Language			: "Accept-Language" DDOT OWS ANYTEXT OWS

int		RequestParser::accept_Language(void)
{
	debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	if (eat_no_casesensitive("Accept-Language") == FAILURE)
		throw (RequestParser::EattingBadPatternException(0, std::string(__FUNCTION__)));

	unimplemented_headfield_data();
	return (SUCCESS);
}

// authorization			: "Authorization" DDOT OWS ANYTEXT OWS

int		RequestParser::authorization(void)
{
	debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	if (eat_no_casesensitive("Authorization") == FAILURE)
		throw (RequestParser::EattingBadPatternException(0, std::string(__FUNCTION__)));

	unimplemented_headfield_data();
	return (SUCCESS);
}

// from					: "From" DDOT OWS ANYTEXT OWS

int		RequestParser::from(void)
{
	debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	if (eat_no_casesensitive("From") == FAILURE)
		throw (RequestParser::EattingBadPatternException(0, std::string(__FUNCTION__)));

	unimplemented_headfield_data();
	return (SUCCESS);
}

// accept					: "Accept" DDOT OWS ANYTEXT OWS

int		RequestParser::accept(void)
{
	debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	if (eat_no_casesensitive("Accept") == FAILURE)
		throw (RequestParser::EattingBadPatternException(0, std::string(__FUNCTION__)));

	unimplemented_headfield_data();
	return (SUCCESS);
}

// if_Modified_Since		: "If-Modified-Since" DDOT OWS ANYTEXT OWS

int		RequestParser::if_Modified_Since(void)
{
	debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	if (eat_no_casesensitive("If-Modified-Since") == FAILURE)
		throw (RequestParser::EattingBadPatternException(0, std::string(__FUNCTION__)));

	unimplemented_headfield_data();
	return (SUCCESS);
}

// proxy_Authorization		: "Proxy-Authorization" DDOT OWS ANYTEXT OWS

int		RequestParser::proxy_Authorization(void)
{
	debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	if (eat_no_casesensitive("Proxy-Authorization") == FAILURE)
		throw (RequestParser::EattingBadPatternException(0, std::string(__FUNCTION__)));

	unimplemented_headfield_data();
	return (SUCCESS);
}

// range					: "Range" DDOT OWS ANYTEXT OWS

int		RequestParser::range(void)
{
	debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	if (eat_no_casesensitive("Range") == FAILURE)
		throw (RequestParser::EattingBadPatternException(0, std::string(__FUNCTION__)));

	unimplemented_headfield_data();
	return (SUCCESS);
}

// referer					: "Referer" DDOT OWS ANYTEXT OWS

int		RequestParser::referer(void)
{
	debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	if (eat_no_casesensitive("Referer") == FAILURE)
		throw (RequestParser::EattingBadPatternException(0, std::string(__FUNCTION__)));

	unimplemented_headfield_data();
	return (SUCCESS);
}

// unless					: "Unless" DDOT OWS ANYTEXT OWS

int		RequestParser::unless(void)
{
	debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	if (eat_no_casesensitive("Unless") == FAILURE)
		throw (RequestParser::EattingBadPatternException(0, std::string(__FUNCTION__)));

	unimplemented_headfield_data();
	return (SUCCESS);
}

// user_Agent				: "User-Agent" DDOT OWS ANYTEXT OWS

int		RequestParser::user_Agent(void)
{
	debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	if (eat_no_casesensitive("User-Agent") == FAILURE)
		throw (RequestParser::EattingBadPatternException(0, std::string(__FUNCTION__)));

	unimplemented_headfield_data();
	return (SUCCESS);
}


// unimplemented_headfield	: accept_Charset
// 							| accept_Encoding
// 							| accept_Language
// 							| authorization
// 							| from
// 							| accept
// 							| if_Modified_Since
// 							| proxy_Authorization
// 							| range
// 							| referer
// 							| unless
// 							| user_Agent
// 							;

int		RequestParser::unimplemented_headfield(void)
{
	debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	try { accept_Charset(); }
	catch (std::exception &) {
		try { accept_Encoding(); }
		catch (std::exception &) {
			try { accept_Language(); }
			catch (std::exception &) {
				try { authorization(); }
				catch (std::exception &) {
					try { from(); }
					catch (std::exception &) {
						try { accept(); }
						catch (std::exception &) {
							try { if_Modified_Since(); }
							catch (std::exception &) {
								try { proxy_Authorization(); }
								catch (std::exception &) {
									try { range(); }
									catch (std::exception &) {
										try { referer(); }
										catch (std::exception &) {
											try { unless(); }
											catch (std::exception &) {
												user_Agent();
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return (SUCCESS);
}

// implemented_headfield	: host
// 							;

int		RequestParser::implemented_headfield(void)
{
	debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	host();
	return (SUCCESS);
}

// headfield				: implemented_headfield
// 							| unimplemented_headfield
// 							;

int		RequestParser::headfield(void)
{
	debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	try { implemented_headfield(); }
	catch (std::exception &) {
		unimplemented_headfield();
	}
	return (SUCCESS);
}

// group_headfield			:
// 							| headfield CRLF group_headfield
// 							;

int		RequestParser::group_headfield(void)
{
	debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	try {
		if (headfield() == SUCCESS)
			CRLF(), group_headfield();
	}
	catch (std::exception &) { return (SUCCESS); }
	return (SUCCESS);
}


// group_content		:
// 						| CONTENT
// 						;

int		RequestParser::group_content(void)
{
	debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	eatall();
	return (SUCCESS);
}

// method				: "GET"
// 						| "POST"
// 						| "DELETE"
// 						;

int		RequestParser::method(void)
{
	debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	if (eat("GET") == SUCCESS)
	{
		this->_method = METHOD_GET;
		return (SUCCESS);
	}
	if (eat("POST") == SUCCESS)
	{
		this->_method = METHOD_POST;
		return (SUCCESS);
	}
	if (eat("DELETE") == SUCCESS)
	{
		this->_method = METHOD_DELETE;
		return (SUCCESS);
	}
	throw (RequestParser::EattingBadPatternException(0, std::string(__FUNCTION__)));

	debug();
 std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;	return (FAILURE);
}

// request_target		: '/' ANYTEXT
// 						;

int		RequestParser::request_target(void)
{
	debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	SLASH();
	try { TEXT(); }
	catch (std::exception) {}
	return (SUCCESS);
}

// HTTP_version			: "HTTP/" DIGIT '.' DIGIT
// 						;

int		RequestParser::HTTP_version(void)
{
	debug();
	digest();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	if (eat("HTTP/") == FAILURE)
		throw (RequestParser::EattingBadPatternException(0, std::string(__FUNCTION__)));


	DIGIT();
	DOT();
	DIGIT();
	this->_http_version = digest();
	std::cout << "this->_http_version: [" << this->_http_version << "]" << std::endl;
	return (SUCCESS);
}

// line_request			: method SP request_target SP HTTP_version
// 						;

int		RequestParser::line_request(void)
{
	debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	method();
	SP();
	OWS();
	digest();
	request_target();
	this->_resource = digest();
	std::cout << "this->_resource: [" << this->_resource << "]" << std::endl;
	SP();
	OWS();
	HTTP_version();
	OWS();
	return (SUCCESS);
}

// full_request					: line_request CRLF group_headfield CRLF group_content
// 								;

int		RequestParser::full_request(void)
{
	debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	line_request();
	CRLF();
	group_headfield();
	// CRLF();
	// digest();
	// group_content();
	// this->_body = digest();
	return (SUCCESS);
}

// request						: full_request CRLF
// 								;

int		RequestParser::request(void)
{
	debug();
	std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	try
	{
		full_request();
		CRLF();
	}
	catch (std::exception & e)
	{
		// std::cout << "error: " << e.what() << std::endl;
		std::cout << "error: RequestParser: " << e.what() << std::endl;
	}
	return (SUCCESS);
}

/* ************************************************************************** */
/* ************************************************************************** */

// PUBLIC MEMBERS FUNCTION : PUMF

/* ************************************************************************** */
/* ************************************************************************** */
