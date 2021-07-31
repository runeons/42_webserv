/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestParser.parser.class.cpp                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 19:36:15 by tharchen          #+#    #+#             */
/*   Updated: 2021/07/25 18:51:30 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <webserv.hpp>

//// parser

// CRLF = CR LF
void	RequestParser::CRLF(void)
{
	size_t	head_save = 0;

	try
	{
		head_save = this->_head;
		CR();
		LF();
	}
	catch (std::exception &) {
		this->_head = head_save;
		bc_s(); throw (LexerException("CRLF expected"));
	}
}

// OWS = *( SP / HTAB )
void	RequestParser::OWS(void)
{
	while (1)
	{
		try { SP(); }
		catch (std::exception &) {
			try { HTAB(); }
			catch (std::exception &) { return ; }
		}
	}
}

// dec_octet   = DIGIT                 ; 0-9
// 			/ 0x31-39 DIGIT         ; 10-99   ; 1-9 0-9
// 			/ "1" 2DIGIT            ; 100-199 ; "1" 0-9 0-9
// 			/ "2" 0x30-34 DIGIT     ; 200-249 ; "2" 0-4 0-9
// 			/ "25" 0x30-35          ; 250-255 ; "25" 0-5

void	RequestParser::dec_octet(void)
{
	size_t	head_save = 0;

	head_save = this->_head;
	try {
		DIGIT();
	} // 0-9
	catch (std::exception &) {
		this->_head = head_save;
		try {
			RANGE(0x31, 0x39); DIGIT();
		} // 1-9 0-9
		catch (std::exception &) {
			this->_head = head_save;
			try {
				CHAR('1'); DIGIT(); DIGIT();
			} // "1" 0-9 0-9
			catch (std::exception &) {
				this->_head = head_save;
				try {
					CHAR('2'); RANGE(0x30, 0x34); DIGIT();
				} // "2" 0-4 0-9
				catch (std::exception &) {
					this->_head = head_save;
					try {
						CHAR('2'); CHAR('5'); RANGE(0x30, 0x35);
					} // "25" 0-5
					catch (std::exception &) {
						this->_head = head_save;
						bc_s(); throw (LexerException("dec_octet expected"));
					}
				}
			}
		}
	}
}

// IPvFuture     = "v" 1*HEXDIG "." 1*( unreserved / sub_delims / ":" )
void	RequestParser::IPvFuture(void)
{
	size_t	head_save = 0;
	size_t	head_start = 0;

	head_start = this->_head;
	head_save = this->_head;
	try
	{
		CHAR('v');
		HEXDIG();
		while (1)
		{
			try { HEXDIG(); }
			catch (std::exception &) { break ; }
		}
		CHAR('.');
		head_save = this->_head;
		try { unreserved(); }
		catch (std::exception &) {
			this->_head = head_save;
			try { sub_delims(); }
			catch (std::exception &) {
				this->_head = head_save;
				try { CHAR(':'); }
				catch (std::exception & e) {
					this->_head = head_save;
					throw (LexerException(e.what()));
				}
			}
		}
		while (1)
		{
			try { unreserved(); }
			catch (std::exception &) {
				this->_head = head_save;
				try { sub_delims(); }
				catch (std::exception &) {
					this->_head = head_save;
					try { CHAR(':'); }
					catch (std::exception & e) {
						this->_head = head_save;
						break ;
					}
				}
			}
		}
	}
	catch (std::exception & e) {
		this->_head = head_start;
		throw (LexerException(e.what()));
	}
}

// h16           = 1*4( HEXDIG )
void	RequestParser::h16(void)
{
	size_t	head_start = 0;

	head_start = this->_head;
	try
	{
		HEXDIG();
		for (int i = 0; i < 3; i++)
		{
			try { HEXDIG(); }
			catch (std::exception &) { return ; }
		}
	}
	catch (std::exception & e)
	{
		this->_head = head_start;
		throw (LexerException(e.what()));
	}
}

// IPv4address = dec_octet "." dec_octet "." dec_octet "." dec_octet
void	RequestParser::IPv4address(void)
{
	size_t	head_start = 0;

	head_start = this->_head;
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
		this->_head = head_start;
		throw (LexerException(e.what()));
	}
}

// ls32          = ( h16 ":" h16 ) / IPv4address
void	RequestParser::ls32(void)
{
	size_t	head_start = 0;
	size_t	head_save = 0;

	head_start = this->_head;
	try
	{
		head_save = this->_head;
		try
		{
			h16();
			CHAR(':');
			h16();
		}
		catch (std::exception &)
		{
			this->_head = head_save;
			IPv4address();
		}
	}
	catch (std::exception & e)
	{
		this->_head = head_start;
		throw (LexerException(e.what()));
	}
}

// IPv6address =                            6( h16 ":" ) ls32
// 			/                       "::" 5( h16 ":" ) ls32
// 			/ [               h16 ] "::" 4( h16 ":" ) ls32
// 			/ [ *1( h16 ":" ) h16 ] "::" 3( h16 ":" ) ls32
// 			/ [ *2( h16 ":" ) h16 ] "::" 2( h16 ":" ) ls32
// 			/ [ *3( h16 ":" ) h16 ] "::"    h16 ":"   ls32
// 			/ [ *4( h16 ":" ) h16 ] "::"              ls32
// 			/ [ *5( h16 ":" ) h16 ] "::"              h16
// 			/ [ *6( h16 ":" ) h16 ] "::"

void	RequestParser::IPv6address(void)
{
	size_t	head_start = 0;
	size_t	head_save = 0;
	size_t	head_save2 = 0;
	size_t	head_save3 = 0;

	head_start = this->_head;
	try
	{
		head_save = this->_head;
		try
		{
			for (int i = 0; i < 6; i++)
			{
				h16();
				CHAR(':');
			}
			ls32();
		}
		catch (std::exception &)
		{
			this->_head = head_save;
			try
			{
				CHAR(':');
				CHAR(':');
				for (int i = 0; i < 5; i++)
				{
					h16();
					CHAR(':');
				}
				ls32();
			}
			catch (std::exception &)
			{
				this->_head = head_save;
				try
				{
					try
					{
						head_save2 = this->_head;
						h16();
					}
					catch (std::exception &) { this->_head = head_save2; }
					CHAR(':');
					CHAR(':');
					for (int i = 0; i < 4; i++)
					{
						h16();
						CHAR(':');
					}
					ls32();
				}
				catch (std::exception &)
				{
					this->_head = head_save;
					try
					{
						try
						{
							head_save2 = this->_head;
							try
							{
								for (int i = 0; i < 1; i++)
								{
									head_save3 = this->_head;
									h16();
									CHAR(':');
								}
							}
							catch (std::exception &) { this->_head = head_save3; }
							h16();
						}
						catch (std::exception &) { this->_head = head_save2; }
						CHAR(':');
						CHAR(':');
						for (int i = 0; i < 3; i++)
						{
							h16();
							CHAR(':');
						}
						ls32();
					}
					catch (std::exception &)
					{
						this->_head = head_save;
						try
						{
							try
							{
								head_save2 = this->_head;
								try
								{
									for (int i = 0; i < 2; i++)
									{
										head_save3 = this->_head;
										h16();
										CHAR(':');
									}
								}
								catch (std::exception &) { this->_head = head_save3; }
								h16();
							}
							catch (std::exception &) { this->_head = head_save2; }
							CHAR(':');
							CHAR(':');
							for (int i = 0; i < 2; i++)
							{
								h16();
								CHAR(':');
							}
							ls32();
						}
						catch (std::exception &)
						{
							this->_head = head_save;
							try
							{
								try
								{
									head_save2 = this->_head;
									try
									{
										for (int i = 0; i < 3; i++)
										{
											head_save3 = this->_head;
											h16();
											CHAR(':');
										}
									}
									catch (std::exception &) { this->_head = head_save3; }
									h16();
								}
								catch (std::exception &) { this->_head = head_save2; }
								CHAR(':');
								CHAR(':');
								for (int i = 0; i < 1; i++)
								{
									h16();
									CHAR(':');
								}
								ls32();
							}
							catch (std::exception &)
							{
								this->_head = head_save;
								try
								{
									try
									{
										head_save2 = this->_head;
										try
										{
											for (int i = 0; i < 4; i++)
											{
												head_save3 = this->_head;
												h16();
												CHAR(':');
											}
										}
										catch (std::exception &) { this->_head = head_save3; }
										h16();
									}
									catch (std::exception &) { this->_head = head_save2; }
									CHAR(':');
									CHAR(':');
									ls32();
								}
								catch (std::exception &)
								{
									this->_head = head_save;
									try
									{
										try
										{
											head_save2 = this->_head;
											try
											{
												for (int i = 0; i < 5; i++)
												{
													head_save3 = this->_head;
													h16();
													CHAR(':');
												}
											}
											catch (std::exception &) { this->_head = head_save3; }
											h16();
										}
										catch (std::exception &) { this->_head = head_save2; }
										CHAR(':');
										CHAR(':');
										h16();
									}
									catch (std::exception &)
									{
										this->_head = head_save;
										try
										{
											try
											{
												head_save2 = this->_head;
												try
												{
													for (int i = 0; i < 6; i++)
													{
														head_save3 = this->_head;
														h16();
														CHAR(':');
													}
												}
												catch (std::exception &) { this->_head = head_save3; }
												h16();
											}
											catch (std::exception &) { this->_head = head_save2; }
											CHAR(':');
											CHAR(':');
										}
										catch (std::exception & e)
										{
											this->_head = head_save;
											throw (LexerException(e.what()));
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
	catch (std::exception & e)
	{
		this->_head = head_start;
		throw (LexerException(e.what()));
	}
}

// segment_nz = 1*(pchar)
void	RequestParser::segment_nz(void)
{
	size_t	head_start = 0;

	head_start = this->_head;
	try
	{
		pchar();
		while (1)
		{
			try { pchar(); }
			catch (std::exception &) { break ; }
		}
	}
	catch (std::exception & e)
	{
		this->_head = head_start;
		throw (LexerException(e.what()));
	}
}

// reg_name = *( unreserved / pct_encoded / sub_delims )
void	RequestParser::reg_name(void)
{
	size_t	head_save = this->_head;
	while (1)
	{
		try { unreserved(); }
		catch (std::exception &)
		{
			this->_head = head_save;
			try { pct_encoded();}
			catch (std::exception &)
			{
				this->_head = head_save;
				try { sub_delims();}
				catch (std::exception &) { break ; }
			}
		}
	}
}

/*
	Salut le theo du matin, c'est le theo du soir :)

	bon, il faut check les head_save, quand une fonction qui utilise se system
	de save quit, il faut peut-etre reset le head a son origine pour que si la
	fonction appelante catch elle meme l'erreur et continue, elle ai bien un head
	au bon endroit.

	J'etais sur la fonction du dessous en train de check si j'avais bien mis les
	saves :) j'avais oublié de les mettre dans les fonction avec des ou.

	pense s'il te plait a bien recheck toute les fonction que j'ai codé cette
	nuit. La fatigue de la fin ma peut etre fait faire des erreurs.

	CHECK TOUT ! merci bb :) j'ai estimé le fichier a 1500 lignes a la fin. :p

	enjoy :D

*/

// IP_literal = "[" ( IPv6address / IPvFuture  ) "]"
void	RequestParser::IP_literal(void)
{
	size_t	head_start = 0;
	size_t	head_save = 0;

	head_start = this->_head;
	try
	{
		CHAR('[');
		head_save = this->_head;
		try { IPv6address(); }
		catch (std::exception &) {
			this->_head = head_save;
			try { IPvFuture(); }
			catch (std::exception & e) {
				this->_head = head_save;
				throw (LexerException(e.what()));
			}
		}
		CHAR(']');
	}
	catch (std::exception & e)
	{
		this->_head = head_start;
		throw (LexerException(e.what()));
	}
}

// path_rootless = segment_nz *( "/" segment )
void	RequestParser::path_rootless(void)
{
	size_t	head_start = 0;

	head_start = this->_head;
	try
	{
		segment_nz();
		while (1)
		{
			try
			{
				CHAR('/');
				segment();
			}
			catch (std::exception &) { break ; }
		}
	}
	catch (std::exception & e)
	{
		this->_head = head_start;
		throw (LexerException(e.what()));
	}
}

// path_absolute = "/" [ segment_nz *( "/" segment ) ]
// or -> path_absolute = "/" [ path_rootless ]
void	RequestParser::path_absolute(void)
{
	size_t	head_start = 0;

	head_start = this->_head;
	try
	{
		CHAR('/');
		try { path_rootless(); }
		catch (std::exception &) { }
	}
	catch (std::exception & e)
	{
		this->_head = head_start;
		throw (LexerException(e.what()));
	}
}

// path_abempty = *( "/" segment )
void	RequestParser::path_abempty(void)
{

	while (1)
	{
		try { CHAR('/'); segment(); }
		catch (std::exception &) { return ; }
	}
}

// pct_encoded = "%" HEXDIG HEXDIG
void	RequestParser::pct_encoded(void)
{
	size_t	head_start = 0;

	head_start = this->_head;
	try
	{
		CHAR('%');
		HEXDIG();
		HEXDIG();
	}
	catch (std::exception & e)
	{
		this->_head = head_start;
		throw (LexerException(e.what()));
	}
}

// unreserved = ALPHA / DIGIT / "-" / "." / "_" / "~"
void	RequestParser::unreserved(void)
{
	try { ALPHA(); }
	catch (std::exception &) {
		try { DIGIT(); }
		catch (std::exception &) {
			try { CHAR('-'); }
			catch (std::exception &) {
				try { CHAR('.'); }
				catch (std::exception &) {
					try { CHAR('_'); }
					catch (std::exception &) {
						try { CHAR('~'); }
						catch (std::exception &) {
							bc_s(); throw (LexerException("unreserved expected"));
						}
					}
				}
			}
		}
	}
}

// port = *DIGIT
void	RequestParser::port(void)
{
	while (1)
	{
		try { DIGIT(); }
		catch (std::exception &) { break ; }
	}
}

// host = IP_literal / IPv4address / reg_name
void	RequestParser::host(void)
{
	size_t	head_start = 0;

	head_start = this->_head;
	try { IP_literal(); }
	catch (std::exception &) {
		this->_head = head_start;
		try { IPv4address(); }
		catch (std::exception &) {
			this->_head = head_start;
			try { reg_name(); }
			catch (std::exception &) {
				this->_head = head_start;
				bc_s(); throw (LexerException("host expected"));
			}
		}
	}
}

// userinfo = *( unreserved / pct_encoded / sub_delims / ":" )
void	RequestParser::userinfo(void)
{
	size_t	head_start = 0;

	head_start = this->_head;
	while (1)
	{
		try { unreserved(); }
		catch (std::exception & e)
		{
			this->_head = head_start;
			try { pct_encoded(); }
			catch (std::exception & e)
			{
				this->_head = head_start;
				try { sub_delims(); }
				catch (std::exception & e)
				{
					this->_head = head_start;
					try { CHAR(':'); }
					catch (std::exception & e)
					{
						this->_head = head_start;
						break ;
					}
				}
			}
		}
	}
}

// hier_part = "//" [ authority / path_abempty / path_absolute / path_rootless ]
void	RequestParser::hier_part(void)
{
	size_t	head_start = 0;
	size_t	head_save = 0;

	head_start = this->_head;
	try
	{
		CHAR('/');
		CHAR('/');
		head_save = this->_head;
		try { authority(); }
		catch (std::exception & e)
		{
			this->_head = head_save;
			try { path_abempty(); }
			catch (std::exception & e)
			{
				this->_head = head_save;
				try { path_absolute(); }
				catch (std::exception & e)
				{
					this->_head = head_save;
					try { path_rootless(); }
					catch (std::exception & e)
					{ this->_head = head_save; }
				}
			}
		}
	}
	catch (std::exception &)
	{
		this->_head = head_start;
		bc_s(); throw (LexerException("hier_part expected"));
	}
}

// scheme = ALPHA *( ALPHA / DIGIT / "+" / "-" / "." )
void	RequestParser::scheme(void)
{
	size_t	head_start = 0;

	head_start = this->_head;
	try
	{
		ALPHA();
		while (1)
		{
			try { ALPHA(); }
			catch (std::exception & e) {
				try { DIGIT(); }
				catch (std::exception & e) {
					try { CHAR('+'); }
					catch (std::exception & e) {
						try { CHAR('-'); }
						catch (std::exception & e) {
							try { CHAR('.'); }
							catch (std::exception & e) { break ; }
						}
					}
				}
			}
		}
	}
	catch (std::exception & e)
	{
		this->_head = head_start;
		throw (LexerException(e.what()));
	}

}

// pchar = unreserved / pct_encoded / sub_delims / ":" / "@"
void	RequestParser::pchar(void)
{
	size_t	head_start = 0;

	head_start = this->_head;
	try { unreserved(); }
	catch (std::exception &) {
		this->_head = head_start;
		try { pct_encoded(); }
		catch (std::exception &) {
			this->_head = head_start;
			try { sub_delims(); }
			catch (std::exception &) {
				this->_head = head_start;
				try { CHAR(':'); }
				catch (std::exception &) {
					this->_head = head_start;
					try { CHAR('@'); }
					catch (std::exception &) {
						this->_head = head_start;
						bc_s(); throw (LexerException("pchar expected"));
					}
				}
			}
		}
	}
}


// segment = *pchar
void	RequestParser::segment(void)
{
	while (1)
	{
		try { pchar(); }
		catch (std::exception &) { break ; }
	}
}

// authority = [ userinfo "@" ] host [ ":" port ]
void	RequestParser::authority(void)
{
	size_t	head_start = 0;

	head_start = this->_head;
	try
	{
		try
		{
			userinfo();
			CHAR('@');
		}
		catch (std::exception &) {}
		host();
		try
		{
			CHAR(':');
			port();
		}
		catch (std::exception &) {}
	}
	catch (std::exception & e)
	{
		this->_head = head_start;
		throw (LexerException(e.what()));
	}
}

// absolute_URI  = scheme ":" hier_part [ "?" query ]
void	RequestParser::absolute_URI(void)
{
	size_t	head_start = 0;

	head_start = this->_head;
	try
	{
		scheme();
		CHAR(':');
		hier_part();
		try
		{
			CHAR('?');
			query();
		}
		catch (std::exception &) { }
	}
	catch (std::exception & e)
	{
		this->_head = head_start;
		throw (LexerException(e.what()));
	}
}

// query = *( pchar / "/" / "?" )
void	RequestParser::query(void)
{
	while (1)
	{
		try { pchar(); }
		catch (std::exception & e) {
			try { CHAR('/'); }
			catch (std::exception & e) {
				try { CHAR('?'); }
				catch (std::exception &) { break ; }
			}
		}
	}
}

// absolute_path = 1*( "/" segment )
void	RequestParser::absolute_path(void)
{
	size_t	head_start = 0;
	size_t	head_save = 0;

	head_start = this->_head;
	try
	{
		CHAR('/');
		segment();
		while (1)
		{
			head_save = this->_head;
			try
			{
				CHAR('/');
				segment();
			}
			catch (std::exception &) {
				this->_head = head_save;
				break ;
			}
		}
	}
	catch (std::exception & e)
	{
		this->_head = head_start;
		throw (LexerException(e.what()));
	}
}

// HTTP_name = 0x48.54.54.50 ; HTTP
void	RequestParser::HTTP_name(void)
{
	size_t	head_start = 0;

	head_start = this->_head;
	try
	{
		CHAR('H');
		CHAR('T');
		CHAR('T');
		CHAR('P');
	}
	catch (std::exception & e)
	{
		this->_head = head_start;
		throw (LexerException(e.what()));
	}
}

// asterisk_form = "*"
void	RequestParser::asterisk_form(void)
{
	size_t	head_start = 0;

	head_start = this->_head;
	try { CHAR('*'); }
	catch (std::exception & e)
	{
		this->_head = head_start;
		throw (LexerException(e.what()));
	}
}

// authority_form = authority
void	RequestParser::authority_form(void)
{
	size_t	head_start = 0;

	head_start = this->_head;
	try { authority(); }
	catch (std::exception & e)
	{
		this->_head = head_start;
		throw (LexerException(e.what()));
	}
}

// absolute_form = absolute_URI
void	RequestParser::absolute_form(void)
{
	size_t	head_start = 0;

	head_start = this->_head;
	try { absolute_URI(); }
	catch (std::exception & e)
	{
		this->_head = head_start;
		throw (LexerException(e.what()));
	}
}


// origin_form = absolute_path [ "?" query ]
void	RequestParser::origin_form(void)
{
	size_t	head_start = 0;

	head_start = this->_head;
	try
	{
		absolute_path();
		try
		{
			CHAR('?');
			query();
		}
		catch (std::exception &) { }
	}
	catch (std::exception & e)
	{
		this->_head = head_start;
		throw (LexerException(e.what()));
	}
}

// obs_fold = CRLF ( SP / HTAB ) OWS
void	RequestParser::obs_fold(void)
{
	size_t	head_start = 0;

	head_start = this->_head;
	try
	{
		CRLF();
		try { SP(); }
		catch (std::exception &) {
			try { HTAB(); }
			catch (std::exception &) { }
		}
		OWS();
	}
	catch (std::exception & e)
	{
		this->_head = head_start;
		throw (LexerException(e.what()));
	}
}

// field_vchar = VCHAR / obs_text
void	RequestParser::field_vchar(void)
{
	size_t	head_start = 0;

	head_start = this->_head;
	try { VCHAR(); }
	catch (std::exception &) {
		try { obs_text(); }
		catch (std::exception &)
		{
			this->_head = head_start;
			bc_s(); throw (LexerException("field_vchar expected"));
		}
	}
}

// field_content = field_vchar [ ( SP / HTAB ) OWS field_vchar ]
void	RequestParser::field_content(void)
{
	size_t	head_start = 0;

	head_start = this->_head;
	try
	{
		field_vchar();
		try
		{
			try { SP(); }
			catch (std::exception &) {
				try { HTAB(); }
				catch (std::exception &) { }
			}
			OWS();
			field_vchar();
		}
		catch (std::exception &) { }
	}
	catch (std::exception & e)
	{
		this->_head = head_start;
		throw (LexerException(e.what()));
	}
}

// token = 1*tchar
void	RequestParser::token(void)
{
	size_t	head_start = 0;

	head_start = this->_head;
	try
	{
		tchar();
		while (1)
		{
			try { tchar(); }
			catch (std::exception &) { break ; }
		}
	}
	catch (std::exception & e)
	{
		this->_head = head_start;
		throw (LexerException(e.what()));
	}
}

// HTTP_version = HTTP_name "/" DIGIT "." DIGIT
void	RequestParser::HTTP_version(void)
{
	size_t	head_start = 0;

	head_start = this->_head;
	try
	{
		HTTP_name();
		CHAR('/');
		init_digest();
		DIGIT();
		CHAR('.');
		DIGIT();
	}
	catch (std::exception & e)
	{
		this->_head = head_start;
		throw (LexerException(e.what()));
	}
	digest(this->_http_version);
}

// request_target = origin_form / absolute_form / authority_form / asterisk_form
void	RequestParser::request_target(void)
{
	size_t	head_start = 0;

	head_start = this->_head;
	init_digest();
	try { origin_form(); }
	catch (std::exception &) {
		this->_head = head_start;
		try { absolute_form(); }
		catch (std::exception &) {
			this->_head = head_start;
			try { authority_form(); }
			catch (std::exception &) {
				this->_head = head_start;
				try { asterisk_form(); }
				catch (std::exception &) {
					this->_head = head_start;
					bc_s(); throw (LexerException("request_target expected"));
				}
			}
		}
	}
	digest(this->_resource);
}

// method = token
void	RequestParser::method(void)
{
	size_t	head_start = 0;

	// debug_print_line();
	head_start = this->_head;
	init_digest();
	try { token(); }
	catch (std::exception & e)
	{
		this->_head = head_start;
		throw (LexerException(e.what()));
	}
	digest(this->_method);
}

// field_value = *( field_content / obs_fold )
void	RequestParser::field_value(void)
{
	// size_t	head_start = 0;

	while (1)
	{
		// head_start = this->_head;
		// try { field_content(); }
		// catch (std::exception &)
		// {
		// 	this->_head = head_start;
		// 	try { obs_fold(); }
		// 	catch (std::exception &) { break ; }
		// }
		try { field_char(); }
		catch (std::exception &) { break ; }
	}
}

// field_name = token
void	RequestParser::field_name(void)
{
	size_t	head_start = 0;

	head_start = this->_head;
	try { token(); }
	catch (std::exception & e)
	{
		this->_head = head_start;
		throw (LexerException(e.what()));
	}
}

// request_line = method SP request_target SP HTTP_version CRLF
void	RequestParser::request_line(void)
{
	size_t	head_start = 0;

	head_start = this->_head;
	try
	{
		method();
		SP();
		request_target();
		SP();
		HTTP_version();
		CRLF();
	}
	catch (std::exception & e)
	{
		this->_head = head_start;
		throw (LexerException(e.what()));
	}
}

// message_body = *OCTET
void	RequestParser::message_body(void)
{
	init_digest();
	this->_head = this->_bytes_read - 1;
	this->_body_size = this->_head - this->_head_last_digest;
	// while (1)
	// {
	// 	try { OCTET(); }
	// 	catch (std::exception &) { break ; }
	// }
	digest(this->_body);
}

// header_field = field_name ":" OWS field_value OWS
void	RequestParser::header_field(void)
{
	size_t	head_start = 0;
	std::string	key;
	std::string	value;

	head_start = this->_head;
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
		this->_head = head_start;
		throw (LexerException(e.what()));
	}
	// TOCHECK maybe push back entries instead of push front to keep order
	headers_iterator it = this->_header_fields.begin();
	this->_header_fields.insert (it, std::pair<std::string, std::string>(key, value));
}

// start_line = request_line
void	RequestParser::start_line(void)
{
	size_t	head_start = 0;

	head_start = this->_head;
	try { request_line(); }
	catch (std::exception & e)
	{
		this->_head = head_start;
		throw (LexerException(e.what()));
	}
}

// HTTP_message = start_line *( header_field CRLF ) CRLF [ message_body ]
void	RequestParser::HTTP_message(void)
{
	size_t	head_start = 0;
	size_t	head_save = 0;

	head_start = this->_head;
	try
	{
		start_line();
		while (1)
		{
			head_save = this->_head;
			try
			{
				header_field();
				CRLF();
			}
			catch (std::exception &) {
				this->_head = head_save;
				break ;
			}
		}
		CRLF();
		try { message_body(); }
		catch (std::exception &) { }
	}
	catch (std::exception & e)
	{
		this->_head = head_start;
		throw (LexerException(e.what()));
	}
}
