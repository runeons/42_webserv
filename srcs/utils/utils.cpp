
# include <webserv.hpp>

// ********************************************* exec_cmd *********************************************

std::string		exec_cmd(std::string cmd, std::string file_res)
{
	std::ostringstream oss;

	cmd += " > ";
	cmd += file_res;
	if (!oss) // EXCEPTION A CREER
		std::cerr << C_ERROR << "Error : can't open osstream" <<  C_RES << std::endl;
	int status = std::system(cmd.c_str());
	if (WEXITSTATUS(status) != 0)
		std::cerr << C_ERROR << "Error : can't exec cmd " << cmd <<  C_RES << std::endl; // EXCEPTION
	oss << std::ifstream(file_res.c_str()).rdbuf();
	return oss.str();
}

// ********************************************* file manip *********************************************

std::string		get_extension(std::string path)
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

std::string get_file_content(std::string filename)
{
	std::ifstream ifs(filename.c_str());
	std::ostringstream oss;

	if (!ifs)
	{
		// std::cerr << C_DEBUG << "[ DEBUG ] " << C_RES << "error ifs get_file_content : " << filename << std::endl;
		// std::cerr << C_DEBUG << "[ DEBUG ] " << C_RES << strerror(errno) << std::endl;
		return "";
	}
	else if (!oss)
	{
		// std::cerr << C_DEBUG << "[ DEBUG ] " << C_RES << "error oss get_file_content" << std::endl;
		return "";
	}
	else
	{
		oss << ifs.rdbuf();
		ifs.close();
		return (oss.str());
	}
}

// ********************************************* permissions *********************************************

// perm[1] = ((s.st_mode & S_IRUSR) ? 'r' : '-');
// perm[2] = ((s.st_mode & S_IWUSR) ? 'w' : '-');
// perm[3] = ((s.st_mode & S_IXUSR) ? sbit(s.st_mode) : '-');
// perm[4] = ((s.st_mode & S_IRGRP) ? 'r' : '-');
// perm[5] = ((s.st_mode & S_IWGRP) ? 'w' : '-');
// perm[6] = ((s.st_mode & S_IXGRP) ? sbit(s.st_mode) : '-');
// perm[7] = ((s.st_mode & S_IROTH) ? 'r' : '-');
// perm[8] = ((s.st_mode & S_IWOTH) ? 'w' : '-');
// perm[9] = ((s.st_mode & S_IXOTH) ? sbit(s.st_mode) : '-');

int		isfile_exist(std::string file)
{
	struct stat perm;
	if (::lstat(file.c_str(), &perm) == -1)
		return 0;
	else	
		return 1;
}

int		user_perm_to_write(std::string file)
{
	struct stat perm;
	if (::lstat(file.c_str(), &perm) == -1)
		std::cout << C_ERROR << "lstat user_perm_to_write error : " << strerror(errno) << C_RES << std::endl;
	if (perm.st_mode & S_IWUSR)
		return 1;
	else
		return 0;
}

int		user_perm_to_read(std::string file)
{
	struct stat perm;
	if (::lstat(file.c_str(), &perm) == -1)
		std::cout << C_ERROR << "lstat user_perm_to_read error : " << strerror(errno) << C_RES << std::endl;
	if (perm.st_mode & S_IRUSR)
		return 1;
	else
		return 0;
}

int		user_perm_to_exec(std::string file)
{
	struct stat perm;
	if (::lstat(file.c_str(), &perm) == -1)
		std::cout << C_ERROR << "lstat user_perm_to_exec error : " << strerror(errno) << C_RES << std::endl;
	if (perm.st_mode & S_IXUSR)
		return 1;
	else
		return 0;
}

// ********************************************* binary conversion *********************************************

std::string itos(int nb)
{
	std::stringstream ss;

	if (!ss)
	{
		std::cout << C_ERROR << "Error in itos" << std::endl << C_RES;
		return "";
	}
	ss << nb;
	return ss.str();
}

std::string int_to_binary(int n)
{
    std::string r;

    while (n != 0)
	{
        r += ( n % 2 == 0 ? "0" : "1" );
        n /= 2;
    }
	std::reverse(r.begin(), r.end());
	while (r.length() < 8)
		r = "0" + r;
    return r;
}

std::string string_to_binary(std::string s)
{
	std::ostringstream oss;

	if (!oss)
		return "";
	for (size_t i = 0; i < s.length(); ++i)
		oss << int_to_binary(s[i]);
	return oss.str();
}

std::string binary_to_string(std::string s)
{
	std::string ret;
	std::ostringstream oss;
	char	parsed = 0;
	int		j = 0;

	if (!oss)
		return "";
	for (size_t i = 0; i < s.length(); ++i)
	{
		parsed = 0;
		j = 0;
		for (int j = 0; j < 8; j++)
		{
			if (s[j] == '1') {
				parsed |= 1 << (7 - j);
			}
		}
		oss << parsed;
		s.erase(0, 8);
		i = 0;
	}
	return oss.str();
}

void	print_char_printf(char c)
{
	if (c == '\r')
		dprintf(1, "\\r");
	else if (c == '\n')
		dprintf(1, "\\n");
	else if (c == '\t')
		dprintf(1, "\\t");
	else if (c == '\0')
		dprintf(1, "\\0");
	else if (c == '\v')
		dprintf(1, "\\v");
	else if (c == '\f')
		dprintf(1, "\\f");
	else if (c == '\a')
		dprintf(1, "\\a");
	else if (c == '\b')
		dprintf(1, "\\b");
	else if (c == '\e')
		dprintf(1, "\\e");
	else
		dprintf(1, "%c", c);
}

void	print_char(char c)
{
	if (c == '\r')
		std::cout << "\\r";
	else if (c == '\n')
		std::cout << "\\n";
	else if (c == '\t')
		std::cout << "\\t";
	else if (c == '\0')
		std::cout << "\\0";
	else if (c == '\v')
		std::cout << "\\v";
	else if (c == '\f')
		std::cout << "\\f";
	else if (c == '\a')
		std::cout << "\\a";
	else if (c == '\b')
		std::cout << "\\b";
	else if (c == '\e')
		std::cout << "\\e";
	else
		std::cout << c;
}

void	print_string_formatted(std::string & s)
{
	for (size_t i = 0; s[i]; i++)
		print_char(s[i]);
}

void	print_string_formatted(std::string & s, size_t size)
{
	for (size_t i = 0; i < size; i++)
		print_char(s[i]);
}

