
#include <webserv.hpp>

// server_token			= 's' 'e' 'r' 'v' 'e' 'r' ; "server"
void	ConfigParser::server_token(void)
{
	SAVE_HEAD(0);
	try
	{
		CHAR('s');
		CHAR('e');
		CHAR('r');
		CHAR('v');
		CHAR('e');
		CHAR('r');
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		throw (Exceptions::ParserException("server_token expected"));
	}
}

// return_token			= 'r' 'e' 't' 'u' 'r' 'n' ; "return"
void	ConfigParser::return_token(void)
{
	SAVE_HEAD(0);
	try
	{
		CHAR('r');
		CHAR('e');
		CHAR('t');
		CHAR('u');
		CHAR('r');
		CHAR('n');
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		throw (Exceptions::ParserException("return_token expected"));
	}
}

// token_301			= '3' '0' '1' ; "301"
void	ConfigParser::token_301(void)
{
	SAVE_HEAD(0);
	try
	{
		CHAR('3');
		CHAR('0');
		CHAR('1');
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		throw (Exceptions::ParserException("token_301 expected"));
	}
}

// host_token				= 'h' 'o' 's' 't' ; "host"
void	ConfigParser::host_token(void)
{
	SAVE_HEAD(0);
	try
	{
		CHAR('h');
		CHAR('o');
		CHAR('s');
		CHAR('t');
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		throw (Exceptions::ParserException("host_token expected"));
	}
}

// port_token				= 'p' 'o' 'r' 't' ; "port"
void	ConfigParser::port_token(void)
{
	SAVE_HEAD(0);
	try
	{
		CHAR('p');
		CHAR('o');
		CHAR('r');
		CHAR('t');
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		throw (Exceptions::ParserException("port_token expected"));
	}
}

// server_name_token		= 's' 'e' 'r' 'v' 'e' 'r' '_' 'n' 'a' 'm' 'e' ; "server_name"
void	ConfigParser::server_name_token(void)
{
	SAVE_HEAD(0);
	try
	{
		CHAR('s');
		CHAR('e');
		CHAR('r');
		CHAR('v');
		CHAR('e');
		CHAR('r');
		CHAR('_');
		CHAR('n');
		CHAR('a');
		CHAR('m');
		CHAR('e');
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		throw (Exceptions::ParserException("server_name_token expected"));
	}
}

// max_client_body_token	= 'm' 'a' 'x' '_' 'c' 'l' 'i' 'e' 'n' 't' '_' 'b' 'o' 'd' 'y' ; "max_client_body"
void	ConfigParser::max_client_body_token(void)
{
	SAVE_HEAD(0);
	try
	{
		CHAR('m');
		CHAR('a');
		CHAR('x');
		CHAR('_');
		CHAR('c');
		CHAR('l');
		CHAR('i');
		CHAR('e');
		CHAR('n');
		CHAR('t');
		CHAR('_');
		CHAR('b');
		CHAR('o');
		CHAR('d');
		CHAR('y');
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		throw (Exceptions::ParserException("max_client_body_token expected"));
	}
}

// root_token				= 'r' 'o' 'o' 't' ; "root"
void	ConfigParser::root_token(void)
{
	SAVE_HEAD(0);
	try
	{
		CHAR('r');
		CHAR('o');
		CHAR('o');
		CHAR('t');
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		throw (Exceptions::ParserException("root_token expected"));
	}
}

// error_token				= 'e' 'r' 'r' 'o' 'r' ; "error"
void	ConfigParser::error_token(void)
{
	SAVE_HEAD(0);
	try
	{
		CHAR('e');
		CHAR('r');
		CHAR('r');
		CHAR('o');
		CHAR('r');
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		throw (Exceptions::ParserException("error_token expected"));
	}
}

// location_token			= 'l' 'o' 'c' 'a' 't' 'i' 'o' 'n' ; "location"
void	ConfigParser::location_token(void)
{
	SAVE_HEAD(0);
	try
	{
		CHAR('l');
		CHAR('o');
		CHAR('c');
		CHAR('a');
		CHAR('t');
		CHAR('i');
		CHAR('o');
		CHAR('n');
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		throw (Exceptions::ParserException("location_token expected"));
	}
}

// uri_token				= 'u' 'r' 'i' ; "uri"
void	ConfigParser::uri_token(void)
{
	SAVE_HEAD(0);
	try
	{
		CHAR('u');
		CHAR('r');
		CHAR('i');
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		throw (Exceptions::ParserException("uri_token expected"));
	}
}

// index_token				= 'i' 'n' 'd' 'e' 'x' ; "index"
void	ConfigParser::index_token(void)
{
	SAVE_HEAD(0);
	try
	{
		CHAR('i');
		CHAR('n');
		CHAR('d');
		CHAR('e');
		CHAR('x');
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		throw (Exceptions::ParserException("index_token expected"));
	}
}

// autoindex_token			= 'a' 'u' 't' 'o' 'i' 'n' 'd' 'e' 'x' ; "autoindex"
void	ConfigParser::autoindex_token(void)
{
	SAVE_HEAD(0);
	try
	{
		CHAR('a');
		CHAR('u');
		CHAR('t');
		CHAR('o');
		CHAR('i');
		CHAR('n');
		CHAR('d');
		CHAR('e');
		CHAR('x');
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		throw (Exceptions::ParserException("autoindex_token expected"));
	}
}

// alias_token				= 'a' 'l' 'i' 'a' 's' ; "alias"
void	ConfigParser::alias_token(void)
{
	SAVE_HEAD(0);
	try
	{
		CHAR('a');
		CHAR('l');
		CHAR('i');
		CHAR('a');
		CHAR('s');
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		throw (Exceptions::ParserException("alias_token expected"));
	}
}

// method_token			= 'm' 'e' 't' 'h' 'o' 'd' ; "method"
void	ConfigParser::method_token(void)
{
	SAVE_HEAD(0);
	try
	{
		CHAR('m');
		CHAR('e');
		CHAR('t');
		CHAR('h');
		CHAR('o');
		CHAR('d');
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		throw (Exceptions::ParserException("method_token expected"));
	}
}

// upload_token			= 'u' 'p' 'l' 'o' 'a' 'd' ; "upload"
void	ConfigParser::upload_token(void)
{
	SAVE_HEAD(0);
	try
	{
		CHAR('u');
		CHAR('p');
		CHAR('l');
		CHAR('o');
		CHAR('a');
		CHAR('d');
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		throw (Exceptions::ParserException("upload_token expected"));
	}
}

// on_token				= 'o' 'n' ; "on"
void	ConfigParser::on_token(void)
{
	SAVE_HEAD(0);
	try
	{
		CHAR('o');
		CHAR('n');
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		throw (Exceptions::ParserException("on_token expected"));
	}
}

// off_token				= 'o' 'f' 'f' ; "off"
void	ConfigParser::off_token(void)
{
	SAVE_HEAD(0);
	try
	{
		CHAR('o');
		CHAR('f');
		CHAR('f');
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		throw (Exceptions::ParserException("off_token expected"));
	}
}
