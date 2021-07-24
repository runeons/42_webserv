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

std::string		Response::r_header_date()
{
	time_t		rawtime;
	struct tm	*timeinfo;
	char		buffer[MAX_DATE];

	time(&rawtime);
	timeinfo = gmtime(&rawtime);
	//Sun, 06 Nov 1994 08:49:37 GMT
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
		_headers_response[R_CONTENT_LENGTH] = itos(_response_body.length()); // should be binary length when appropriate ?
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

std::string		Response::exec_cmd(std::string cmd)
{
	std::ostringstream oss;


	if (!oss) // EXCEPTION A CREER
		std::cerr << RED << "Error : can't open ofstream" <<  C_RES << std::endl;
	int status = std::system(cmd.c_str());
	if (WEXITSTATUS(status) != 0)
		std::cerr << RED << "Error : can't exec cmd " << cmd <<  C_RES << std::endl; // EXCEPTION
	oss << std::ifstream("test.txt").rdbuf();
	return oss.str();
}
//
// std::string		Response::get_mime_type(std::string path)
// {
// 	if (_mime_types[get_extension(path)] == "")
// 		return _mime_types["html"];
// 	return _mime_types[get_extension(path)];
// 	// and charset ??
// }

void		Response::retrieve_type_mime_charset(std::string str)
{
	unsigned first = str.find(":") + 2;
	unsigned last = str.find(";");

	if (_status_code == 404 || last > str.length()) // si "cannot open file"
	{
		_type_mime = "text/html";
		_charset = "utf-8";
		return ;
	}
	_type_mime = str.substr(first, last - first);
	first = str.find("=") + 1;
	last = str.find("\n");
	_charset = str.substr(first, last - first);
}


std::string		Response::r_header_content_type()
{
	std::string cmd;
	cmd = "file --mime " + _full_path + " > test.txt";
	retrieve_type_mime_charset(exec_cmd(cmd.c_str()));
	// AJOUTER : si couldn't exec file => utiliser get_mime_type ?
	_headers_response[R_CONTENT_TYPE] = _type_mime + "; charset=" + _charset;
	return (formatted_header_response(R_CONTENT_TYPE));
}
