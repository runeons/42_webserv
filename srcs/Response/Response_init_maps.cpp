# include "Response.hpp"

// ********************************************* init maps *********************************************

std::string		Response::get_response_field_name(enum e_resp_fields field)
{
	switch (field) {
		case R_DATE				: return (std::string("Date"));
		case R_SERVER			: return (std::string("Server"));
		case R_CONNECTION		: return (std::string("Connection"));
		case R_CONTENT_LENGTH	: return (std::string("Content-Length"));
		case R_CONTENT_TYPE		: return (std::string("Content-Type"));
		default					: return (std::string("None"));
	}
}

std::map<int, std::string>	Response::init_map_headers()
{
	std::map<int, std::string> m;

	m[R_DATE] = "";
	m[R_SERVER] = "";
	m[R_CONNECTION] = "";
	m[R_CONTENT_LENGTH] = "";
	m[R_CONTENT_TYPE] = "";
	return m;
}

std::map<int, std::string>	Response::init_map_msg()
{
	std::map<int, std::string> m;

	m[100] = "Continue";
	m[101] = "Switching Protocols";
	m[200] = "OK";
	m[201] = "Created";
	m[202] = "Accepted";
	m[203] = "Non-Authoritative Information";
	m[204] = "No Content";
	m[205] = "Reset Content";
	m[206] = "Partial Content";
	m[300] = "Multiple Choices";
	m[301] = "Moved Permanently";
	m[302] = "Found";
	m[303] = "See Other";
	m[304] = "Not Modified";
	m[305] = "Use Proxy";
	m[307] = "Temporary Redirect";
	m[400] = "Bad Request";
	m[401] = "Unauthorized";
	m[402] = "Payment Required";
	m[403] = "Forbidden";
	m[404] = "Not Found";
	m[405] = "Method Not Allowed";
	m[406] = "Not Acceptable";
	m[407] = "Proxy Authentication Required";
	m[408] = "Request Timeout";
	m[409] = "Conflict";
	m[410] = "Gone";
	m[411] = "Length Required";
	m[412] = "Precondition Failed";
	m[413] = "Payload Too Large";
	m[414] = "URI Too Long";
	m[415] = "Unsupported Media Type";
	m[416] = "Range Not Satisfiable";
	m[417] = "Expectation Failed";
	m[418] = "I'm a teapot";
	m[426] = "Upgrade Required";
	m[500] = "Internal Server Error";
	m[501] = "Not Implemented";
	m[502] = "Bad Gateway";
	m[503] = "Service Unavailable";
	m[504] = "Gateway Timeout";
	m[505] = "HTTP Version Not Supported";

	return m;
}

std::map<int, std::string>	Response::init_map_body()
{
	std::map<int, std::string> m;

	m[404] = "<html><body><center><h1>Error 404: Not found</h1></center><p>Head back to <a href=\"/\">home page</a>.</p></body></html>";

	return m;
}
