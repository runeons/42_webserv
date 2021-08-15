#include "utils.hpp"

unsigned int stringToIp(std::string ip) //return in Little-Endian
{
	unsigned char	v[4];
	size_t			pos(0);
	size_t			start(0);

	for (int i = 0; i < 3; ++i)
	{
		pos = ip.find_first_of('.', start);
		if (pos != std::string::npos)
		{
			v[i] = atoi(ip.substr(start, pos - start).c_str());
			start = pos + 1;			
		}
	}
	v[3] = atoi(ip.substr(start, pos).c_str());
	
	return (v[3] << 24 | v[2] << 16 | v[1] << 8 | v[0]);
}

std::string ipToString(unsigned int ip)
{
	unsigned char		v[4];
	std::ostringstream	os;

	for (int i = 0; i < 4; ++i)
	{
		v[i] = (ip >> (i * 8)) & 0xFF;
	}

	for (int i = 0; i < 3; ++i)
	{
		os << static_cast<int>(v[i]);
		os << '.'; 
	}
	os << static_cast<int>(v[3]);

	return (os.str());
}

static unsigned short	ft_bswap_16(unsigned short port)
{
	port = (port >> 8) | (port << 8);
	return (port);
}

unsigned short	ft_htons(unsigned short port)
{
	if (BYTE_ORDER == BIG_ENDIAN)
		return (port);
	else if (BYTE_ORDER == LITTLE_ENDIAN)
		return (ft_bswap_16(port));
	return (0);
}

unsigned short	ft_ntohs(unsigned short port)
{
	return ft_htons(port);
}
