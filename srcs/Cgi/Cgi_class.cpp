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
	env[_env_map.size()] = NULL;
	_env_arr = env;
}

void	Cgi::exec_script(void)
{
	int	pipe_fd[2];
	int	cgi_fd;
	pid_t child;
	// char buf;
	int status;

	std::string script = "./scripts/displayenv.pl";
	char *av[3] = {
		(char *)script.c_str(),
		(char *)script.c_str(),
		(char *)0
	};
	// open tmp file to store cgi response
	cgi_fd = open("/tmp/cgi_file", O_RDWR | O_CREAT | O_APPEND | O_TRUNC, 0666);
	if (cgi_fd == -1)
	{
		perror("open cgi_fd");
		exit(EXIT_FAILURE);
	}
	// create pipe
	if (pipe(pipe_fd) == -1)
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
	if (child == 0)		// Child reads from pipe (connect pipe to stdin + exec more)
	{
		close(pipe_fd[1]);					// Close unused write side
		dup2(pipe_fd[0], STDIN_FILENO);		// Connect the read side with stdin
		close(pipe_fd[0]);					// Close the read side
		for (int i = 0; _env_arr[i]; i++)
			std::cout << "[ DEBUG ] _env_arr[" << i << "] = \"" << _env_arr[i] << "\"" << std::endl;
		if (execve(av[0], &av[0], _env_arr) < 0)	// Execute process
		{
			perror("execve");
			close(pipe_fd[0]);
			exit(EXIT_FAILURE);
		}
	}
	else				// Parent writes to pipe
	{
		// Close unused read side
		// close(pipe_fd[0]);
		// Connect the write side with stdout
		// dup2(pipe_fd[1], STDOUT_FILENO);
		// Close the write side
		// close(pipe_fd[1]);
		// execute process
		if (waitpid(child, &status, 0) == -1)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
		if (!WIFEXITED(status))
		{
			std::cout << "status : " << status << std::endl;
			std::cout << "WIFEXITED(status) : " << WIFEXITED(status) << std::endl;
			perror("WIFEXITED(status)");
			exit(EXIT_FAILURE);
		}
	}
}

void	Cgi::launch(void)
{
	setup_metavariables();
	transform_to_envp();
	exec_script(); // get response and/or body

}