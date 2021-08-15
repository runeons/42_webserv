
# include <webserv.hpp>

// ********************************************* status line *********************************************

std::string Response::generate_status_line(void)
{
	std::map<int, std::string>::iterator it_msg = _error_msg.find(_status_code);

	return ("HTTP/1.1 " + itos(_status_code) + PAT_SP + it_msg->second + PAT_CRLF);
}

// ********************************************* headers utils *********************************************

std::string		Response::formatted_header_response(enum e_resp_fields field)
{
	return (get_response_field_name(field) + PAT_DDOT + PAT_SP + _headers_response[field] + PAT_CRLF);
}

// ********************************************* Server *********************************************

std::string		Response::r_header_server()
{
	_headers_response[R_SERVER] = _config.get__server_name();
	// _headers_response[R_SERVER] = SERVER_NAME;
	return (formatted_header_response(R_SERVER));
}

// ********************************************* Date *********************************************

std::string		Response::r_header_date()
{
	time_t		rawtime;
	struct tm	*timeinfo;
	char		buffer[MAX_DATE];

	time(&rawtime);
	timeinfo = gmtime(&rawtime);
	strftime(buffer, MAX_DATE, "%a, %d %h %G %X GMT", timeinfo); // Sun, 06 Nov 1994 08:49:37 GMT
	_headers_response[R_DATE] = buffer;
	return (formatted_header_response(R_DATE));
}

// ********************************************* Connection *********************************************

std::string		Response::r_header_connection()
{
	_headers_response[R_CONNECTION] = "close"; // TOCHECK
	_headers_response[R_CONNECTION] = "Keep-Alive"; // TOCHECK
	return (formatted_header_response(R_CONNECTION));
}

// ********************************************* Content-Length *********************************************

std::string		Response::r_header_content_length()
{
	if (_response_body.length())
		_headers_response[R_CONTENT_LENGTH] = itos(_response_body.length());
	else
		_headers_response[R_CONTENT_LENGTH] = "None";
	return (formatted_header_response(R_CONTENT_LENGTH));
}

// ********************************************* Content-Length *********************************************

std::string		Response::r_header_location()
{
	if (_status_code == 301)
	{
		_headers_response[R_LOCATION] = _applied_location.get__redir301();
		return (formatted_header_response(R_LOCATION));
	}
	else
		return "";
}

// ********************************************* Content-Type *********************************************

std::string		Response::r_header_content_type()
{
	_headers_response[R_CONTENT_TYPE] = _type_mime + "; charset=" + _charset;
	return (formatted_header_response(R_CONTENT_TYPE));
}
