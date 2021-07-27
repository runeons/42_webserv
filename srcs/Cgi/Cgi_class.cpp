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