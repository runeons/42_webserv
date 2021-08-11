
#include <webserv.hpp>

std::vector<std::string> RequestParser::init_methods_implemented(void)
{
	std::vector<std::string> v;

	v.push_back("GET");
	v.push_back("POST");
	v.push_back("DELETE");
	return (v);
}

std::vector<std::string> RequestParser::init_methods_unimplemented(void)
{
	std::vector<std::string> v;

	v.push_back("COPY");
	v.push_back("OPTIONS");
	v.push_back("HEAD");
	v.push_back("LINK");
	v.push_back("MOVE");
	v.push_back("PUT");
	v.push_back("PATCH");
	v.push_back("TRACE");
	v.push_back("UNLINK");
	v.push_back("WRAPPED");
	return (v);
}
