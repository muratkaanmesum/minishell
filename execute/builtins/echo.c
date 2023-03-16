#include "../execute.h"

int	does_have_option(t_node *node)
{
	int	i;

	i = 0;
	if (node->command->argument_count == 0)
		return (0);
	if (ft_strncmp(node->command->arguments[0], "-n",
			ft_strlen(node->command->arguments[0])) == 0)
		return (1);
	return (0);
}

void	print_with_option(t_node *head)
{
	int	i;

	i = 1;
	while (i < head->command->argument_count)
	{
		if (head->command->arguments[i + 1] != NULL)
			printf("%s ", head->command->arguments[i]);
		else
			printf("%s", head->command->arguments[i]);
		i++;
	}
}
int	print_args(t_node *head)
{
	int	i;

	i = 0;
	while (i < head->command->argument_count)
	{
		if (head->command->arguments[i + 1] != NULL)
			printf("%s ", head->command->arguments[i]);
		else
			printf("%s", head->command->arguments[i]);
		i++;
	}
	printf("\n");
	return (1);
}

int	echo(t_node *head)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(head->in_fd, 0);
		dup2(head->out_fd, 1);
		if (head->in_fd != 0)
			close(head->in_fd);
		if (head->out_fd != 1)
			close(head->out_fd);
		if (does_have_option(head))
			print_with_option(head);
		else
			print_args(head);
		exit(0);
	}
	waitpid(pid, NULL, 0);
	return (0);
}
