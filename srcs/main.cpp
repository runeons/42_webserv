
# include <webserv.hpp>
# include<signal.h>

# define SIGNAL_MSG_2 "2     SIGINT       terminate process    interrupt program"
# define SIGNAL_MSG_3 "3     SIGQUIT      create core image    quit program"
# define SIGNAL_MSG_9 "9     SIGKILL      terminate process    kill program"

bool signal_caught = false;

std::string	get_config_file(const char *filename)
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
	printf("signal: %d\n", sig);
	signal_caught = false;
	if (sig == 2 || sig == 3 || sig == 9 || sig == 15)
		signal_caught = true;
	if (sig == 2)
		std::cout << "\r[2] SIGINT: interrupt program" << std::endl;
	else if (sig == 3)
		std::cout << "\r[3] SIGQUIT: quit program" << std::endl;
	else if (sig == 9)
		std::cout << "\r[9] SIGKILL: kill program" << std::endl;
	else if (sig == 15)
		std::cout << "\r[15] SIGTERM: terminate program" << std::endl;
}

int			main(int ac, char **av)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	signal(SIGKILL, handle_signal);
	signal(SIGTERM, handle_signal);
	try
	{
		std::string	config_file;

		if (ac > 2)
		{
			std::cerr << C_G_RED << "error: " << C_G_WHITE << "too many arguments." << C_RES << std::endl;
			return (-1);
		}
		else
		{
			try
			{
				if (ac < 2)
				{
					std::cerr << C_G_MAGENTA << "warning: " << C_G_WHITE << "no config file provided - using conf/example.conf." << C_RES << std::endl;
					std::string default_conf = "conf/example.conf";
					config_file = get_config_file(default_conf.c_str());
				}
				else
					config_file = get_config_file(av[1]);
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

		Server server(cp.get__servers_config());

		if (server.launch())
			return (-1);
	}
	catch (std::exception & e)
	{
		std::cout << "fatal error: " << e.what() << std::endl;
	}

	return (0);
}
