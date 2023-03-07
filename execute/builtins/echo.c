#include "../execute.h"

int	does_have_option(char **option)
{
	int	i;

	i = 0;
	while (option[i] != NULL)
	{
		if (ft_strncmp("-n", option[i], 2) == 0)
			return (1);
		i++;
	}
	return (0);
}
int	print_args(char **args)
{
	int	i;

	i = 0;
	while (args[i + 1] != NULL)
		printf("%s ", args[i++]);
	printf("%s", args[i]);
	return (1);
}
int	echo(char **args, char **option)
{
	int	i;

	if (does_have_option(option) == 0)
	{
		i = 0;
		print_args(args);
		printf("\n");
	}
	else
		print_args(args);
	return (1);
}
