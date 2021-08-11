
# include <webserv.hpp>

# define SBOOL(X) (X ? "true" : "false")

void			Location::print_info(void) const
{
	std::cout << C_G_CYAN << "    location" << C_RES << ": " << std::endl;
	std::cout << "    {" << std::endl;
	std::cout << C_G_CYAN << "        uri       " << C_RES << ": " << this->get__uri() << std::endl;
	std::cout << C_G_CYAN << "        root_loc  " << C_RES << ": " << this->get__root_loc() << std::endl;
	std::cout << C_G_CYAN << "        alias     " << C_RES << ": " << this->get__alias() << std::endl;
	std::cout << C_G_CYAN << "        index     " << C_RES << ": " << this->get__index() << std::endl;
	std::cout << C_G_CYAN << "        autoindex " << C_RES << ": " << SBOOL(this->get__autoindex()) << std::endl;
	std::cout << C_G_CYAN << "        upload    " << C_RES << ": " << this->get__upload() << std::endl;
	std::cout << C_G_CYAN << "        redir_301 " << C_RES << ": " << this->get__redir301() << std::endl;
	std::cout << C_G_CYAN << "        methods   " << C_RES << ": " << std::endl;
	std::vector<std::string>::const_iterator it_m = this->get__methods().begin();
	for (; it_m != this->get__methods().end(); it_m++)
	{
		std::cout << "            " << *it_m;
		if (it_m + 1 != this->get__methods().end())
			std::cout << ",";
		std::cout << std::endl;
	}
	std::cout << "    }" << std::endl;
}
