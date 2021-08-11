
# include <webserv.hpp>

void			Config::print_info(void) const
{
	std::cout << C_G_CYAN << "Server" << C_RES << ": " << std::endl;
	std::cout << "{" << std::endl;
	std::cout << C_G_CYAN << "    host" << C_RES << ": " << this->get__host() << std::endl;
	std::cout << C_G_CYAN << "    port" << C_RES << ": " << this->get__port() << std::endl;
	std::cout << C_G_CYAN << "    server_name" << C_RES << ": " << this->get__server_name() << std::endl;
	std::cout << C_G_CYAN << "    host_name" << C_RES << ": " << this->get__host_name() << std::endl;
	std::cout << C_G_CYAN << "    root_dir" << C_RES << ": " << this->get__root_dir() << std::endl;
	std::cout << C_G_CYAN << "    max_body_size" << C_RES << ": " << this->get__max_body_size() << std::endl;
	std::cout << C_G_CYAN << "    error_pages" << C_RES << ": " << std::endl;
	std::cout << "    {" << std::endl;
	std::map<int, std::string>::const_iterator it_e = this->get__error_pages().begin();
	for (; it_e != this->get__error_pages().end(); it_e++)
		std::cout << C_G_CYAN << "        status_code" << C_RES << ": " << it_e->first << " -> " << it_e->second << std::endl;
	std::cout << "    }" << std::endl << std::endl;
	std::map<std::string, Location>::const_iterator it_l = this->get__locations().begin();
	while (it_l != this->get__locations().end())
	{
		it_l->second.print_info();
		it_l++;
		if (it_l != this->get__locations().end())
			std::cout << std::endl;
	}
	std::cout << "}" << std::endl;
}
