#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

int		error(std::string msg)
{
	std::cerr << "Error : " << msg << std::endl;
	return (-1);
};

std::string get_file(const char * & filename)
{
	std::string	str;
	std::ifstream ifs(filename);
	std::ostringstream oss;

	if (!ifs)
	{
		error("file does'nt exist");
		throw (-1);
	}
	if (!oss)
	{
		error("can't open ofstream");
		throw (-1);
	}
	oss << ifs.rdbuf();
	ifs.close();
	str = oss.str();
	return (str);
}

void	replace_all(std::string& str, const std::string s1, const std::string s2)
{
	while (1)
	{
		int pos = str.find(s1);

		if (pos < 0)
			break;
		str.replace(pos, s1.length(), s2);
	}
}

void	fill_file(std::string(filename), std::string str)
{
	std::ofstream ofs((filename + ".replace").c_str());
	if (!ofs)
	{
		error("can't open ofstream");
		throw (-1);
	}
	ofs << str;
	ofs.close();
	return ;
}

int		main(int ac, char *av[])
{
	if (ac != 4)
		return (error("arguments"));

	const char * filename = av[1];
	const std::string s1 = av[2];
	const std::string s2 = av[3];

	if (s1.length() == 0 || s2.length() == 0)
		return (error("empty string"));

	try
	{
		std::string	str = get_file(filename);
		replace_all(str, s1, s2);
		fill_file(std::string(filename), str);
	}
	catch (int errnb)
	{
		return (-1);
	}
	return (0);
}