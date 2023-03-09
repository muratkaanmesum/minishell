#include "wildcard.h"

int	files_count(char **files)
{
	int	i;

	i = 0;
	if (files[0] == 0)
		return (0);
	while (files[i])
		i++;
	return (i);
}

void	match_arg_files(char **files, t_command *command, int i)
{
	int match_files_count = files_count(files);
	char **new_args = malloc(sizeof(char *) * (command->argument_count
				+ match_files_count));
	int k = 0;
	while (k < i)
	{
		new_args[k] = command->arguments[k];
		k++;
	}
	int m = 0;
	while (m < match_files_count)
	{
		new_args[k + m] = files[m];
		m++;
	}
	while (k + m < command->argument_count)
	{
		new_args[k + m] = command->arguments[k + m];
		m++;
	}
	new_args[k + m] = NULL;
	command->arguments = new_args;
	command->argument_count = k + m;
}