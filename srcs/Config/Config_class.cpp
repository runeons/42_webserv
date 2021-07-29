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

	// m["/"] =
	return m;
}
