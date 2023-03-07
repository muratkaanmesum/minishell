#include "../execute.h"

int	get_arg_count(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}
int	exit(char **args)
{
	int	count;

	count = get_arg_count(args);
	if (count > 1)
		return (1);
}
