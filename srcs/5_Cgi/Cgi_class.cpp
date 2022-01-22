
# include <webserv.hpp>

void	Cgi::setup_metavariables(void)
{



}

void	Cgi::delete_env_arr(void)
{
	unsigned long i = 0;
	if (_env_arr)
	{
		// while (_env_arr[i])
		while (i < _env_map.size())
		{
			delete _env_arr[i];
			i++;
		}
		std::cout << C_G_YELLOW << "i: " << i << C_RES << '\n';
		delete [] _env_arr;
	}
}

void	Cgi::transform_to_envp(void)
{
	char **env = new char*[_env_map.size() + 1];
	std::cout << C_G_YELLOW << "length of env: " << _env_map.size() + 1 << C_RES << '\n';

	std::map<std::string, std::string>::iterator it = _env_map.begin();
	std::map<std::string, std::string>::iterator itend = _env_map.end();
	for (int i = 0; it != itend; it++, i++)
	{
		std::string var = it->first + "=" + it->second;
		env[i] = new char[var.size() + 1];
		env[i] = strcpy(env[i], var.c_str());
	}
	env[_env_map.size()] = NULL;
	_env_arr = env;
}

static void	bufcat(std::string & dest, char *src)
{
	std::string tmp(src);

	dest += tmp;
}

void	Cgi::exec_script(void)
{
	int		pipe_fd[2];
	int		cgi_fd;
	pid_t	child;
	int		status;

	std::string script = _env_map["SCRIPT_NAME"];
	char *av[3] = {
		(char *)_bin.c_str(), //TODO casts C to change
		(char *)script.c_str(),
		(char *)0
	};
	// open fd of tmp file to store cgi response
	cgi_fd = open("/tmp/cgi_file_our", O_RDWR | O_CREAT | O_APPEND | O_TRUNC, 0666);
	if (cgi_fd == -1)
	{
		std::cerr << "EXIT_IN_CGI_EXEC" << std::endl;
		perror("open cgi_fd");
		exit(EXIT_FAILURE);
	}
	// create pipe
	if (pipe(pipe_fd) == -1)
	{
		std::cerr << "EXIT_IN_CGI_EXEC" << std::endl;
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	// fork process
	child = fork();
	if (child == -1)
	{
		std::cerr << "EXIT_IN_CGI_EXEC" << std::endl;
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (child == 0)		// Child reads from pipe (connect pipe to stdin + exec more)
	{ // PROTECT ALL DUP2
		close(pipe_fd[1]);					// Close unused write side
		dup2(cgi_fd, STDOUT_FILENO);		// Connect the cgi_fd with stdout
		dup2(cgi_fd, STDERR_FILENO);		// Connect the cgi_fd with stderr
		close(cgi_fd);						// Close the cgi_fd
		dup2(pipe_fd[0], STDIN_FILENO);		// Connect the read side with stdin
		close(pipe_fd[0]);					// Close the read side
		// => quand le child va lire, il lira sur le pipe
		// => quand le child va ecrire, il ecrira sur le fichier tmp
		if (execve(av[0], &av[0], _env_arr) < 0)	// Execute process
		{
			std::cerr << "EXIT_IN_CGI_EXEC (av[0] = " << av[0] << ")" << std::endl;
			perror("execve");
			close(pipe_fd[0]);
			exit(EXIT_FAILURE);
		}
	}
	else				// Parent writes to pipe
	{
		// puisque aucun dup2 :
		// => quand le parent va ecrire, il ecrira sur STDOUT
		// => quand le parent va lire, il lira sur STDIN
		close(pipe_fd[0]);					// Close unused read side
		// TODO - DONE - ADDED : si body => write body in pipe_fd[1]
		std::string body = _request.get__body();
		if (body.size())
		{
			ssize_t ret = write(pipe_fd[1], body.c_str(), body.size());
			if (ret == 0 || ret < static_cast<ssize_t>(body.size()))
				throw (Exceptions::ClientException("Write failure (in CGI)"));
			if (ret == -1)
				throw (Exceptions::ClientException("Write failure (in CGI) - returned -1"));
		}

		close(pipe_fd[1]);
		// wait for child
		if (waitpid(child, &status, 0) == -1)
		{
			std::cerr << "EXIT_IN_CGI_EXEC" << std::endl;
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
		if (!WIFEXITED(status))
		{
			std::cout << "status : " << status << std::endl;

			std::cerr << "EXIT_IN_CGI_EXEC" << std::endl;std::cout << "WIFEXITED(status) : " << WIFEXITED(status) << std::endl;
			perror("WIFEXITED(status)");
			exit(EXIT_FAILURE);
		}

		// recup body from cgi_fd to buffer
		lseek(cgi_fd, 0, SEEK_SET); // reposition file offset at begining

		std::string full_buf;
		char buf[BUFS + 1];
		int ret;

		while (1)
		{
			ret = read(cgi_fd, buf, BUFS);
			if (ret == 0)
				break ;
			// ret = -1;
			if (ret == -1)
				throw (Exceptions::ClientException("Read failure (in CGI) - returned -1"));
			buf[ret] = 0;
			bufcat(full_buf, &buf[0]);
		}
		// std::cerr << C_DEBUG << "[ DEBUG ] " << C_RES << "full_buf: [" << full_buf << "]" << std::endl;
		_full_buf = full_buf;
		// TO DO : if body: treat header + body
		close(cgi_fd);
	}
}

void	Cgi::launch(void)
{
	setup_metavariables();
	transform_to_envp();
	exec_script(); // get response and/or body

}
