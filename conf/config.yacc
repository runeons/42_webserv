
//// lexer

ALPHA = 0x41-5A / 0x61-7A
                    ; A-Z / a-z

DIGIT = 0x30-39
                    ; 0-9

TDIGIT = 0x31-39
                    ; 1-9

LF = 0x0A
                    ; '\n'
                    ; linefeed

SP = 0x20
                    ; ' '
                    ; space

HTAB = 0x09
                    ; '\t'
                    ; horizontal tab

CHAR = 0x01-7F
                    ; any 7-bit US-ASCII character,
                    ; excluding NUL

//// parser

OWS = *(SP / HTAB)

OWSON = *(OWS / LF)

server_token = 's' 'e' 'r' 'v' 'e' 'r'

host_token = 'h' 'o' 's' 't'

port_token = 'p' 'o' 'r' 't'

server_name_token = 's' 'e' 'r' 'v' 'e' 'r' '_' 'n' 'a' 'm' 'e'

max_client_body_token = 'm' 'a' 'x' '_' 'c' 'l' 'i' 'e' 'n' 't' '_' 'b' 'o' 'd' 'y'

root_token = 'r' 'o' 'o' 't'

error_token = 'e' 'r' 'r' 'o' 'r'

location_token = 'l' 'o' 'c' 'a' 't' 'i' 'o' 'n'


dec_octet   = DIGIT                 ; 0-9
			/ 0x31-39 DIGIT         ; 10-99   ; 1-9 0-9
			/ '1' 2DIGIT            ; 100-199 ; "1" 0-9 0-9
			/ '2' 0x30-34 DIGIT     ; 200-249 ; "2" 0-4 0-9
			/ '2' '5' 0x30-35       ; 250-255 ; "25" 0-5

IPv4address = dec_octet '.' dec_octet '.' dec_octet '.' dec_octet

port = *DIGIT

unreserved = ALPHA / DIGIT / '_' / '-' / '.' / '~'

name = 1*(unreserved)

number = TDIGIT *(DIGIT)

sub_delims = "!" / "$" / "&" / "'" / "(" / ")" / "*" / "+" / "," / ";" / "="

pchar = unreserved / sub_delims / ":" / "@"

segment = *pchar

segment_nz = 1*(pchar)

path_rootless = segment_nz *( "/" segment )

b_host = host_token OWSON ':' OWSON IPv4address OWSON ';'

b_port = port_token OWSON ':' OWSON port OWSON ';'

b_server_name = server_name_token OWSON ':' OWSON name OWSON ';'

b_max_client_body = max_client_body_token OWSON ':' OWSON number OWSON ';'

b_root = root_token OWSON ':' OWSON path_rootless OWSON ';'

b_error = error_token ':' OWSON '{' OWSON  OWSON '}'

b_location = location_token ':' OWSON '{' OWSON  OWSON '}'

blocs = b_host OWSON b_port OWSON b_server_name OWSON b_root OWSON b_max_client_body OWSON b_error OWSON 1*(b_location OWSON)

server = server_token OWSON ':' OWSON  '{' OWSON blocs OWSON '}'

config = OWSON 1*(server OWSON)
