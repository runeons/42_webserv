/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantoni <tsantoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 18:41:57 by tsantoni          #+#    #+#             */
/*   Updated: 2021/07/31 14:55:55 by tsantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <webserv.hpp>

// ********************************************* exec_cmd *********************************************

std::string		exec_cmd(std::string cmd, std::string file_res)
{
	std::ostringstream oss;

	cmd += " > ";
	cmd += file_res;
	if (!oss) // EXCEPTION A CREER
		std::cerr << RED << "Error : can't open osstream" <<  C_RES << std::endl;
	int status = std::system(cmd.c_str());
	if (WEXITSTATUS(status) != 0)
		std::cerr << RED << "Error : can't exec cmd " << cmd <<  C_RES << std::endl; // EXCEPTION
	oss << std::ifstream(file_res).rdbuf();
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
	std::ifstream ifs(filename);
	std::ostringstream oss;

	if (!ifs)
		return "";
	else if (!oss)
		return "";
	else
	{
		oss << ifs.rdbuf();
		ifs.close();
		return (oss.str());
	}
}

// ********************************************* binary conversion *********************************************

std::string itos(int nb)
{
	std::stringstream ss;

	if (!ss)
	{
		std::cout << RED << "Error in itos" << std::endl << C_RES;
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
	reverse(r.begin(), r.end());
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
