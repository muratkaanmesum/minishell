#include "execute.h"

void	execute_node(t_node *node, char **env)
{
	if (ft_strncmp(node->command->command, "pwd", 3) == 0)
		pwd(env);
	if (ft_strncmp(node->command->command, "cd", 2) == 0)
		cd(node->command->arguments[0], env);
	if (ft_strncmp(node->command->command, "echo", 4) == 0)
		echo(node);
	if (ft_strncmp(node->command->command, "env", 3) == 0)
		print_env(env);
	if (ft_strncmp(node->command->command, "export", 6) == 0)
		export(node->command->arguments, env);
	if (ft_strncmp(node->command->command, "unset", 5) == 0)
		unset(node->command->arguments, env);
	if (ft_strncmp(node->command->command, "exit", 4) == 0)
		exit(0);
	return ;
}

int	execute(t_node *head, char **env)
{

	int	i;

	i = 0;
	if (head->connection_count == 1)
		execute_node(head, env);
	else if (head->connection_count > 1)
		while (i < head->connection_count)
		{
			execute(head->connections[i], env);
			i++;
		}
	return (0);
}
