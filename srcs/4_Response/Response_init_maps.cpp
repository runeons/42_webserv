
# include <webserv.hpp>

// ********************************************* init maps *********************************************

std::string		Response::get_response_field_name(enum e_resp_fields field)
{
	switch (field) {
		case R_DATE				: return (std::string("Date"));
		case R_SERVER			: return (std::string("Server"));
		case R_CONNECTION		: return (std::string("Connection"));
		case R_CONTENT_LENGTH	: return (std::string("Content-Length"));
		case R_CONTENT_TYPE		: return (std::string("Content-Type"));
		case R_LOCATION			: return (std::string("Location"));
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
	m[R_LOCATION] = "";
	return m;
}

std::map<int, std::string>	Response::init_map_msg()
{
	std::map<int, std::string> m;

	m[200] = "OK"; 						// BOTH
	m[202] = "Accepted"; 						// BOTH
	m[204] = "No Content"; 						// RESP
	m[301] = "Moved Permanently"; 				// RESP
	m[307] = "Temporary Redirect"; 				// RESP
	m[400] = "Bad Request"; 				// REQ
	m[403] = "Forbidden"; 						// RESP
	m[404] = "Not Found"; 						// RESP
	m[405] = "Method Not Allowed";				// RESP
	m[408] = "Request Timeout"; 				// RESP
	m[409] = "Conflict";		 				// RESP
	m[411] = "Length Required";				// REQ
	m[413] = "Payload Too Large"; 			// REQ
	m[414] = "URI Too Long"; 				// REQ
	m[415] = "Unsupported Media Type";			// RESP
	m[500] = "Internal Server Error";	// BOTH
	m[501] = "Not Implemented";				// REQ
	m[505] = "HTTP Version Not Supported";	// REQ

	return m;
}

std::string Response::generate_error_page_content(int code)
{
	std::string page;

	(void)code;
	page = "<html class=\"no-js\" lang=\"en\"><head>\
			<meta charset=\"utf-8\">\
			<meta http-equiv=\"x-ua-compatible\" content=\"IE=edge,chrome=1\">\
			<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\
			<title>Error " + itos(code) + " - " + _error_msg[code] + " !</title>\
			<meta name=\"robots\" content=\"noindex\">\
			<link rel=\"stylesheet\" href=\"https://cdnjs.cloudflare.com/ajax/libs/twitter-bootstrap/3.3.7/css/bootstrap.min.css\">\
			<style>\
			h1.error {\
				margin-top: 1em;\
				font-size: 7em;\
				font-weight: 500;\
			}\
		</style>\
		<script src=\"https://cdnjs.cloudflare.com/ajax/libs/modernizr/2.8.3/modernizr.min.js\"></script>\
		</head>\
		<body>\
			<div class=\"container\">\
				<div class=\"row\">\
					<div class=\"col-md-10 col-md-offset-2\">\
						<h1 class=\"error\">Oops!</h1>\
						<h2>Error " + itos(code) + " - " + _error_msg[code] + "</h2>\
						<p class=\"lead\">[this is an automatically generated error page]</p>\
						<p class=\"lead\">Sorry.</p>\
						<a href=\"/\" class=\"btn btn-primary btn-md\"><span class=\"glyphicon glyphicon-home\"></span> Home </a>\
					</div>\
				</div>\
			</div>\
		</body>\
	</html>";
	return page;
}

std::map<int, std::string>	Response::init_map_body() // _error_content map
{
	std::map<int, std::string> m;
	std::map<int, std::string>::iterator it;

	std::map<int, std::string> m_config_errors_path = _config.get__error_pages();
	std::map<int, std::string>::iterator it_config;

	std::string path;

	for (it = _error_msg.begin(); it != _error_msg.end(); it++)
	{
		path = "";
		// va chercher le path dans la Config s'il y est
		for (it_config = m_config_errors_path.begin(); it_config != m_config_errors_path.end(); it_config++)
		{
			if (it_config->first == it->first)
			{
				path = m_config_errors_path[it->first];
			}
		}
		// sinon : path par défaut NB.html // A SUPPRIMER ? TOCHECK
		if (path.length() == 0)
			path = DIR_ERROR_PAGES + itos(it->first) + ".html";
		if (it->first != 200 && it->first != 202 && it->first != 204)
		{
			// recup content du path
			path = _config.get__root_dir() + "/" + path;
			m[it->first] = get_file_content(path.c_str());
			// si vide : genere
			if (m[it->first].length() == 0)
				m[it->first] = generate_error_page_content(it->first);
		}

	}
	return m;
}

// m[100] = "Continue";
// m[101] = "Switching Protocols";
// m[200] = "OK";
// m[201] = "Created";
// m[202] = "Accepted";
// m[203] = "Non-Authoritative Information";
// m[204] = "No Content";
// m[205] = "Reset Content";
// m[206] = "Partial Content";
// m[300] = "Multiple Choices";
// m[301] = "Moved Permanently";
// m[302] = "Found";
// m[303] = "See Other";
// m[304] = "Not Modified";
// m[305] = "Use Proxy";
// m[307] = "Temporary Redirect";
// m[400] = "Bad Request";
// m[401] = "Unauthorized";
// m[402] = "Payment Required";
// m[403] = "Forbidden";
// m[404] = "Not Found";
// m[405] = "Method Not Allowed";
// m[406] = "Not Acceptable";
// m[407] = "Proxy Authentication Required";
// m[408] = "Request Timeout";
// m[409] = "Conflict";
// m[410] = "Gone";
// m[411] = "Length Required";
// m[412] = "Precondition Failed";
// m[413] = "Payload Too Large";
// m[414] = "URI Too Long";
// m[415] = "Unsupported Media Type";
// m[416] = "Range Not Satisfiable";
// m[417] = "Expectation Failed";
// m[418] = "I'm a teapot";
// m[426] = "Upgrade Required";
// m[500] = "Internal Server Error";
// m[501] = "Not Implemented";
// m[502] = "Bad Gateway";
// m[503] = "Service Unavailable";
// m[504] = "Gateway Timeout";
// m[505] = "HTTP Version Not Supported";
