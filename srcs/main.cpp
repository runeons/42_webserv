
# include <webserv.hpp>
# include<signal.h>

# define SIGNAL_MSG_2 "2     SIGINT       terminate process    interrupt program"
# define SIGNAL_MSG_3 "3     SIGQUIT      create core image    quit program"
# define SIGNAL_MSG_9 "9     SIGKILL      terminate process    kill program"

std::string	get_config_file(char *filename)
{
	std::string file;
	std::ifstream ifs(filename);
	std::ostringstream ofs;

	if (!ifs)
	{
		std::cerr << C_G_RED << "error:" << C_G_WHITE << "unable to open config_file \'" << filename << "\'." << C_RES << std::endl;
		exit(-1);
	}
	else
	{
		ofs << ifs.rdbuf();
		file = ofs.str();
	}
	if (ifs)
		ifs.close();
	return (file);
}

void		clean_comments_config_file(std::string & config_file)
{
	while (1)
	{
		size_t	pos_diez = config_file.find("#", 0);
		if (pos_diez == std::string::npos)
			break ;
		size_t	pos_nl = config_file.find("\n", pos_diez);
		config_file.replace(pos_diez, pos_nl - pos_diez, "");
	}
}

void		handle_signal(int sig)
{
	if (sig == 2)
		std::cout << "\r[2] SIGINT: interrupt program" << std::endl;
	else if (sig == 3)
		std::cout << "\r[3] SIGQUIT: quit program" << std::endl;
	else if (sig == 9)
		std::cout << "\r[9] SIGKILL: kill program" << std::endl;
}

int			main(int ac, char **av)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	signal(SIGKILL, handle_signal);
	try
	{
		std::string	config_file("");

		if (ac > 2)
		{
			std::cerr << C_G_RED << "error: " << C_G_WHITE << "too many arguments." << C_RES << std::endl;
			return (-1);
		}
		else if (ac < 2)
		{
			std::cerr << C_G_RED << "error: " << C_G_WHITE << "not enough arguments." << C_RES << std::endl;
			return (-1);
		}
		else
		{
			try
			{
				for (int i = 1; i < ac; i++)
					config_file += get_config_file(av[i]);
				clean_comments_config_file(config_file);
				// std::cout << "config_file: " << "[" << config_file << "]" << std::endl;
			}
			catch (std::exception & e)
			{
				std::cout << "error: " << e.what() << std::endl;
			}
		}
		ConfigParser cp(config_file);
		cp.print_info();

		Server server(cp.get__servers_config()[0]);

		if (server.launch())
			return (-1);
	}
	catch (std::exception & e)
	{
		std::cout << "fatal error: " << e.what() << std::endl;
	}

	return (0);
}
