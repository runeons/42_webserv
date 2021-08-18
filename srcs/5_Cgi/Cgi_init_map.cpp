
# include <webserv.hpp>

std::string str_to_upper(std::string s)
{
	int	i;

	i = -1;
	while (s[++i])
		s[i] = std::toupper(s[i]);
	return s;
}

std::string reworked_http_header(std::string header)
{
	std::string s;

	s = str_to_upper(header);
	for (size_t i = 0; i < s.size(); i++)
	{
		if (s[i] == '-')
			s[i] = '_';
	}
	s = "HTTP_" + s;
	return s;
}

std::map<std::string, std::string>	Cgi::init_map_http()
{
	std::map<std::string, std::string>	m;
	std::map<std::string, std::string>	h = _request.get__header_fields();

	headers_iterator it = h.begin();
	for (; it != h.end(); it++)
		m[reworked_http_header(it->first)] = it->second;
	return m;
}

std::string	get_cwd(void)
{
	char cwd[256];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (std::string("./"));
	else
		return (std::string(cwd));
}

std::map<std::string, std::string>	Cgi::init_map_env()
{
	std::map<std::string, std::string>	m;

	// MUST for php-cgi
	m["REDIRECT_STATUS"]	= "200";		// nécessaire si utilise php-cgi
	// CONDITIONAL (RFC)
	m["CONTENT_LENGTH"]		= _request.get__header_value("Content-Length");				// if no body, MUST NOT be set
	m["CONTENT_TYPE"]		= _request.get__header_value("Content-Type");				// if no body, can be NULL
	// MUST (RFC)
	m["GATEWAY_INTERFACE"]	= "CGI/1.1";
	m["SERVER_PROTOCOL"]	= "HTTP/" + _request.get__http_version();
	m["REMOTE_ADDR"]		= _config.get__host();
	m["REQUEST_METHOD"]		= _request.get__method();
	m["SERVER_SOFTWARE"]	= _config.get__server_name();
	m["SERVER_NAME"]		= _config.get__server_name();
	m["SERVER_PORT"]		= _config.get__port();
	m["QUERY_STRING"]		= "";
	// paths
	m["DOCUMENT_ROOT"]		= get_cwd();

	std::string script;
	if (_type == CGI_UPLOAD)
	{
		std::cerr << C_DEBUG << "[ DEBUG ] " << C_RES << "CGI_UPLOAD" << std::endl;
		script = _request.get__resource();
		m["UPLOAD_DIR"]		= _applied_location.get__upload();
	}
	else if (_type == CGI_EXTENSION)
	{
		std::cerr << C_DEBUG << "[ DEBUG ] " << C_RES << "CGI_EXTENSION" << std::endl;
		script = "/cgi-bin/uppercase.php";
		m["QUERY_STRING"]	= _query_string;
	}
	m["PATH_INFO"]			= script;
	m["REQUEST_URI"]		= script;
	m["PATH_TRANSLATED"]	= _applied_location.get__root_loc() + script;
	m["SCRIPT_FILENAME"]	= _applied_location.get__root_loc() + script;
	m["SCRIPT_NAME"]		= _applied_location.get__root_loc() + script;
	m.insert(_map_http.begin(), _map_http.end());
	return m;
}
