#include "execute.h"

int	execute(t_node *head, char **env)
{
	if (ft_strncmp(head->command->command, "pwd", 3) == 0)
		pwd(env);
	if (ft_strncmp(head->command->command, "cd", 2) == 0)
		cd(head->command->arguments[0], env);
}
