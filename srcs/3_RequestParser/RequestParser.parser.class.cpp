
#include <webserv.hpp>

// int				deep = 0;
// std::string		g_tmp;

// CRLF = CR LF
void	RequestParser::CRLF(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		CR();
		LF();
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		SET_ERROR;
		throw (Exceptions::ParserException("CRLF expected"));
	}
	RESET_ERROR;
	END_FUN(SUCCESS);
}


// OWS = *( SP / HTAB )
void	RequestParser::OWS(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		while (1)
		{
			try { SP(); continue ; }
			catch (std::exception & e) { }
			try { HTAB(); continue ; }
			catch (std::exception & e) { break ; }
		}
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		SET_ERROR;
		throw (Exceptions::ParserException("OWS expected"));
	}
	RESET_ERROR;
	END_FUN(SUCCESS);
}

// dec_octet	= DIGIT                 ; 0-9
// 				/ 0x31-39 DIGIT         ; 10-99   ; 1-9 0-9
// 				/ "1" 2DIGIT            ; 100-199 ; "1" 0-9 0-9
// 				/ "2" 0x30-34 DIGIT     ; 200-249 ; "2" 0-4 0-9
// 				/ "25" 0x30-35          ; 250-255 ; "25" 0-5
void	RequestParser::dec_octet(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		CHAR('2');
		CHAR('5');
		RANGE(0x30, 0x35);
		RESET_ERROR;
		END_FUN(SUCCESS); return ;
	}
	catch (std::exception & e) { LOAD_HEAD(0); }
	try
	{
		CHAR('2');
		RANGE(0x30, 0x34);
		DIGIT();
		RESET_ERROR;
		END_FUN(SUCCESS); return ;
	}
	catch (std::exception & e) { LOAD_HEAD(0); }
	try
	{
		CHAR('1');
		DIGIT();
		DIGIT();
		RESET_ERROR;
		END_FUN(SUCCESS); return ;
	}
	catch (std::exception & e) { LOAD_HEAD(0); }
	try
	{
		RANGE(0x31, 0x39);
		DIGIT();
		RESET_ERROR;
		END_FUN(SUCCESS); return ;
	}
	catch (std::exception & e) { LOAD_HEAD(0); }
	try
	{
		DIGIT();
		RESET_ERROR;
		END_FUN(SUCCESS); return ;
	}
	catch (std::exception & e) {
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		SET_ERROR;
		throw (Exceptions::ParserException("dec_octet expected"));
	}
}

// IPvFuture     = "v" 1*HEXDIG "." 1*( unreserved / sub_delims / ":" )
void	RequestParser::IPvFuture(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		CHAR('v');
		for (int i = 0; 1; i++)
		{
			try { HEXDIG(); }
			catch (std::exception & e) { if (i < 1) throw (e); else break ; }
		}
		CHAR('.');
		for (int i = 0; 1; i++)
		{
			try { unreserved(); continue ; }
			catch (std::exception & e) {}
			try { sub_delims(); continue ; }
			catch (std::exception & e) {}
			try { CHAR(':'); continue ; }
			catch (std::exception & e) { if (i < 1) throw (e); else break ; }
		}
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		SET_ERROR;
		throw (Exceptions::ParserException("IPvFuture expected"));
	}
	RESET_ERROR;
	END_FUN(SUCCESS);
}

// h16           = 1*4( HEXDIG )
void	RequestParser::h16(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		for (int i = 0; i < 4; i++)
		{
			try { HEXDIG(); }
			catch (std::exception & e) { if (i < 1) throw (e); else break ; }
		}
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		SET_ERROR;
		throw (Exceptions::ParserException("h16 expected"));
	}
	RESET_ERROR;
	END_FUN(SUCCESS);
}

// ls32          = ( h16 ":" h16 ) / IPv4address
void	RequestParser::ls32(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		h16();
		CHAR(':');
		h16();
	}
	catch (std::exception & e) { LOAD_HEAD(0); }
	try
	{
		IPv4address();
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		SET_ERROR;
		throw (Exceptions::ParserException("ls32 expected"));
	}
	RESET_ERROR;
	END_FUN(SUCCESS);
}

// IPv6address	=                            6( h16 ":" ) ls32
// 				/                       "::" 5( h16 ":" ) ls32
// 				/ [               h16 ] "::" 4( h16 ":" ) ls32
// 				/ [ *1( h16 ":" ) h16 ] "::" 3( h16 ":" ) ls32
// 				/ [ *2( h16 ":" ) h16 ] "::" 2( h16 ":" ) ls32
// 				/ [ *3( h16 ":" ) h16 ] "::"    h16 ":"   ls32
// 				/ [ *4( h16 ":" ) h16 ] "::"              ls32
// 				/ [ *5( h16 ":" ) h16 ] "::"              h16
// 				/ [ *6( h16 ":" ) h16 ] "::"
void	RequestParser::IPv6address(void)
{START_FUN;
	SAVE_HEAD(0);
	// 6( h16 ":" ) ls32
	try
	{
		for (int i = 0; i < 6; i++)
		{
			SAVE_HEAD(1);
			try { h16(); CHAR(':'); }
			catch (std::exception & e) { LOAD_HEAD(1); if (i < 6) throw (e); else break ; }
		}
		ls32();
	}
	catch (std::exception & e) { LOAD_HEAD(0); }
	// "::" 5( h16 ":" ) ls32
	try
	{
		CHAR(':');
		CHAR(':');
		for (int i = 0; i < 5; i++)
		{
			SAVE_HEAD(1);
			try { h16(); CHAR(':'); }
			catch (std::exception & e) { LOAD_HEAD(1); if (i < 5) throw (e); else break ; }
		}
		ls32();
	}
	catch (std::exception & e) { LOAD_HEAD(0); }
	// [ h16 ] "::" 4( h16 ":" ) ls32
	try
	{
		try { h16(); }
		catch (std::exception & e) {}
		CHAR(':');
		CHAR(':');
		for (int i = 0; i < 4; i++)
		{
			SAVE_HEAD(1);
			try { h16(); CHAR(':'); }
			catch (std::exception & e) { LOAD_HEAD(1); if (i < 4) throw (e); else break ; }
		}
		ls32();
	}
	catch (std::exception & e) { LOAD_HEAD(0); }
	// [ *1( h16 ":" ) h16 ] "::" 3( h16 ":" ) ls32
	try
	{
		SAVE_HEAD(1);
		try
		{
			for (int i = 0; i < 1; i++)
			{
				SAVE_HEAD(2);
				try { h16(); CHAR(':'); }
				catch (std::exception & e) { LOAD_HEAD(2); break ; }
			}
			h16();
		}
		catch (std::exception & e) { LOAD_HEAD(1); }
		CHAR(':');
		CHAR(':');
		for (int i = 0; i < 3; i++)
		{
			SAVE_HEAD(1);
			try { h16(); CHAR(':'); }
			catch (std::exception & e) { LOAD_HEAD(1); if (i < 3) throw (e); else break ; }
		}
		ls32();
	}
	catch (std::exception & e) { LOAD_HEAD(0); }
	// [ *2( h16 ":" ) h16 ] "::" 2( h16 ":" ) ls32
	try
	{
		SAVE_HEAD(1);
		try
		{
			for (int i = 0; i < 2; i++)
			{
				SAVE_HEAD(2);
				try { h16(); CHAR(':'); }
				catch (std::exception & e) { LOAD_HEAD(2); break ; }
			}
			h16();
		}
		catch (std::exception & e) { LOAD_HEAD(1); }
		CHAR(':');
		CHAR(':');
		for (int i = 0; i < 2; i++)
		{
			SAVE_HEAD(1);
			try { h16(); CHAR(':'); }
			catch (std::exception & e) { LOAD_HEAD(1); if (i < 2) throw (e); else break ; }
		}
		ls32();
	}
	catch (std::exception & e) { LOAD_HEAD(0); }
	// [ *3( h16 ":" ) h16 ] "::" h16 ":" ls32
	try
	{
		SAVE_HEAD(1);
		try
		{
			for (int i = 0; i < 3; i++)
			{
				SAVE_HEAD(2);
				try { h16(); CHAR(':'); }
				catch (std::exception & e) { LOAD_HEAD(2); break ; }
			}
			h16();
		}
		catch (std::exception & e) { LOAD_HEAD(1); }
		CHAR(':');
		CHAR(':');
		h16();
		CHAR(':');
		ls32();
	}
	catch (std::exception & e) { LOAD_HEAD(0); }
	// [ *4( h16 ":" ) h16 ] "::" ls32
	try
	{
		SAVE_HEAD(1);
		try
		{
			for (int i = 0; i < 4; i++)
			{
				SAVE_HEAD(2);
				try { h16(); CHAR(':'); }
				catch (std::exception & e) { LOAD_HEAD(2); break ; }
			}
			h16();
		}
		catch (std::exception & e) { LOAD_HEAD(1); }
		CHAR(':');
		CHAR(':');
		ls32();
	}
	catch (std::exception & e) { LOAD_HEAD(0); }
	// [ *5( h16 ":" ) h16 ] "::" h16
	try
	{
		SAVE_HEAD(1);
		try
		{
			for (int i = 0; i < 5; i++)
			{
				SAVE_HEAD(2);
				try { h16(); CHAR(':'); }
				catch (std::exception & e) { LOAD_HEAD(2); break ; }
			}
			h16();
		}
		catch (std::exception & e) { LOAD_HEAD(1); }
		CHAR(':');
		CHAR(':');
		h16();
	}
	catch (std::exception & e) { LOAD_HEAD(0); }
	// [ *6( h16 ":" ) h16 ] "::"
	try
	{
		SAVE_HEAD(1);
		try
		{
			for (int i = 0; i < 6; i++)
			{
				SAVE_HEAD(2);
				try { h16(); CHAR(':'); }
				catch (std::exception & e) { LOAD_HEAD(2); break ; }
			}
			h16();
		}
		catch (std::exception & e) { LOAD_HEAD(1); }
		CHAR(':');
		CHAR(':');
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		SET_ERROR;
		throw (Exceptions::ParserException("IPv6address expected"));
	}
	RESET_ERROR;
	END_FUN(SUCCESS);
}


// IPv4address = dec_octet "." dec_octet "." dec_octet "." dec_octet
void	RequestParser::IPv4address(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		dec_octet();
		CHAR('.');
		dec_octet();
		CHAR('.');
		dec_octet();
		CHAR('.');
		dec_octet();
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		SET_ERROR;
		throw (Exceptions::ParserException("IPv4address expected"));
	}
	RESET_ERROR;
	END_FUN(SUCCESS);
}

// segment_nz = 1*(pchar)
void	RequestParser::segment_nz(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		for (int i = 0; 1; i++)
		{
			try { pchar(); }
			catch (std::exception & e) { if (i < 1) throw (e); else break ; }
		}
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		SET_ERROR;
		throw (Exceptions::ParserException("segment_nz expected"));
	}
	RESET_ERROR;
	END_FUN(SUCCESS);
}

// reg_name = *( unreserved / pct_encoded / sub_delims )
void	RequestParser::reg_name(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		while (1)
		{
			try { unreserved(); continue ; }
			catch (std::exception & e) {}
			try { pct_encoded(); continue ; }
			catch (std::exception & e) {}
			try { sub_delims(); continue ; }
			catch (std::exception & e) { break ; }
		}
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		SET_ERROR;
		throw (Exceptions::ParserException("reg_name expected"));
	}
	RESET_ERROR;
	END_FUN(SUCCESS);
}

// IP_literal = "[" ( IPv6address / IPvFuture  ) "]"
void	RequestParser::IP_literal(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		CHAR('[');
		for (int i = 0; i < 1; i++) // tp_or
		{
			try { IPv6address(); break ; }
			catch (std::exception & e) {}
			try { IPvFuture(); break ; }
			catch (std::exception & e) { throw (e); }
		}
		CHAR(']');
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		SET_ERROR;
		throw (Exceptions::ParserException("IP_literal expected"));
	}
	RESET_ERROR;
	END_FUN(SUCCESS);
}

// path_rootless = segment_nz *( "/" segment )
void	RequestParser::path_rootless(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
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
		END_FUN(FAILURE);
		SET_ERROR;
		throw (Exceptions::ParserException("path_rootless expected"));
	}
	RESET_ERROR;
	END_FUN(SUCCESS);
}

// path_absolute = "/" [ segment_nz *( "/" segment ) ]
void	RequestParser::path_absolute(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		CHAR('/');
		for (int i = 0; i < 1; i++)
		{
			SAVE_HEAD(1);
			try
			{
				segment_nz();
				while (1)
				{
					SAVE_HEAD(2);
					try { CHAR('/'); segment(); }
					catch (std::exception & e) { LOAD_HEAD(2); break ; }
				}
			}
			catch (std::exception & e) { LOAD_HEAD(1); break ; }
		}
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		SET_ERROR;
		throw (Exceptions::ParserException("path_absolute expected"));
	}
	RESET_ERROR;
	END_FUN(SUCCESS);
}

// path_abempty = *( "/" segment )
void	RequestParser::path_abempty(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
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
		END_FUN(FAILURE);
		SET_ERROR;
		throw (Exceptions::ParserException("path_abempty expected"));
	}
	RESET_ERROR;
	END_FUN(SUCCESS);
}

// sub_delims = "!" / "$" / "&" / "'" / "(" / ")" / "*" / "+" / "," / ";" / "="
void	RequestParser::sub_delims(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		for (int i = 0; i < 1; i++)
		{
			try { CHAR('!'); break ; }
			catch (std::exception & e) {}
			try { CHAR('$'); break ; }
			catch (std::exception & e) {}
			try { CHAR('&'); break ; }
			catch (std::exception & e) {}
			try { CHAR('\''); break ; }
			catch (std::exception & e) {}
			try { CHAR('('); break ; }
			catch (std::exception & e) {}
			try { CHAR(')'); break ; }
			catch (std::exception & e) {}
			try { CHAR('*'); break ; }
			catch (std::exception & e) {}
			try { CHAR('+'); break ; }
			catch (std::exception & e) {}
			try { CHAR(','); break ; }
			catch (std::exception & e) {}
			try { CHAR(';'); break ; }
			catch (std::exception & e) {}
			try { CHAR('='); break ; }
			catch (std::exception & e) {}
			throw(Exceptions::ParserException(""));
		}
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		SET_ERROR;
		throw (Exceptions::ParserException("sub_delims expected"));
	}
	RESET_ERROR;
	END_FUN(SUCCESS);
}

// pct_encoded = "%" HEXDIG HEXDIG
void	RequestParser::pct_encoded(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		CHAR('%');
		HEXDIG();
		HEXDIG();
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		SET_ERROR;
		throw (Exceptions::ParserException("pct_encoded expected"));
	}
	RESET_ERROR;
	END_FUN(SUCCESS);
}

// unreserved = ALPHA / DIGIT / "-" / "." / "_" / "~"
void	RequestParser::unreserved(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		for (int i = 0; i < 1; i++)
		{
			try { ALPHA(); break ; }
			catch (std::exception & e) {}
			try { DIGIT(); break ; }
			catch (std::exception & e) {}
			try { CHAR('-'); break ; }
			catch (std::exception & e) {}
			try { CHAR('.'); break ; }
			catch (std::exception & e) {}
			try { CHAR('_'); break ; }
			catch (std::exception & e) {}
			try { CHAR('~'); break ; }
			catch (std::exception & e) {}
			throw(Exceptions::ParserException(""));
		}
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		SET_ERROR;
		throw (Exceptions::ParserException("unreserved expected"));
	}
	RESET_ERROR;
	END_FUN(SUCCESS);
}

// port = *DIGIT
void	RequestParser::port(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
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
		SET_ERROR;
		throw (Exceptions::ParserException("port expected"));
	}
	RESET_ERROR;
	END_FUN(SUCCESS);
}

// host = IP_literal / IPv4address / reg_name
void	RequestParser::host(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		for (int i = 0; i < 1; i++)
		{
			try { IP_literal(); break ; }
			catch (std::exception & e) {}
			try { IPv4address(); break ; }
			catch (std::exception & e) {}
			try { reg_name(); break ; }
			catch (std::exception & e) {}
			throw(Exceptions::ParserException(""));
		}
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		SET_ERROR;
		throw (Exceptions::ParserException("host expected"));
	}
	RESET_ERROR;
	END_FUN(SUCCESS);
}

// userinfo = *( unreserved / pct_encoded / sub_delims / ":" )
void	RequestParser::userinfo(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		while (1)
		{
			try { unreserved(); continue ; }
			catch (std::exception & e) { break ; }
			try { pct_encoded(); continue ; }
			catch (std::exception & e) { break ; }
			try { sub_delims(); continue ; }
			catch (std::exception & e) { break ; }
			try { CHAR(':'); continue ; }
			catch (std::exception & e) { break ; }
		}
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		SET_ERROR;
		throw (Exceptions::ParserException("userinfo expected"));
	}
	RESET_ERROR;
	END_FUN(SUCCESS);
}

// hier_part = "//" [ authority / path_abempty / path_absolute / path_rootless ]
void	RequestParser::hier_part(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		CHAR('/');
		CHAR('/');
		for (int i = 0; i < 1; i++)
		{
			try { authority(); break ; }
			catch (std::exception & e) {}
			try { path_abempty(); break ; }
			catch (std::exception & e) {}
			try { path_absolute(); break ; }
			catch (std::exception & e) {}
			try { path_rootless(); break ; }
			catch (std::exception & e) {}
		}
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		SET_ERROR;
		throw (Exceptions::ParserException("hier_part expected"));
	}
	RESET_ERROR;
	END_FUN(SUCCESS);
}

// scheme = ALPHA *( ALPHA / DIGIT / "+" / "-" / "." )
void	RequestParser::scheme(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		ALPHA();
		while (1)
		{
			try { ALPHA(); continue ; }
			catch (std::exception & e) { break ; }
			try { DIGIT(); continue ; }
			catch (std::exception & e) { break ; }
			try { CHAR('+'); continue ; }
			catch (std::exception & e) { break ; }
			try { CHAR('-'); continue ; }
			catch (std::exception & e) { break ; }
			try { CHAR('.'); continue ; }
			catch (std::exception & e) { break ; }
		}
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		SET_ERROR;
		throw (Exceptions::ParserException("scheme expected"));
	}
	RESET_ERROR;
	END_FUN(SUCCESS);
}

// pchar = unreserved / pct_encoded / sub_delims / ":" / "@"
void	RequestParser::pchar(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		for (int i = 0; i < 1; i++)
		{
			try { unreserved(); break ; }
			catch (std::exception & e) {}
			try { pct_encoded(); break ; }
			catch (std::exception & e) {}
			try { sub_delims(); break ; }
			catch (std::exception & e) {}
			try { CHAR(':'); break ; }
			catch (std::exception & e) {}
			try { CHAR('@'); break ; }
			catch (std::exception & e) {}
			throw(Exceptions::ParserException(""));
		}
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		SET_ERROR;
		throw (Exceptions::ParserException("pchar expected"));
	}
	RESET_ERROR;
	END_FUN(SUCCESS);
}

// segment = *pchar
void	RequestParser::segment(void)
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
		SET_ERROR;
		throw (Exceptions::ParserException("segment expected"));
	}
	RESET_ERROR;
	END_FUN(SUCCESS);
}

// authority = [ userinfo "@" ] host [ ":" port ]
void	RequestParser::authority(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		SAVE_HEAD(1);
		try
		{
			userinfo();
			CHAR('@');
		}
		catch (std::exception & e) { LOAD_HEAD(1); }
		host();
		RESAVE_HEAD(1);
		try
		{
			CHAR(':');
			port();
		}
		catch (std::exception & e) { LOAD_HEAD(1); }
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		SET_ERROR;
		throw (Exceptions::ParserException("authority expected"));
	}
	RESET_ERROR;
	END_FUN(SUCCESS);
}

// absolute_URI  = scheme ":" hier_part [ "?" query ]
void	RequestParser::absolute_URI(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		scheme();
		CHAR(':');
		hier_part();
		SAVE_HEAD(1);
		try
		{
			CHAR('?');
			query();
		}
		catch (std::exception & e) { LOAD_HEAD(1); }
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		SET_ERROR;
		throw (Exceptions::ParserException("absolute_URI expected"));
	}
	RESET_ERROR;
	END_FUN(SUCCESS);
}

// query = *( pchar / "/" / "?" )
void	RequestParser::query(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		while (1)
		{
			try { pchar(); continue ; }
			catch (std::exception & e) {}
			try { CHAR('/'); continue ; }
			catch (std::exception & e) {}
			try { CHAR('?'); continue ; }
			catch (std::exception & e) { break ; }
		}
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		SET_ERROR;
		throw (Exceptions::ParserException("query expected"));
	}
	RESET_ERROR;
	END_FUN(SUCCESS);
}

// absolute_path = 1*( "/" segment )
void	RequestParser::absolute_path(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		for (int i = 0; 1; i++)
		{
			SAVE_HEAD(1);
			try { CHAR('/'); segment(); }
			catch (std::exception & e) { LOAD_HEAD(1); if (i < 1) throw (e); else break ; }
		}
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		SET_ERROR;
		throw (Exceptions::ParserException("absolute_path expected"));
	}
	RESET_ERROR;
	END_FUN(SUCCESS);
}

// tchar = "!" / "#" / "$" / "%" / "&" / "'" / "*" / "+" / "-" / "." / "^" / "_" / "`" / "|" / "~" / DIGIT / ALPHA
void	RequestParser::tchar(void)
{
	// START_FUN;
	SAVE_HEAD(0);
	try
	{
		for (int i = 0; i < 1; i++)
		{
			try { CHAR('!'); break ; }
			catch (std::exception & e) {}
			try { CHAR('#'); break ; }
			catch (std::exception & e) {}
			try { CHAR('$'); break ; }
			catch (std::exception & e) {}
			try { CHAR('%'); break ; }
			catch (std::exception & e) {}
			try { CHAR('&'); break ; }
			catch (std::exception & e) {}
			try { CHAR('\''); break ; }
			catch (std::exception & e) {}
			try { CHAR('*'); break ; }
			catch (std::exception & e) {}
			try { CHAR('+'); break ; }
			catch (std::exception & e) {}
			try { CHAR('-'); break ; }
			catch (std::exception & e) {}
			try { CHAR('.'); break ; }
			catch (std::exception & e) {}
			try { CHAR('^'); break ; }
			catch (std::exception & e) {}
			try { CHAR('_'); break ; }
			catch (std::exception & e) {}
			try { CHAR('`'); break ; }
			catch (std::exception & e) {}
			try { CHAR('|'); break ; }
			catch (std::exception & e) {}
			try { CHAR('~'); break ; }
			catch (std::exception & e) {}
			try { DIGIT(); break ; }
			catch (std::exception & e) {}
			try { ALPHA(); break ; }
			catch (std::exception & e) {}
			throw(Exceptions::ParserException(""));
		}
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		// END_FUN(FAILURE);
		SET_ERROR;
		throw (Exceptions::ParserException("tchar expected"));
	}
		RESET_ERROR;
	END_FUN(SUCCESS);
}

// HTTP_name = 0x48.54.54.50 ; HTTP
void	RequestParser::HTTP_name(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		CHAR('H');
		CHAR('T');
		CHAR('T');
		CHAR('P');
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		SET_ERROR;
		throw (Exceptions::ParserException("HTTP_name expected"));
	}
	RESET_ERROR;
	END_FUN(SUCCESS);
}

// asterisk_form = "*"
void	RequestParser::asterisk_form(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		CHAR('*');
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		SET_ERROR;
		throw (Exceptions::ParserException("asterisk_form expected"));
	}
	RESET_ERROR;
	END_FUN(SUCCESS);
}

// authority_form = authority
void	RequestParser::authority_form(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		authority();
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		SET_ERROR;
		throw (Exceptions::ParserException("authority_form expected"));
	}
	RESET_ERROR;
	END_FUN(SUCCESS);
}

// absolute_form = absolute_URI
void	RequestParser::absolute_form(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		absolute_URI();
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		SET_ERROR;
		throw (Exceptions::ParserException("absolute_form expected"));
	}
	RESET_ERROR;
	END_FUN(SUCCESS);
}

// origin_form = absolute_path [ "?" query ]
void	RequestParser::origin_form(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		absolute_path();
		SAVE_HEAD(1);
		try
		{
			CHAR('?');
			query();
		}
		catch (std::exception & e) { LOAD_HEAD(1); }
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		SET_ERROR;
		throw (Exceptions::ParserException("origin_form expected"));
	}
	RESET_ERROR;
	END_FUN(SUCCESS);
}

// obs_fold = CRLF 1*( SP / HTAB )
void	RequestParser::obs_fold(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		CRLF();
		for (int i = 0; 1; i++)
		{
			try { SP(); continue ; }
			catch (std::exception & e) {}
			try { HTAB(); continue ; }
			catch (std::exception & e) { if (i < 1) throw (e); else break ; }
		}
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		SET_ERROR;
		throw (Exceptions::ParserException("obs_fold expected"));
	}
	RESET_ERROR;
	END_FUN(SUCCESS);
}

// field_vchar = VCHAR / obs_text
void	RequestParser::field_vchar(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		for (size_t i = 0; i < 1; i++)
		{
			try { VCHAR(); break ; }
			catch (std::exception & e) {}
			try { obs_text(); break ; }
			catch (std::exception & e) {}
			throw(Exceptions::ParserException(""));
		}
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		SET_ERROR;
		throw (Exceptions::ParserException("field_vchar expected"));
	}
	RESET_ERROR;
	END_FUN(SUCCESS);
}

// field_content = field_vchar [ 1*( SP / HTAB ) field_vchar ]
void	RequestParser::field_content(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		field_vchar();
		for (int i = 0; i < 1; i++)
		{
			SAVE_HEAD(1);
			try
			{
				for (int i = 0; 1; i++)
				{
					try { SP(); continue ; }
					catch (std::exception & e) {}
					try { HTAB(); continue ; }
					catch (std::exception & e) { if (i < 1) throw (e); else break ; }
				}
				field_vchar();
			}
			catch (std::exception & e) { LOAD_HEAD(1); break ; }
		}
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		SET_ERROR;
		throw (Exceptions::ParserException("field_content expected"));
	}
	RESET_ERROR;
	END_FUN(SUCCESS);
}

// token = 1*tchar
void	RequestParser::token(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		for (int i = 0; 1; i++)
		{
			try { tchar(); }
			catch (std::exception & e) { if (i < 1) throw (e); else break ; }
		}
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		SET_ERROR;
		throw (Exceptions::ParserException("token expected"));
	}
	RESET_ERROR;
	END_FUN(SUCCESS);
}

// HTTP_version = HTTP_name "/" DIGIT "." DIGIT
void	RequestParser::HTTP_version(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		HTTP_name();
		CHAR('/');
		init_digest();
		DIGIT();
		CHAR('.');
		DIGIT();
		digest(this->_http_version);
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		SET_ERROR;
		throw (Exceptions::ParserException("HTTP_version expected"));
	}
	RESET_ERROR;
	END_FUN(SUCCESS);
}

// request_target = origin_form / absolute_form / authority_form / asterisk_form
void	RequestParser::request_target(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		for (size_t i = 0; i < 1; i++)
		{
			try { origin_form(); break ; }
			catch (std::exception & e) {}
			try { absolute_form(); break ; }
			catch (std::exception & e) {}
			try { authority_form(); break ; }
			catch (std::exception & e) {}
			try { asterisk_form(); break ; }
			catch (std::exception & e) {}
			throw(Exceptions::ParserException(""));
		}
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		SET_ERROR;
		throw (Exceptions::ParserException("request_target expected"));
	}
	RESET_ERROR;
	END_FUN(SUCCESS);
}

// method = token
void	RequestParser::method(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		init_digest();
		token();
		digest(this->_method);
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		SET_ERROR;
		throw (Exceptions::ParserException("method expected"));
	}
	RESET_ERROR;
	END_FUN(SUCCESS);
}

// field_value = *( field_content / obs_fold )
void	RequestParser::field_value(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		while (1)
		{
			// try { field_content(); }
			// catch (std::exception & e) {}
			// try { obs_fold(); }
			// catch (std::exception & e) { break ; }
			try { field_char(); }
			catch (std::exception &) { break ; }
		}
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		SET_ERROR;
		throw (Exceptions::ParserException("field_value expected"));
	}
	RESET_ERROR;
	END_FUN(SUCCESS);
}

// field_name = token
void	RequestParser::field_name(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		token();
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		SET_ERROR;
		throw (Exceptions::ParserException("field_name expected"));
	}
	RESET_ERROR;
	END_FUN(SUCCESS);
}

// request_line = method SP request_target SP HTTP_version CRLF
void	RequestParser::request_line(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		method();
		SP();
		init_digest();
		request_target();
		digest(this->_resource);
		SP();
		HTTP_version();
		CRLF();
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		SET_ERROR;
		throw (e);
		// throw (Exceptions::ParserException("request_line expected"));
	}
	RESET_ERROR;
	END_FUN(SUCCESS);
}

// message_body = *OCTET
void	RequestParser::message_body(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		init_digest();
		if (this->_head != static_cast<size_t>(this->_bytes_read))
			this->_head = this->_bytes_read - 1;
		this->_body_size = this->_head - this->_head_last_digest;
		digest(this->_body);
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		SET_ERROR;
		throw (Exceptions::ParserException("message_body expected"));
	}
	RESET_ERROR;
	END_FUN(SUCCESS);
}

// header_field = field_name ":" OWS field_value OWS
void	RequestParser::header_field(void)
{START_FUN;
	std::string		key;
	std::string		value;
	SAVE_HEAD(0);
	try
	{
		init_digest();
		field_name();
		digest(key);
		CHAR(':');
		OWS();
		init_digest();
		field_value();
		digest(value);
		OWS();
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		SET_ERROR;
		throw (Exceptions::ParserException("header_field expected"));
	}
	// headers_iterator it = this->_header_fields.begin();
	// this->_header_fields.insert(it, std::pair<std::string, std::string>(key, value));
	this->_header_fields[key] = value;
	RESET_ERROR;
	END_FUN(SUCCESS);
}

// start_line = request_line
void	RequestParser::start_line(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		request_line();
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		SET_ERROR;
		throw (e);
		// throw (Exceptions::ParserException("start_line expected"));
	}
	RESET_ERROR;
	END_FUN(SUCCESS);
}

// HTTP_message = start_line *( header_field CRLF ) CRLF [ message_body ]
void	RequestParser::HTTP_message(void)
{START_FUN;
	SAVE_HEAD(0);
	try
	{
		start_line();
		while (1)
		{
			SAVE_HEAD(1);
			try { header_field(); CRLF(); }
			catch (std::exception & e) { LOAD_HEAD(1); break ; }
		}
		CRLF();
		SAVE_HEAD(1);
		try { message_body(); }
		catch (std::exception & e) { LOAD_HEAD(1); }
	}
	catch (std::exception & e)
	{
		LOAD_HEAD(0);
		END_FUN(FAILURE);
		SET_ERROR;
		throw (e);
		// throw (Exceptions::ParserException("HTTP_message expected"));
	}
	RESET_ERROR;
	END_FUN(SUCCESS);
}
