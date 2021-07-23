# include "Response.hpp"

// ********************************************* generate_response_header *********************************************

std::string Response::generate_status_line(void)
{
	std::map<int, std::string>::iterator it_msg = _error_msg.find(_status_code);

	// sl = "HTTP/" + _request_parser->get__http_version() + PAT_SP + itos(_status_code) + PAT_SP + it_msg->second + PAT_CRLF;
	return ("HTTP/1.1 " + itos(_status_code) + PAT_SP + it_msg->second + PAT_CRLF);
}

std::string		Response::formatted_header_response(enum e_resp_fields field)
{
	return (get_response_field_name(field) + PAT_DDOT + PAT_SP + _headers_response[field] + PAT_CRLF);
}

std::string		Response::r_header_server()
{
	_headers_response[R_SERVER] = SERVER_NAME;
	return (formatted_header_response(R_SERVER));
}

//Sun, 06 Nov 1994 08:49:37 GMT
std::string		Response::r_header_date()
{
	time_t		rawtime;
	struct tm	*timeinfo;
	char		buffer[MAX_DATE];

	time(&rawtime);
	timeinfo = gmtime(&rawtime);
	strftime(buffer, MAX_DATE, "%a, %d %h %G %X GMT", timeinfo);
	_headers_response[R_DATE] = buffer;
	return (formatted_header_response(R_DATE));
}

std::string		Response::r_header_connection()
{
	_headers_response[R_CONNECTION] = "close"; // à vérifier
	return (formatted_header_response(R_CONNECTION));
}

std::string		Response::r_header_content_length()
{
	if (_response_body.length())
		_headers_response[R_CONTENT_LENGTH] = itos(_response_body.length());
	else
		_headers_response[R_CONTENT_LENGTH] = "None";
	return (formatted_header_response(R_CONTENT_LENGTH));
}

std::string		Response::get_extension(std::string path)
{
	size_t pos;
	std::string sub;
	pos = path.rfind("/");
	sub = path.substr(pos + 1, path.length() - (pos + 1));
	pos = sub.rfind(".");
	if (pos == std::string::npos)
		return ("");
	else
		return (sub.substr(pos + 1, sub.length() - (pos + 1)));
}

std::string		Response::get_mime_type(std::string path)
{
	if (_mime_types[get_extension(path)] == "")
		return _mime_types["html"];
	return _mime_types[get_extension(path)];
}

std::string		Response::r_header_content_type()
{
	_headers_response[R_CONTENT_TYPE] = get_mime_type(_full_path) + "; charset=utf-8";
	// _headers_response[R_CONTENT_TYPE] = get_mime_type(_full_path);
	return (formatted_header_response(R_CONTENT_TYPE));
}

void		Response::generate_response_header(void)
{
	_response_header = generate_status_line();
	_response_header += r_header_server();
	_response_header += r_header_date();
	_response_header += r_header_connection();
	_response_header += r_header_content_length();
	_response_header += r_header_content_type();

	return ;
}
