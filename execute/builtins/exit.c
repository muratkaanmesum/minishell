#include "../execute.h"

int	get_arg_count(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	is_num(char **args)
{
	int	i;

	i = 0;
	while (args[0][i])
	{
		if (!ft_isdigit(args[0][i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(char **args, int last_exit_code)
{
	int	count;
	int	pid;

	printf("last_exit_code: %d\n", last_exit_code);
	count = get_arg_count(args);
	if (count == 0)
		exit(last_exit_code);
	if (is_num(args) == 0)
	{
		printf("exit\nnumeric argument required\n");
		exit(2);
	}
	else if (count > 1)
	{
		printf("exit\nminishell: exit: too many arguments\n");
		return (1);
	}
	exit(ft_atoi(args[0])); // check this again
	return (0);
}
