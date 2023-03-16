#include "../execute.h"

int	print_env(char **env, t_node *node)
{
	int	i;
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(node->in_fd, 0);
		dup2(node->out_fd, 1);
		// close(node->in_fd);
		// close(node->out_fd);
		i = 0;
		while (env[i] != NULL)
		{
			printf("%s\n", env[i]);
			i++;
		}
		exit(0);
	}
	waitpid(pid, NULL, 0);
	return (1);
}
