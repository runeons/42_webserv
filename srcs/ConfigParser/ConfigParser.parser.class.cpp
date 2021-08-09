/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.parser.class.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 15:25:32 by tharchen          #+#    #+#             */
/*   Updated: 2021/08/04 19:19:55 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>

int deep = 0;
std::string		g_tmp;

Config								tmp_server;
Location							tmp_location;
std::map<int, std::string>			tmp_error_pages;
std::map<std::string, Location>		tmp_map_locations;

// # define START_FUN deep++; dprintf(1, "%*s[ %s%s%s ] "C_G_CYAN"start"C_RES"", deep * 4, "", C_G_GRAY, __FUNCTION__, C_RES); print_center_line((int)strlen((char *)__FUNCTION__), (int)strlen("start"))
// # define DEBUG_MSG(X) dprintf(1, "%*s[ %s%s%s ] "C_G_WHITE"%s on \'%c\'"C_RES"\n", deep * 4, "", C_G_GRAY, __FUNCTION__, C_RES, X, _config_raw[_head])
// # define END_FUN(X) dprintf(1, "%*s[ %s%s%s ] %s", deep * 4, "", C_G_GRAY, __FUNCTION__, C_RES, X == FAILURE ? C_G_RED"FAILURE"C_RES : X == SUCCESS ? C_G_GREEN"SUCCESS"C_RES : "code "#X); print_center_line((int)strlen((char *)__FUNCTION__), (int)strlen(X == FAILURE ? "FAILURE" : X == SUCCESS ? "SUCCESS" : "code "#X)); deep--

# define START_FUN // deep++; dprintf(1, "%*s[ %s%s%s ] "C_G_CYAN"start"C_RES"", deep * 4, "", C_G_GRAY, __FUNCTION__, C_RES); print_center_line((int)strlen((char *)__FUNCTION__), (int)strlen("start"))
# define DEBUG_MSG(X) // dprintf(1, "%*s[ %s%s%s ] "C_G_WHITE"%s on \'%c\'"C_RES"\n", deep * 4, "", C_G_GRAY, __FUNCTION__, C_RES, X, _config_raw[_head])
# define END_FUN(X) // dprintf(1, "%*s[ %s%s%s ] %s", deep * 4, "", C_G_GRAY, __FUNCTION__, C_RES, X == FAILURE ? C_G_RED"FAILURE"C_RES : X == SUCCESS ? C_G_GREEN"SUCCESS"C_RES : "code "#X); print_center_line((int)strlen((char *)__FUNCTION__), (int)strlen(X == FAILURE ? "FAILURE" : X == SUCCESS ? "SUCCESS" : "code "#X)); deep--

int	ft_atoi(std::string s)
{
	int ret;

	std::stringstream ss(s);
	ss >> ret;
	return (ret);
}

// OWS						= *( SP / HTAB )
void	ConfigParser::OWS(void)
{START_FUN;
	while (1)
	{
		try { SP(); }
		catch (std::exception & e) {
			try { HTAB(); }
			catch (std::exception & e) { break ; }
		}
	}
	END_FUN(SUCCESS);
}

// OWSON					= *( SP / HTAB / LF )
void	ConfigParser::OWSON(void)
{START_FUN;
	while (1)
	{
		try { SP(); }
		catch (std::exception & e) {
			try { HTAB(); }
			catch (std::exception & e) {
				try { LF(); }
				catch (std::exception & e) { break ; }
			}
		}
	}
	END_FUN(SUCCESS);
}

// token					= 1*( ALPHA_UPPER )
void	ConfigParser::token(void)
{START_FUN;
	ALPHA_UPPER();
	while (1)
	{
		try { ALPHA_UPPER(); }
		catch (std::exception & e) { break ; }
	}
	END_FUN(SUCCESS);
}

// dec_octet   			= DIGIT                 ; 0-9
// 						/ 0x31-39 DIGIT         ; 10-99   ; 1-9 0-9
// 						/ '1' 2DIGIT            ; 100-199 ; "1" 0-9 0-9
// 						/ '2' 0x30-34 DIGIT     ; 200-249 ; "2" 0-4 0-9
// 						/ '2' '5' 0x30-35       ; 250-255 ; "25" 0-5
void	ConfigParser::dec_octet(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		// std::cout << "dec_octet try " << __LINE__ << std::endl;
		CHAR('2');
		CHAR('5');
		RANGE(0x30, 0x35);
		END_FUN(SUCCESS); return ;
	}
	catch (std::exception & e) { LOAD_HEAD(0); }
	try
	{
		// std::cout << "dec_octet try " << __LINE__ << std::endl;
		CHAR('2');
		RANGE(0x30, 0x34);
		DIGIT();
		END_FUN(SUCCESS); return ;
	}
	catch (std::exception & e) { LOAD_HEAD(0); }
	try
	{
		// std::cout << "dec_octet try " << __LINE__ << std::endl;
		CHAR('1');
		DIGIT();
		DIGIT();
		END_FUN(SUCCESS); return ;
	}
	catch (std::exception & e) { LOAD_HEAD(0); }
	try
	{
		// std::cout << "dec_octet try " << __LINE__ << std::endl;
		RANGE(0x31, 0x39);
		DIGIT();
		END_FUN(SUCCESS); return ;
	}
	catch (std::exception & e) { LOAD_HEAD(0); }
	try
	{
		// std::cout << "dec_octet try " << __LINE__ << std::endl;
		DIGIT();
		END_FUN(SUCCESS); return ;
	}
	catch (std::exception & e) {
		LOAD_HEAD(0);
		// std::cout << "dec_octet last catch " << __LINE__ << std::endl;
		END_FUN(FAILURE);
		throw (Exceptions::ParserException("dec_octet expected"));
	}
}

// port_no			= 1*4( DIGIT )                  ; 0-9999      ; 0-9 0-9 0-9 0-9
// 				/ 0x31-35 4( DIGIT )            ; 10000-59999 ; 1-5 0-9 0-9 0-9 0-9
// 				/ '6' 0x30-34 3( DIGIT )        ; 60000-64999 ; "6" 0-4 0-9 0-9 0-9
// 				/ '6' '5' 0x30-34 2( DIGIT )    ; 65000-65499 ; "65" 0-4 0-9 0-9
// 				/ '6' '5' '5' 0x30-32 DIGIT     ; 65500-65529 ; "655" 0-2 0-9
// 				/ '6' '5' '5' '3' 0x30-35       ; 65530-65535 ; "6553" 0-5
void	ConfigParser::port_no(void)
{START_FUN;
	SAVE_HEAD(0);

	try
	{
		CHAR('6');
		CHAR('5');
		CHAR('5');
		CHAR('3');
		RANGE(0x31, 0x35);
		END_FUN(SUCCESS); return ;
	}
	catch (std::exception & e) { LOAD_HEAD(0); }
	try
	{
		CHAR('6');
		CHAR('5');
		CHAR('5');
		RANGE(0x30, 0x32);
		DIGIT();
		END_FUN(SUCCESS); return ;
	}
	catch (std::exception & e) { LOAD_HEAD(0); }
	try
	{
		CHAR('6');
		CHAR('5');
		RANGE(0x30, 0x34);
		DIGIT();
		DIGIT();
		END_FUN(SUCCESS); return ;
	}
	catch (std::exception & e) { LOAD_HEAD(0); }
	try
	{
		CHAR('6');
		RANGE(0x30, 0x34);
		DIGIT();
		DIGIT();
		DIGIT();
		END_FUN(SUCCESS); return ;
	}
	catch (std::exception & e) { LOAD_HEAD(0); }
	try
	{
		RANGE(0x31, 0x35);
		DIGIT();
		DIGIT();
		DIGIT();
		DIGIT();
		END_FUN(SUCCESS); return ;
	}
	catch (std::exception & e) { LOAD_HEAD(0); }
	try
	{
		DIGIT();
		try { DIGIT(); }
		catch (std::exception & e) { END_FUN(SUCCESS); return ; }
		try { DIGIT(); }
		catch (std::exception & e) { END_FUN(SUCCESS); return ; }
		try { DIGIT(); }
		catch (std::exception & e) { END_FUN(SUCCESS); return ; }
		END_FUN(SUCCESS); return ;
	}
	catch (std::exception & e) {
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		throw (Exceptions::ParserException("port_no expected"));
	}
	END_FUN(SUCCESS);
}

// IPv4address		= dec_octet '.' dec_octet '.' dec_octet '.' dec_octet
void	ConfigParser::IPv4address(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		// std::cout << "try IPv4address" << std::endl;
		dec_octet();
		CHAR('.');
		dec_octet();
		CHAR('.');
		dec_octet();
		CHAR('.');
		dec_octet();
	}
	catch (std::exception & e) {
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		throw (Exceptions::ParserException("IPv4address expected"));
	}
	END_FUN(SUCCESS);
}

// unreserved		= ALPHA / DIGIT / '_' / '-' / '.' / '~'
void	ConfigParser::unreserved(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		try { ALPHA(); END_FUN(SUCCESS); return ; }
		catch (std::exception & e) { LOAD_HEAD(0); }
		try { DIGIT(); END_FUN(SUCCESS); return ; }
		catch (std::exception & e) { LOAD_HEAD(0); }
		try { CHAR('_'); END_FUN(SUCCESS); return ; }
		catch (std::exception & e) { LOAD_HEAD(0); }
		try { CHAR('-'); END_FUN(SUCCESS); return ; }
		catch (std::exception & e) { LOAD_HEAD(0); }
		try { CHAR('.'); END_FUN(SUCCESS); return ; }
		catch (std::exception & e) { LOAD_HEAD(0); }
		try { CHAR('~'); END_FUN(SUCCESS); return ; }
		catch (std::exception & e) { LOAD_HEAD(0); }
		throw(Exceptions::ParserException(""));
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		throw (Exceptions::ParserException("unreserved expected"));
	}
	END_FUN(FAILURE);
}

// name			= 1*( unreserved )
void	ConfigParser::name(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		unreserved();
		while (1)
		{
			try { unreserved(); }
			catch (std::exception & e) { break ; }
		}
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		throw (Exceptions::ParserException("name expected"));
	}
	END_FUN(SUCCESS);
}

// number			= TDIGIT *( DIGIT )
void	ConfigParser::number(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		TDIGIT();
		while (1)
		{
			try { DIGIT(); }
			catch (std::exception & e) { break ; }
		}
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		throw (Exceptions::ParserException("number expected"));
	}
	END_FUN(SUCCESS);
}

// sub_delims		= '!' / '$' / '&' / '\'' / '(' / ')' / '*' / '+' / '='
void	ConfigParser::sub_delims(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		try { CHAR('!'); END_FUN(SUCCESS); return ; }
		catch (std::exception & e) { LOAD_HEAD(0); }
		try { CHAR('$'); END_FUN(SUCCESS); return ; }
		catch (std::exception & e) { LOAD_HEAD(0); }
		try { CHAR('&'); END_FUN(SUCCESS); return ; }
		catch (std::exception & e) { LOAD_HEAD(0); }
		try { CHAR('\\'); END_FUN(SUCCESS); return ; }
		catch (std::exception & e) { LOAD_HEAD(0); }
		try { CHAR('('); END_FUN(SUCCESS); return ; }
		catch (std::exception & e) { LOAD_HEAD(0); }
		try { CHAR(')'); END_FUN(SUCCESS); return ; }
		catch (std::exception & e) { LOAD_HEAD(0); }
		try { CHAR('*'); END_FUN(SUCCESS); return ; }
		catch (std::exception & e) { LOAD_HEAD(0); }
		try { CHAR('+'); END_FUN(SUCCESS); return ; }
		catch (std::exception & e) { LOAD_HEAD(0); }
		try { CHAR('='); END_FUN(SUCCESS); return ; }
		catch (std::exception & e) { LOAD_HEAD(0); }
		throw(Exceptions::ParserException(""));
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		throw (Exceptions::ParserException("sub_delims expected"));
	}
	END_FUN(FAILURE);
}

// pchar			= unreserved / sub_delims / ":" / "@"
void	ConfigParser::pchar(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		try { unreserved(); END_FUN(SUCCESS); return ; }
		catch (std::exception & e) { LOAD_HEAD(0); }
		try { sub_delims(); END_FUN(SUCCESS); return ; }
		catch (std::exception & e) { LOAD_HEAD(0); }
		try { CHAR(':'); END_FUN(SUCCESS); return ; }
		catch (std::exception & e) { LOAD_HEAD(0); }
		try { CHAR('@'); END_FUN(SUCCESS); return ; }
		catch (std::exception & e) { LOAD_HEAD(0); }
		throw(Exceptions::ParserException(""));
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		throw (Exceptions::ParserException("pchar expected"));
	}
	END_FUN(FAILURE);
}

// segment_nz		= 1*( pchar )
void	ConfigParser::segment_nz(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		pchar();
		while (1)
		{
			try { pchar(); }
			catch (std::exception & e) { break ; }
		}
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		throw (Exceptions::ParserException("segment_nz expected"));
	}
	END_FUN(SUCCESS);
}

// segment			= *( pchar )
void	ConfigParser::segment(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		while (1)
		{
			try { pchar(); }
			catch (std::exception & e) { break ; }
		}
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		throw (Exceptions::ParserException("segment expected"));
	}
	END_FUN(SUCCESS);
}

// path			= ( [ '/' ] segment_nz *( '/' segment ) ) / '/'
void	ConfigParser::path(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		try { CHAR('/'); }
		catch (std::exception & e) { }
		segment_nz();
		while (1)
		{
			SAVE_HEAD(1);
			try { CHAR('/'); segment(); }
			catch (std::exception & e) { LOAD_HEAD(1); break ; }
		}
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		try { CHAR('/'); }
		catch (std::exception & e)
		{
			LOAD_HEAD(0);
			END_FUN(FAILURE);
			throw (Exceptions::ParserException("path expected"));
		}
	}
	END_FUN(SUCCESS);
}

// file			= path segment_nz
void	ConfigParser::file(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		path();
		// segment_nz();
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		throw (Exceptions::ParserException("file expected"));
	}
	END_FUN(SUCCESS);
}

// status_code		= 3( DIGIT )
void	ConfigParser::status_code(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		DIGIT();
		DIGIT();
		DIGIT();
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		throw (Exceptions::ParserException("status_code expected"));
	}
	END_FUN(SUCCESS);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// item_error		= status_code OWSON ':' OWSON file OWSON ';'
void	ConfigParser::item_error(void)
{START_FUN;
	SAVE_HEAD(0);
	int			tmp_status_code;
	std::string	tmp_file;
	try
	{
		init_digest();
		status_code();
		digest(g_tmp);
		tmp_status_code = ft_atoi(g_tmp);
		OWSON();
		CHAR(':');
		OWSON();
		init_digest();
		file();
		digest(g_tmp);
		tmp_file = g_tmp;
		OWSON();
		CHAR(';');
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		throw (Exceptions::ParserException("item_error expected"));
	}
	tmp_error_pages.insert(std::pair<int,std::string>(tmp_status_code, tmp_file));
	END_FUN(SUCCESS);
}

// index			= index_token OWSON ':' OWSON file OWSON ';'
void	ConfigParser::index(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		index_token();
		OWSON();
		CHAR(':');
		OWSON();
		init_digest();
		file();
		digest(g_tmp);
		tmp_location.setIndex(g_tmp);
		OWSON();
		CHAR(';');
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		throw (Exceptions::ParserException("index expected"));
	}
	END_FUN(SUCCESS);
}

// uri				= uri_token OWSON ':' OWSON path OWSON ';'
void	ConfigParser::uri(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		uri_token();
		OWSON();
		CHAR(':');
		OWSON();
		init_digest();
		path();
		digest(g_tmp);
		tmp_location.setUri(g_tmp);
		OWSON();
		CHAR(';');
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		throw (Exceptions::ParserException("uri expected"));
	}
	END_FUN(SUCCESS);
}

// server_root			= root_token OWSON ':' OWSON path OWSON ';'
void	ConfigParser::server_root(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		root_token();
		OWSON();
		CHAR(':');
		OWSON();
		init_digest();
		path();
		digest(g_tmp);
		tmp_server.setRootDir(g_tmp);
		OWSON();
		CHAR(';');
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		throw (Exceptions::ParserException("server_root expected"));
	}
	END_FUN(SUCCESS);
}

// location_root			= root_token OWSON ':' OWSON path OWSON ';'
void	ConfigParser::location_root(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		root_token();
		OWSON();
		CHAR(':');
		OWSON();
		init_digest();
		path();
		digest(g_tmp);
		tmp_location.setRootLoc(g_tmp);
		OWSON();
		CHAR(';');
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		throw (Exceptions::ParserException("location_root expected"));
	}
	END_FUN(SUCCESS);
}

// autoindex		= autoindex_token OWSON ':' OWSON 1( on_token / off_token ) OWSON ';'
void	ConfigParser::autoindex(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		autoindex_token();
		OWSON();
		CHAR(':');
		OWSON();
		try {
			// init_digest();
			on_token();
			// digest(g_tmp);
			tmp_location.setAutoindex(true);
		}
		catch (std::exception & e) {
			try {
				// init_digest();
				off_token();
				// digest(g_tmp);
				tmp_location.setAutoindex(false);
			}
			catch (std::exception & e) { throw(Exceptions::ParserException("token [on / off] expected")); }
		}
		OWSON();
		CHAR(';');
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		throw (Exceptions::ParserException("autoindex expected"));
	}
	END_FUN(SUCCESS);
}

// alias			= alias_token OWSON ':' OWSON '[' OWSON [ path OWSON *( ',' OWSON path ) OWSON ] ']'
void	ConfigParser::alias(void)
{START_FUN;
	SAVE_HEAD(0);
	std::vector<std::string> tmp_alias;
	try
	{
		alias_token();
		OWSON();
		CHAR(':');
		OWSON();
		CHAR('[');
		OWSON();
		SAVE_HEAD(1);
		try { // optional
			init_digest();
			path();
			digest(g_tmp);
			tmp_alias.push_back(g_tmp);
			OWSON();
			while (1)
			{
				SAVE_HEAD(2);
				try {
					CHAR(',');
					OWSON();
					init_digest();
					path();
					digest(g_tmp);
					tmp_alias.push_back(g_tmp);
				}
				catch (std::exception & e) { LOAD_HEAD(2); break ;}
			}
			OWSON();
		}
		catch (std::exception & e) { LOAD_HEAD(1); }
		CHAR(']');
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		throw (Exceptions::ParserException("alias expected"));
	}
	tmp_location.setAlias(tmp_alias);
	END_FUN(SUCCESS);
}

// method			= method_token OWSON ':' OWSON '[' OWSON [ token OWSON *( ',' OWSON token ) OWSON ] ']'
void	ConfigParser::method(void)
{START_FUN;
	SAVE_HEAD(0);
	std::vector<std::string> tmp_method;
	try
	{
		method_token();
		OWSON();
		CHAR(':');
		OWSON();
		CHAR('[');
		OWSON();
		SAVE_HEAD(1);
		try { // optional
			init_digest();
			token();
			digest(g_tmp);
			tmp_method.push_back(g_tmp);
			OWSON();
			while (1)
			{
				SAVE_HEAD(2);
				try {
					CHAR(',');
					OWSON();
					init_digest();
					token();
					digest(g_tmp);
					tmp_method.push_back(g_tmp);
				}
				catch (std::exception & e) { LOAD_HEAD(2); break ; }
			}
			OWSON();
		}
		catch (std::exception & e) { LOAD_HEAD(1); }
		CHAR(']');
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		throw (Exceptions::ParserException("method expected"));
	}
	tmp_location.setMethods(tmp_method);
	END_FUN(SUCCESS);
}

// upload			= upload_token OWSON ':' OWSON ( ( on_token OWSON path ) / off_token ) OWSON ';'
void	ConfigParser::upload(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		upload_token();
		OWSON();
		CHAR(':');
		OWSON();
		SAVE_HEAD(1);
		try {
			on_token();
			OWSON();
			init_digest();
			path();
			digest(g_tmp);
			tmp_location.setUpload(g_tmp);
		}
		catch (std::exception & e) {
			LOAD_HEAD(1);
			try { off_token(); }
			catch (std::exception & e) { throw(Exceptions::ParserException("token [on path / off] expected")); }
		}
		OWSON();
		CHAR(';');
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		throw (Exceptions::ParserException("upload expected"));
	}
	END_FUN(SUCCESS);
}

// item_location	= uri / root / index / autoindex / alias / method / upload
void	ConfigParser::item_location(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		try { uri(); END_FUN(SUCCESS); return ; }
		catch (std::exception & e) { LOAD_HEAD(0); }
		try { location_root(); END_FUN(SUCCESS); return ; }
		catch (std::exception & e) { LOAD_HEAD(0); }
		try { index(); END_FUN(SUCCESS); return ; }
		catch (std::exception & e) { LOAD_HEAD(0); }
		try { autoindex(); END_FUN(SUCCESS); return ; }
		catch (std::exception & e) { LOAD_HEAD(0); }
		try { alias(); END_FUN(SUCCESS); return ; }
		catch (std::exception & e) { LOAD_HEAD(0); }
		try { method(); END_FUN(SUCCESS); return ; }
		catch (std::exception & e) { LOAD_HEAD(0); }
		try { upload(); END_FUN(SUCCESS); return ; }
		catch (std::exception & e) { LOAD_HEAD(0); }
		throw(Exceptions::ParserException(""));
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		throw (Exceptions::ParserException("item_location expected"));
	}
	END_FUN(FAILURE);
}

// host			= host_token OWSON ':' OWSON IPv4address OWSON ';'
void	ConfigParser::host(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		host_token();
		OWSON();
		CHAR(':');
		OWSON();
		init_digest();
		IPv4address();
		digest(g_tmp);
		tmp_server.setHost(g_tmp);
		OWSON();
		CHAR(';');
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		throw (Exceptions::ParserException("host expected"));
	}
	END_FUN(SUCCESS);
}

// port			= port_token OWSON ':' OWSON port_no OWSON ';'
void	ConfigParser::port(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		port_token();
		OWSON();
		CHAR(':');
		OWSON();
		init_digest();
		port_no();
		digest(g_tmp);
		tmp_server.setPort(ft_atoi(g_tmp));
		OWSON();
		CHAR(';');
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		throw (Exceptions::ParserException("port expected"));
	}
	END_FUN(SUCCESS);
}

// server_name		= server_name_token OWSON ':' OWSON name OWSON ';'
void	ConfigParser::server_name(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		server_name_token();
		OWSON();
		CHAR(':');
		OWSON();
		init_digest();
		name();
		digest(g_tmp);
		tmp_server.setServerName(g_tmp);
		OWSON();
		CHAR(';');
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		throw (Exceptions::ParserException("server_name expected"));
	}
	END_FUN(SUCCESS);
}

// max_client_body	= max_client_body_token OWSON ':' OWSON number OWSON ';'
void	ConfigParser::max_client_body(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		max_client_body_token();
		OWSON();
		CHAR(':');
		OWSON();
		init_digest();
		number();
		digest(g_tmp);
		tmp_server.setMaxBodySize(ft_atoi(g_tmp));
		OWSON();
		CHAR(';');
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		throw (Exceptions::ParserException("max_client_body expected"));
	}
	END_FUN(SUCCESS);
}

// error			= error_token ':' OWSON '{' OWSON *( item_error OWSON ) '}'
void	ConfigParser::error(void)
{START_FUN;
	SAVE_HEAD(0);
	tmp_error_pages.clear();
	try
	{
		error_token();
		CHAR(':');
		OWSON();
		CHAR('{');
		OWSON();
		while (1)
		{
			SAVE_HEAD(1);
			try {
				item_error(); OWSON(); }
			catch (std::exception & e) { LOAD_HEAD(1); break ; }
		}
		CHAR('}');
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		throw (Exceptions::ParserException("error expected"));
	}
	tmp_server.setErrorPages(tmp_error_pages);
	END_FUN(SUCCESS);
}

// location		= location_token ':' OWSON '{' OWSON *( item_location OWSON ) '}'
void	ConfigParser::location(void)
{START_FUN;
	SAVE_HEAD(0);
	tmp_location.clear();
	try
	{
		location_token();
		CHAR(':');
		OWSON();
		CHAR('{');
		OWSON();
		while (1)
		{
			SAVE_HEAD(1);
			try
			{
				item_location();
				OWSON();
			}
			catch (std::exception & e) { LOAD_HEAD(1); break ; }
		}
		CHAR('}');
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		throw (Exceptions::ParserException("location expected"));
	}
	tmp_map_locations.insert(std::pair<std::string, Location>(tmp_location.getUri(), tmp_location));
	END_FUN(SUCCESS);
}

// item			= host / port / server_name / root / max_client_body / error / location
void	ConfigParser::item(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		try { host(); END_FUN(SUCCESS); return ; }
		catch (std::exception & e) { LOAD_HEAD(0); }
		try { port(); END_FUN(SUCCESS); return ; }
		catch (std::exception & e) { LOAD_HEAD(0); }
		try { server_name(); END_FUN(SUCCESS); return ; }
		catch (std::exception & e) { LOAD_HEAD(0); }
		try { server_root(); END_FUN(SUCCESS); return ; }
		catch (std::exception & e) { LOAD_HEAD(0); }
		try { max_client_body(); END_FUN(SUCCESS); return ; }
		catch (std::exception & e) { LOAD_HEAD(0); }
		try { error(); END_FUN(SUCCESS); return ; }
		catch (std::exception & e) { LOAD_HEAD(0); }
		try { location(); END_FUN(SUCCESS); return ; }
		catch (std::exception & e) { LOAD_HEAD(0); }
		throw(Exceptions::ParserException(""));
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		throw (Exceptions::ParserException("item expected"));
	}
	END_FUN(FAILURE);
}

// server			= server_token OWSON ':' OWSON '{' OWSON *( item OWSON ) '}'
void	ConfigParser::server(void)
{START_FUN;
	SAVE_HEAD(0);
	tmp_server.clear();
	tmp_map_locations.clear();
	try
	{
		server_token();
		OWSON();
		CHAR(':');
		OWSON();
		CHAR('{');
		OWSON();
		while (1)
		{
			SAVE_HEAD(1);
			try {
				item(); OWSON();
			}
			catch (std::exception & e) { LOAD_HEAD(1); break ; }
		}
		CHAR('}');
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		throw (Exceptions::ParserException("server expected"));
	}
	tmp_server.setLocations(tmp_map_locations);
	this->_servers_config.push_back(tmp_server);
	END_FUN(SUCCESS);
}

// config			= OWSON 1*( server OWSON )
void	ConfigParser::config(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		OWSON();
		server();
		OWSON();
		while (1)
		{
			SAVE_HEAD(1);
			try {
				server(); OWSON(); }
			catch (std::exception & e) { LOAD_HEAD(1); break ; }
		}
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		throw (Exceptions::ParserException("config expected"));
	}
	END_FUN(SUCCESS);
}
