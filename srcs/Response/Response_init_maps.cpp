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

std::string get_file_content(std::string filename)
{
	std::ifstream ifs(filename);
	std::ostringstream oss;

	if (!ifs)
	{
		std::cerr << RED << "Error get content : file does'nt exist" <<  C_RES << std::endl;
		return "";
	}
	else if (!oss) // EXCEPTION A CREER
	{
		std::cerr << RED << "Error get content : can't open ofstream" <<  C_RES << std::endl;
		return "";
	}
	else
	{
		std::cerr << GREEN_B << "OK get content : file found" <<  C_RES << std::endl;
		oss << ifs.rdbuf();
		ifs.close();
		return (oss.str());
	}
}

std::map<int, std::string>	Response::init_map_body()
{
	std::map<int, std::string> m;

	m[404] = get_file_content("./html/404.html");
	// m[404] = get_file_content("./html/404_no_img.html");
	m[500] = "<html><body><center><h1>Error 404: Not found</h1></center><p>Head back to <a href=\"/\">home page</a>.</p></body></html>";

	return m;
}

std::map<std::string, std::string>	Response::init_map_mimes()
{
	std::map<std::string, std::string> m;

	m["aac"] = "audio/aac";
	m["abw"] = "application/x-abiword";
	m["arc"] = "application/x-freearc";
	m["avi"] = "video/x-msvideo";
	m["azw"] = "application/vnd.amazon.ebook";
	m["bin"] = "application/octet-stream";
	m["bmp"] = "image/bmp";
	m["bz"] = "application/x-bzip";
	m["bz2"] = "application/x-bzip2";
	m["cda"] = "application/x-cdf";
	m["csh"] = "application/x-csh";
	m["css"] = "text/css";
	m["csv"] = "text/csv";
	m["doc"] = "application/msword";
	m["docx"] = "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
	m["eot"] = "application/vnd.ms-fontobject";
	m["epub"] = "application/epub+zip";
	m["gz"] = "application/gzip";
	m["gif"] = "image/gif";
	m["htm"] = "text/html";
	m["html"] = "text/html";
	m["ico"] = "image/vnd.microsoft.icon";
	m["ics"] = "text/calendar";
	m["jar"] = "application/java-archive";
	m["jpeg"] = "image/jpeg";
	m["jpg"] = "image/jpeg";
	m["js"] = "text/javascript";
	m["json"] = "application/json";
	m["jsonld"] = "application/ld+json";
	m["mid"] = "audio/midi audio/x-midi";
	m["midi"] = "audio/midi audio/x-midi";
	m["mjs"] = "text/javascript";
	m["mp3"] = "audio/mpeg";
	m["mp4"] = "video/mp4";
	m["mpeg"] = "video/mpeg";
	m["mpkg"] = "application/vnd.apple.installer+xml";
	m["odp"] = "application/vnd.oasis.opendocument.presentation";
	m["ods"] = "application/vnd.oasis.opendocument.spreadsheet";
	m["odt"] = "application/vnd.oasis.opendocument.text";
	m["oga"] = "audio/ogg";
	m["ogv"] = "video/ogg";
	m["ogx"] = "application/ogg";
	m["opus"] = "audio/opus";
	m["otf"] = "font/otf";
	m["png"] = "image/png";
	m["pdf"] = "application/pdf";
	m["php"] = "application/x-httpd-php";
	m["ppt"] = "application/vnd.ms-powerpoint";
	m["pptx"] = "application/vnd.openxmlformats-officedocument.presentationml.presentation";
	m["rar"] = "application/vnd.rar";
	m["rtf"] = "application/rtf";
	m["sh"] = "application/x-sh";
	m["svg"] = "image/svg+xml";
	m["swf"] = "application/x-shockwave-flash";
	m["tar"] = "application/x-tar";
	m["tif"] = "image/tiff";
	m["tiff"] = "image/tiff";
	m["ts"] = "video/mp2t";
	m["ttf"] = "font/ttf";
	m["txt"] = "text/plain";
	m["vsd"] = "application/vnd.visio";
	m["wav"] = "audio/wav";
	m["weba"] = "audio/webm";
	m["webm"] = "video/webm";
	m["webp"] = "image/webp";
	m["woff"] = "font/woff";
	m["woff2"] = "font/woff2";
	m["xhtml"] = "application/xhtml+xml";
	m["xls"] = "application/vnd.ms-excel";
	m["xlsx"] = "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
	m["xul"] = "application/vnd.mozilla.xul+xml";
	m["zip"] = "application/zip";
	m["7z"] = "application/x-7z-compressed";

/*
	// conditionals
	.xml	application/xml //if not readable from casual users (RFC 3023, section 3)
	.xml	text/xml //if readable from casual users (RFC 3023, section 3)"
	.3gp	video/3gpp
	.3gp	audio/3gpp //if it doesn't contain video
	.3g2	video/3gpp2
	.3g2	audio/3gpp2 // if it doesn't contain video"
*/
	return m;
}
