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

void	print_arg(char **arg)
{
	int	k;

	k = 0;
	while (arg[k])
	{
		printf(" %s  ", arg[k]);
		k++;
	}
}

//SIRALAMA YAPMADIM!!!!!!!!   +tamam

// file gelmiyosa klendini ata!!!!!!  +tamam

//.. için .... verirsen yanlış alır!!!    ----tekrar kontrol

// ** için tek * gibi davranmalı!!!

// *er** tekrar bak

void	match_arg_files(char **files, t_command *command, int i)
{
	int match_files_count = files_count(files);
	int new_len = command->argument_count + match_files_count;
	char **new_args = malloc(sizeof(char *) * (new_len));
	int k = 0;
	int m;
	if (files[0] != NULL)
	{
		while (k < i)
		{
			new_args[k] = command->arguments[k];
			k++;
		}
		m = 0;
		while (m < match_files_count)
		{
			new_args[k + m] = files[m];
			m++;
		}
		while (command->arguments[k + 1])
		{
			new_args[k + m] = command->arguments[k + 1];
			k++;
		}
		new_args[k + m] = NULL;
		command->arguments = new_args;
		command->argument_count = k + m;
	}
}