#include "../execute.h"

int	find_env(char **env, char *arg)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], arg, get_env_len(env[i])) == 0)
		{
			free(env[i]);
			while (env[i + 1] != NULL)
			{
				env[i] = env[i + 1];
				i++;
			}
			env[i] = NULL;
			return (0);
		}
		i++;
	}
	return (0);
}
int	unset(char **args, char ***env, t_node *node)
{
	int	i;
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(node->in_fd, 0);
		dup2(node->out_fd, 1);
		close(node->out_fd);
		close(node->in_fd);
		i = 0;
		while (args[i] != NULL)
			find_env(*env, args[i++]);
		exit(0);
	}
	waitpid(pid, NULL, 0);
	return (0);
}
