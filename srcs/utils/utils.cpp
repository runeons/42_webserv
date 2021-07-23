#include "webserv.hpp"

// ********************************************* utils *********************************************

std::string itos(int nb)
{
	std::stringstream ss;

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
		std::cerr << RED << "Error oss : can't open ofstream" <<  C_RES << std::endl; // EXCEPTION A CREER
	for (size_t i = 0; i < s.length(); ++i)
	{
		oss << int_to_binary(s[i]);

		// if (i % 6 == 0 && i != 0) // controle le format d'impression
			// oss << std::endl;
	}
	return oss.str();
}

std::string binary_to_string(std::string s)
{
	std::string ret;
	std::ostringstream oss;
	char	parsed = 0;
	int		j = 0;

	if (!oss)
		std::cerr << RED << "Error oss : can't open ofstream" <<  C_RES << std::endl; // EXCEPTION A CREER
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
