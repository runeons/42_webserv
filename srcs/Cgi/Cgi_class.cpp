# include "Cgi.hpp"

void	Cgi::setup_metavariables(void)
{



}

void	Cgi::transform_to_envp(void)
{
	char **env = new char*[_env_map.size() + 1];

	std::map<std::string, std::string>::iterator it = _env_map.begin();
	std::map<std::string, std::string>::iterator itend = _env_map.end();
	for (int i = 0; it != itend; it++, i++)
	{
		std::string var = it->first + "=" + it->second;
		env[i] = new char[var.size() + 1];
		env[i] = strcpy(env[i], var.c_str());
		// std::cout << "env[" << i << "]" << " : " << env[i] << std::endl;
	}
	env[_env_map.size() + 1] = NULL;
	_env_arr = env;
}

void	Cgi::exec_script(void)
{
	int pipefd[2];
	pid_t child;
	// char buf;
	int	status;
	int	ret = 0;

	char *args[] = {(char *)"/bin/ls", 0};
	// char av1[12] = "hello world";
	// create pipe
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	// fork process
	child = fork();
	if (child == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	// if child: connect pipe to stdin + exec more
	if (child == 0) // Child reads from pipe
	{
		if (dup2(pipefd[1], STDOUT_FILENO) < 0)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		ret = execve(args[0], args, _env_arr);
		if (!ret)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
		exit (ret);
		/*
			close(pipefd[1]);  		// Close unused write end
			while (read(pipefd[0], &buf, 1) > 0)
				write(STDOUT_FILENO, &buf, 1);
			write(STDOUT_FILENO, "\n", 1);
			close(pipefd[0]);
			_exit(EXIT_SUCCESS);
		*/
	}
	// write to pipe
	else // Parent writes argv[1] to pipe
	{
		waitpid(child, &status, 0);
		if (close(pipefd[1]) < 0)
		{
			perror("close(pipefd[1])");
			exit(EXIT_FAILURE);
		}
		if (close(pipefd[0]) < 0)
		{
			perror("close(pipefd[0])");
			exit(EXIT_FAILURE);
		}
		if (WIFEXITED(status))
			ret = WIFEXITED(status);

		/*
			close(pipefd[0]);  		// Close unused read end
			write(pipefd[1], av1, strlen(av1));
			close(pipefd[1]);  		// Reader will see EOF
			wait(NULL);				// Wait for child
		*/
	}
	std::cout << "test cout" << std::endl;
	std::cout << "ret : " << ret << std::endl;
}
/* basic man pipe
void	Cgi::exec_script(void)
{
	int pipefd[2];
	pid_t child;
	char buf;

	char av1[12] = "hello world";
	// create pipe
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	// fork process
	child = fork();
	if (child == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	// if child: connect pipe to stdin + exec more
	if (child == 0) // Child reads from pipe
	{
		close(pipefd[1]);  		// Close unused write end
		while (read(pipefd[0], &buf, 1) > 0)
			write(STDOUT_FILENO, &buf, 1);
		write(STDOUT_FILENO, "\n", 1);
		close(pipefd[0]);
		_exit(EXIT_SUCCESS);
	}
	// write to pipe
	else // Parent writes argv[1] to pipe
	{
		close(pipefd[0]);  		// Close unused read end
		write(pipefd[1], av1, strlen(av1));
		close(pipefd[1]);  		// Reader will see EOF
		wait(NULL);				// Wait for child
	}
	std::cout << "test cout" << std::endl;
}
*/

void	Cgi::launch(void)
{
	setup_metavariables();
	transform_to_envp();
	exec_script(); // get response and/or body

}