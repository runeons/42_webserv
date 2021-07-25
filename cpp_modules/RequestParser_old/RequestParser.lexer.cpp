/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestParser.lexer.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 17:56:06 by tharchen          #+#    #+#             */
/*   Updated: 2021/07/22 21:38:14 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>

// DOT					: '.'
// 						;
int		RequestParser::DOT(void)
{
	// debug();
	// std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	if (eat(PAT_DOT) == FAILURE)
	{
		char *tmp;
		asprintf(&tmp, "%s expected at %lu", PAT_DOT, this->_head);
		throw (RequestParser::EattingBadPatternException(0, std::string(tmp)));
	}
	return (SUCCESS);
}

// SLASH				: '/'
// 						;
int		RequestParser::SLASH(void)
{
	// debug();
	// std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	if (eat(PAT_SLASH) == FAILURE)
	{
		char *tmp;
		asprintf(&tmp, "%s expected at %lu", PAT_SLASH, this->_head);
		throw (RequestParser::EattingBadPatternException(0, std::string(tmp)));
	}
	return (SUCCESS);
}

// SP					: ' '
// 						;
int		RequestParser::SP(void)
{
	// debug();
	// std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	if (eat(PAT_SP) == FAILURE)
	{
		char *tmp;
		asprintf(&tmp, "%s expected at %lu", PAT_SP, this->_head);
		throw (RequestParser::EattingBadPatternException(0, std::string(tmp)));
	}
	return (SUCCESS);
}

// HTAB					: '\t'
// 						;
int		RequestParser::HTAB(void)
{
	// debug();
	// std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	if (eat(PAT_HTAB) == FAILURE)
	{
		char *tmp;
		asprintf(&tmp, "%s expected at %lu", PAT_HTAB, this->_head);
		throw (RequestParser::EattingBadPatternException(0, std::string(tmp)));
	}
	return (SUCCESS);
}
// CR					: '\r'
// 						;
int		RequestParser::CR(void)
{
	// debug();
	// std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	if (eat(PAT_CR) == FAILURE)
	{
		char *tmp;
		asprintf(&tmp, "%s expected at %lu", PAT_CR, this->_head);
		throw (RequestParser::EattingBadPatternException(0, std::string(tmp)));
	}
	return (SUCCESS);
}
// LF					: '\n'
// 						;
int		RequestParser::LF(void)
{
	// debug();
	// std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	if (eat(PAT_LF) == FAILURE)
	{
		char *tmp;
		asprintf(&tmp, "%s expected at %lu", PAT_LF, this->_head);
		throw (RequestParser::EattingBadPatternException(0, std::string(tmp)));
	}
	return (SUCCESS);
}

// DDOT					: ':'
// 						;
int		RequestParser::DDOT(void)
{
	// debug();
	// std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	if (eat(PAT_DDOT) == FAILURE)
	{
		char *tmp;
		asprintf(&tmp, "%s expected at %lu", PAT_DDOT, this->_head);
		throw (RequestParser::EattingBadPatternException(0, std::string(tmp)));
	}
	return (SUCCESS);
}

// HYPHEN				: '-'
// 						;
int		RequestParser::HYPHEN(void)
{
	// debug();
	// std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	if (eat(PAT_HYPHEN) == FAILURE)
	{
		char *tmp;
		asprintf(&tmp, "%s expected at %lu", PAT_HYPHEN, this->_head);
		throw (RequestParser::EattingBadPatternException(0, std::string(tmp)));
	}
	return (SUCCESS);
}

// CRLF					: CR LF
// 						;
int		RequestParser::CRLF(void)
{
	// debug();
	// std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	CR();
	LF();
	return (SUCCESS);
}

int		RequestParser::ALPHA(void)
{
	// debug();
	// std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
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
	return (FAILURE);
}

int		RequestParser::DIGIT(void)
{
	// debug();
	// std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	for (int i = '0'; i <= '9'; i++)
	{
		if (eat(i) == SUCCESS)
			return (SUCCESS);
	}
	throw (RequestParser::EattingBadPatternException(0, std::string(__FUNCTION__)));
	return (FAILURE);
}

// ALPHA_DIGIT_HYPHEN		: ALPHA
// 							| DIGIT
// 							| HYPHEN
// 							;

int		RequestParser::ALPHA_DIGIT_HYPHEN(void)
{
	// debug();
	// std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
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
	// debug();
	// std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
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
	// debug();
	// std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
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
	// debug();
	// std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
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

int		RequestParser::VCHAR(void)
{
	// debug();
	// std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	for (int i = 0x21; i <= 0x7E; i++)
	{
		if (eat(i) == SUCCESS)
			return (SUCCESS);
	}
	throw (RequestParser::EattingBadPatternException(0, std::string(__FUNCTION__)));
	return (FAILURE);
}

int		RequestParser::ANYTEXT(void)
{
	// debug();
	// std::cout << "[ " << C_G_GREEN << __FUNCTION__ << C_RES << " ]" << std::endl;
	VCHAR();
	try {
		if (VCHAR() == SUCCESS)
			ANYTEXT();
	}
	catch (std::exception &) {
		return (SUCCESS);
	}
	return (SUCCESS);
}
