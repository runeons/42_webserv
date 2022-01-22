
#include <webserv.hpp>

//// lexer

void	RequestParser::CHAR(char c)
{
	if (eat(c) == FAILURE)
	{
		throw (Exceptions::LexerException("CHAR expected"));
	}
}

// CR = 0x0D
void	RequestParser::CR(void)
{
	if (eat(0x0D) == FAILURE)
	{
		throw (Exceptions::LexerException("CR expected"));
	}
}

// LF = 0x0A
void	RequestParser::LF(void)
{
	if (eat(0x0A) == FAILURE)
	{
		throw (Exceptions::LexerException("LF expected"));
	}
}

// SP = 0x20
void	RequestParser::SP(void)
{
	if (eat(0x20) == FAILURE)
	{
		throw (Exceptions::LexerException("SP expected"));
	}
}

// HTAB = 0x09
void	RequestParser::HTAB(void)
{
	if (eat(0x09) == FAILURE)
	{
		throw (Exceptions::LexerException("HTAB expected"));
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
	throw (Exceptions::LexerException("RANGE expected"));
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
	throw (Exceptions::LexerException("ALPHA expected"));
}

// DIGIT = 0x30-39
void	RequestParser::DIGIT(void)
{
	for (char i = 0x30; i <= 0x39; i++)
	{
		if (eat(i) == SUCCESS)
			return ;
	}
	throw (Exceptions::LexerException("DIGIT expected"));
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
		throw (Exceptions::LexerException("HEXDIG expected"));
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
	throw (Exceptions::LexerException("OCTET expected"));
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
	throw (Exceptions::LexerException("VCHAR expected"));
}

// field_char = 0x21-7E
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
	throw (Exceptions::LexerException("VCHAR expected"));
}

// obs_text = 0x80-FF
void	RequestParser::obs_text(void)
{START_FUN;
	for (int i = 0x80; i <= 0xFF; i++)
	{
		if (eat(i) == SUCCESS)
		{
			END_FUN(SUCCESS);
			return ;
		}
	}
	throw (Exceptions::LexerException("obs_text expected"));
	END_FUN(FAILURE);
}
