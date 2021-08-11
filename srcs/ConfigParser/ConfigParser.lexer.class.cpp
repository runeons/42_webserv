
#include <webserv.hpp>

// ALPHA					= 0x41-5A / 0x61-7A
void		ConfigParser::ALPHA(void)
{
	for (int i = 'a'; i <= 'z'; i++)
	{
		if (eat(i) == SUCCESS)
			return ;
	}
	for (int i = 'A'; i <= 'Z'; i++)
	{
		if (eat(i) == SUCCESS)
			return ;
	}
	/*bc_s();*/ throw (Exceptions::LexerException("ALPHA expected"));
}

// ALPHA_UPPER				= 0x41-5A
void		ConfigParser::ALPHA_UPPER(void)
{
	for (int i = 'A'; i <= 'Z'; i++)
	{
		if (eat(i) == SUCCESS)
			return ;
	}
	/*bc_s();*/ throw (Exceptions::LexerException("ALPHA_UPPER expected"));
}

// DIGIT					= 0x30-39
void		ConfigParser::DIGIT(void)
{
	for (char i = '0'; i <= '9'; i++)
	{
		if (eat(i) == SUCCESS)
			return ;
	}
	/*bc_s();*/ throw (Exceptions::LexerException("DIGIT expected"));
}

// TDIGIT					= 0x31-39
void		ConfigParser::TDIGIT(void)
{
	for (char i = '1'; i <= '9'; i++)
	{
		if (eat(i) == SUCCESS)
			return ;
	}
	/*bc_s();*/ throw (Exceptions::LexerException("TDIGIT expected"));
}

// LF						= 0x0A
void		ConfigParser::LF(void)
{
	if (eat(0x0A) == FAILURE)
	{
		/*bc_s();*/
		throw (Exceptions::LexerException("LF expected"));
	}
}

// SP						= 0x20
void		ConfigParser::SP(void)
{
	if (eat(0x20) == FAILURE)
	{
		/*bc_s();*/
		throw (Exceptions::LexerException("SP expected"));
	}
}

// HTAB					= 0x09
void		ConfigParser::HTAB(void)
{
	if (eat(0x09) == FAILURE)
	{
		/*bc_s();*/
		throw (Exceptions::LexerException("HTAB expected"));
	}
}

// CHAR					= 0x09
void		ConfigParser::CHAR(int c)
{
	if (eat(c) == FAILURE)
	{
		/*bc_s();*/
		throw (Exceptions::LexerException("CHAR expected"));
	}
}

// RANGE					= 0x09
void		ConfigParser::RANGE(int start, int end)
{
	for (char i = start; i <= end; i++)
	{
		if (eat(i) == SUCCESS)
			return ;
	}
	/*bc_s();*/ throw (Exceptions::LexerException("RANGE expected"));
}
