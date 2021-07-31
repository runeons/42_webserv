# include <webserv.hpp>

std::map<int, std::string>		Config::init_map_error_pages()
{
	std::map<int, std::string> m;

	m[404] = _root_dir + "error_pages/404_default.html";
	m[500] = _root_dir + "error_pages/500_default.html";
	return m;
}

std::map<std::string, Location *>		Config::init_map_locations()
{
	std::map<std::string, Location *> m;
	std::vector<std::string> v_methods;
	std::vector<std::string> v_upload;
	std::vector<std::string> v_alias;

	std::string arr_methods[] = {"GET", "POST", "DELETE"};
	for (size_t i = 0; i < sizeof(arr_methods)/sizeof(*arr_methods); i++)
		v_methods.push_back(arr_methods[i]);

	std::string arr_upload[] = {"html/uploads/"};
	for (size_t i = 0; i < sizeof(arr_upload)/sizeof(*arr_upload); i++)
		v_upload.push_back(arr_upload[i]);

	std::string arr_alias[] = {"/home"};
	for (size_t i = 0; i < sizeof(arr_alias)/sizeof(*arr_alias); i++)
		v_alias.push_back(arr_alias[i]);

	m["/"] = new Location("/", "./html/", 1, v_methods, v_upload, v_alias);

	v_methods.clear();
	v_methods.push_back("POST");
	v_alias.pop_back();
	v_alias.push_back("/docs");
	m["/documents"] = new Location("/documents", "./html/documents", 1, v_methods, v_upload, v_alias);
	return m;
}
