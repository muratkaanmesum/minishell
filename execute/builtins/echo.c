#include "../execute.h"

int	check_option(char *str)
{
	if (str[0] == '-' && str[1] == 'n' && str[2] == '\0' && str != NULL)
		return (1);
	return (0);
}

int	does_have_option(t_node *node)
{
	int	i;

	i = 0;
	if (check_option(node->tokens[1].str) == 1)
		return (1);
	return (0);
}

int	print_args(t_node *head)
{
	int	i;

	i = 0;
	while (head->tokens[i].token != UNKNOWN)
	{
		if (ft_strncmp(head->tokens[i].str, "echo", 4) != 0)
		{
			if (head->tokens[i + 1].token != UNKNOWN)
				printf("%s ", head->tokens[i].str);
			else
				printf("%s", head->tokens[i].str);
		}
		i++;
	}
	return (1);
}

int	echo(t_node *head)
{
	int	i;

	if (does_have_option(head) == 0)
	{
		i = 0;
		print_args(head);
		printf("\n");
	}
	else
		print_args(head);
	return (1);
}
