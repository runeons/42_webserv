/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 18:12:44 by tharchen          #+#    #+#             */
/*   Updated: 2021/08/06 18:40:14 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <webserv.hpp>

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

int			main(int ac, char **av)
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

	return 0;
}
