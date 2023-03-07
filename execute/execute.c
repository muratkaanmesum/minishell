#include "execute.h"

int	execute(t_node *head, char **env)
{
	if (ft_strncmp(head->command->command, "pwd", 3) == 0)
		pwd(env);
	if (ft_strncmp(head->command->command, "cd", 2) == 0)
		cd(head->command->arguments[0], env);
	if (ft_strncmp(head->command->command, "echo", 4) == 0)
		echo(head->command->arguments, head->command->options);
	if (ft_strncmp(head->command->command, "env", 3) == 0)
		print_env(env);
}
