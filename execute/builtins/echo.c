#include "../execute.h"

int	check_option(char *str)
{
	if (ft_strlen(str) != 2)
		return (0);
	if (str[0] == '-' && str[1] == 'n' && str[2] == '\0' && str != NULL)
		return (1);
	return (0);
}

int	does_have_option(t_node *node)
{
	int	i;

	i = 0;
	if (ft_strncmp(node->command->arguments[0], "-n", ft_strlen(node->command->arguments[0])) == 0)
		return (0);
	return (1);
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
	return (1);
}

int	echo(t_node *head)
{
	if (does_have_option(head))
	{
		print_args(head);
		printf("\n");
	}
	else
		print_args(head);
	return (1);
}
