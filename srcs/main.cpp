# include "webserv.hpp"


int main(void)
{
	Server server;

	if (server.launch())
		return (-1);

	return 0;
}
