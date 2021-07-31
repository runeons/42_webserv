/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestParser.lexer.class.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 19:36:15 by tharchen          #+#    #+#             */
/*   Updated: 2021/07/24 23:36:13 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>

//// lexer

// test one char

// static std::string	convchar(int c)
// {
// 	std::string r("~");
// 	if (c == '\r')
// 		return (std::string("\\r"));
// 	if (c == '\n')
// 		return (std::string("\\n"));
// 	if (c == '\t')
// 		return (std::string("\\t"));
// 	r[0] = c;
// 	return (r);
// }

void	RequestParser::CHAR(char c)
{
	if (eat(c) == FAILURE)
	{
		bc_s();
		throw (LexerException("CHAR expected"));
	}
}

// CR = 0x0D
void	RequestParser::CR(void)
{
	if (eat(0x0D) == FAILURE)
	{
		bc_s();
		throw (LexerException("CR expected"));
	}
}

// LF = 0x0A
void	RequestParser::LF(void)
{
	if (eat(0x0A) == FAILURE)
	{
		bc_s();
		throw (LexerException("LF expected"));
	}
}

// SP = 0x20
void	RequestParser::SP(void)
{
	if (eat(0x20) == FAILURE)
	{
		bc_s();
		throw (LexerException("SP expected"));
	}
}

// HTAB = 0x09
void	RequestParser::HTAB(void)
{
	if (eat(0x09) == FAILURE)
	{
		bc_s();
		throw (LexerException("HTAB expected"));
	}
}

///////

// RANGE = 0x30-39
void	RequestParser::RANGE(char start, char end)
{
	for (char i = start; i <= end; i++)
	{
		if (eat(i) == SUCCESS)
			return ;
	}
	bc_s(); throw (LexerException("RANGE expected"));
}


// ALPHA = 0x41-5A / 0x61-7A
void	RequestParser::ALPHA(void)
{
	for (char i = 0x41; i <= 0x5A; i++)
	{
		if (eat(i) == SUCCESS)
			return ;
	}
	for (char i = 0x61; i <= 0x7A; i++)
	{
		if (eat(i) == SUCCESS)
			return ;
	}
	bc_s(); throw (LexerException("ALPHA expected"));
}

// DIGIT = 0x30-39
void	RequestParser::DIGIT(void)
{
	for (char i = 0x30; i <= 0x39; i++)
	{
		if (eat(i) == SUCCESS)
			return ;
	}
	bc_s(); throw (LexerException("DIGIT expected"));
}

// HEXDIG = DIGIT / "A" / "B" / "C" / "D" / "E" / "F"
void	RequestParser::HEXDIG(void)
{
	try { DIGIT(); } catch (std::exception &) {
		for (char i = 'A'; i <= 'F'; i++)
		{
			if (eat(i) == SUCCESS)
				return ;
		}
		bc_s(); throw (LexerException("HEXDIG expected"));
	}
}

// OCTET = 0x00-FF
void	RequestParser::OCTET(void)
{
	for (int i = 0x00; i <= 0xFF; i++)
	{
		if (eat(i) == SUCCESS)
			return ;
	}
	bc_s(); throw (LexerException("OCTET expected"));
}

// VCHAR = 0x21-7E
void	RequestParser::VCHAR(void)
{
	for (char i = 0x21; i <= 0x7E; i++)
	{
		if (eat(i) == SUCCESS)
			return ;
	}
	// std::cout << "[ FAIL VCHAR ] head: " << this->_head << " [" << static_cast<int>(this->_request_raw[this->_head]) << "]" << " \'" << convchar(this->_request_raw[this->_head]) << "\'" << std::endl;
	bc_s(); throw (LexerException("VCHAR expected"));
}

// VCHAR = 0x21-7E
void	RequestParser::field_char(void)
{
	for (char i = 0x21; i <= 0x7E; i++)
	{
		if (eat(i) == SUCCESS)
			return ;
	}
	if (eat('\t') == SUCCESS)
		return ;
	if (eat(' ') == SUCCESS)
		return ;
	// std::cout << "[ FAIL VCHAR ] head: " << this->_head << " [" << static_cast<int>(this->_request_raw[this->_head]) << "]" << " \'" << convchar(this->_request_raw[this->_head]) << "\'" << std::endl;
	bc_s(); throw (LexerException("VCHAR expected"));
}


// sub_delims = "!" / "$" / "&" / "'" / "(" / ")" / "*" / "+" / "," / ";" / "="

void	RequestParser::sub_delims(void)
{
	std::string	set("!$&\'()*+,;=");

	for (int i = 0; set[i]; i++)
	{
		if (eat(set[i]) == SUCCESS)
			return ;
	}
	bc_s(); throw (LexerException("sub_delims expected"));
}

// tchar = "!" / "#" / "$" / "%" / "&" / "\'" / "*" / "+" / "-" / "." / "^" / "_" / "\`" / "|" / "~" / DIGIT / ALPHA
void	RequestParser::tchar(void)
{
	std::string	set("!#$%&\'*+-.^_`|~");

	for (int i = 0; set[i]; i++)
	{
		if (eat(set[i]) == SUCCESS)
			return ;
	}
	try { DIGIT(); }
	catch (std::exception &) {
		try { ALPHA(); }
		catch (std::exception &) {
			bc_s(); throw (LexerException("tchar expected"));
		}
	}
}

// obs_text = 0x80-FF
void	RequestParser::obs_text(void)
{
	for (int i = 0x80; i <= 0xFF; i++)
	{
		if (eat(i) == SUCCESS)
			return ;
	}
	bc_s(); throw (LexerException("obs_text expected"));
}
