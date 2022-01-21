
//// lexer

ALPHA					= 0x41-5A / 0x61-7A
        ; A-Z / a-z

ALPHA_UPPER				= 0x41-5A
        ; A-Z

DIGIT					= 0x30-39
        ; 0-9

TDIGIT					= 0x31-39
        ; 1-9

LF						= 0x0A
        ; '\n'
        ; linefeed

SP						= 0x20
        ; ' '
        ; space

HTAB					= 0x09
        ; '\t'
        ; horizontal tab

CHAR					= 0x01-7F
        ; any 7-bit US-ASCII character,
        ; excluding NUL

//// parser

server_token			= 's' 'e' 'r' 'v' 'e' 'r'

host_token				= 'h' 'o' 's' 't'

port_token				= 'p' 'o' 'r' 't'

server_name_token		= 's' 'e' 'r' 'v' 'e' 'r' '_' 'n' 'a' 'm' 'e'

max_client_body_token	= 'm' 'a' 'x' '_' 'c' 'l' 'i' 'e' 'n' 't' '_' 'b' 'o' 'd' 'y'

root_token				= 'r' 'o' 'o' 't'

error_token				= 'e' 'r' 'r' 'o' 'r'

location_token			= 'l' 'o' 'c' 'a' 't' 'i' 'o' 'n'

uri_token				= 'u' 'r' 'i'

index_token				= 'i' 'n' 'd' 'e' 'x'

autoindex_token			= 'a' 'u' 't' 'o' 'i' 'n' 'd' 'e' 'x'

alias_token				= 'a' 'l' 'i' 'a' 's'

method_token			= 'm' 'e' 't' 'h' 'o' 'd'

upload_token			= 'u' 'p' 'l' 'o' 'a' 'd'

on_token				= 'o' 'n'

off_token				= 'o' 'f' 'f'

OWS						= *( SP / HTAB )

OWSON					= *( OWS / LF )

token					= 1*( ALPHA_UPPER )

dec_octet   			= DIGIT                 ; 0-9
						/ 0x31-39 DIGIT         ; 10-99   ; 1-9 0-9
						/ '1' 2DIGIT            ; 100-199 ; "1" 0-9 0-9
						/ '2' 0x30-34 DIGIT     ; 200-249 ; "2" 0-4 0-9
						/ '2' '5' 0x30-35       ; 250-255 ; "25" 0-5

port_no			= 1*4( DIGIT )                  ; 0-9999      ; 0-9 0-9 0-9 0-9
				/ 0x31-35 4( DIGIT )            ; 10000-59999 ; 1-5 0-9 0-9 0-9 0-9
				/ '6' 0x30-34 3( DIGIT )        ; 60000-64999 ; "6" 0-4 0-9 0-9 0-9
				/ '6' '5' 0x30-34 2( DIGIT )    ; 65000-65499 ; "65" 0-4 0-9 0-9
				/ '6' '5' '5' 0x30-32 DIGIT     ; 65500-65529 ; "655" 0-2 0-9
				/ '6' '5' '5' '3' 0x30-35       ; 65530-65535 ; "6553" 0-5

IPv4address		= dec_octet '.' dec_octet '.' dec_octet '.' dec_octet

unreserved		= ALPHA / DIGIT / '_' / '-' / '.' / '~'

name			= 1*( unreserved )

number			= TDIGIT *( DIGIT )

sub_delims		= '!' / '$' / '&' / '\'' / '(' / ')' / '*' / '+' / '='

pchar			= unreserved / sub_delims / ":" / "@"

segment_nz		= 1*( pchar )

segment			= *( pchar )

path			= [ '/' ] segment_nz *( '/' segment )

file			= path segment_nz

status_code		= 3( DIGIT )

item_error		= status_code OWSON ':' OWSON file OWSON ';'

index			= index_token OWSON ':' OWSON file OWSON ';'

uri				= uri_token OWSON ':' OWSON path OWSON ';'

root			= root_token OWSON ':' OWSON path OWSON ';'

autoindex		= autoindex_token OWSON ':' OWSON 1( on_token / off_token ) OWSON ';'

alias			= alias_token OWSON ':' OWSON '[' OWSON [ path OWSON *( ',' OWSON path ) OWSON ] ']'

method			= method_token OWSON ':' OWSON '[' OWSON [ token OWSON *( ',' OWSON token ) OWSON ] ']'

upload			= upload_token OWSON ':' OWSON 1( 1( on_token path ) / off_token ) OWSON ';'

item_location	= uri / root / index / autoindex / alias / method / upload

host			= host_token OWSON ':' OWSON IPv4address OWSON ';'

port			= port_token OWSON ':' OWSON port_no OWSON ';'

server_name		= server_name_token OWSON ':' OWSON name OWSON ';'

max_client_body	= max_client_body_token OWSON ':' OWSON number OWSON ';'

error			= error_token ':' OWSON '{' OWSON *( item_error OWSON ) '}'

location		= location_token ':' OWSON '{' OWSON *( item_location OWSON ) '}'

item			= host / port / server_name / root / max_client_body / error / location

server			= server_token OWSON ':' OWSON '{' OWSON *( item OWSON ) '}'

config			= OWSON 1*( server OWSON )
