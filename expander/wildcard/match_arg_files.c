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

//.. için .... verirsen yanlış alır!!!    +tamam

// *er** tekrar bak !! BİRDEN FAZLA * YANYANAYSA YANLIŞ ALIR

int	files_w_dot_count(char **files)
{
	int	i;
	int	count;

	i = 0;
	if (files[0] == 0)
		return (0);
	while (files[i])
	{
		if (files[i][0] != '.')
			count++;
		i++;
	}
	return (count);
}

void	match_without_dot(char **files, t_command *command, int i)
{
	int		count;
	int		new_len;
	char	**new_args;
	int		k;
	int		m;
	int		file_count;

	file_count = 0;
	m = 0;
	k = 0;
	count = files_w_dot_count(files);
	new_len = command->argument_count + count;
	new_args = malloc(sizeof(char *) * (new_len));
	k = 0;
	if (files[0] != NULL)
	{
		while (k < i)
		{
			new_args[k] = command->arguments[k];
			k++;
		}
		m = 0;
		while (m < count)
		{
			if (files[m][0] != '.')
			{
				new_args[k + file_count] = files[m];
				file_count++;
			}
			m++;
		}
		while (command->arguments[k + 1])
		{
			new_args[k + file_count] = command->arguments[k + 1];
			k++;
		}
		new_args[k + file_count] = NULL;
		command->arguments = new_args;
		command->argument_count = k + file_count;
	}
}

void	match_arg_files(char **files, t_command *command, int i)
{
	int		match_files_count;
	int		new_len;
	char	**new_args;
	int		k;
	int		m;

	if (command->arguments[i][0] != '.')
	{
		match_without_dot(files, command, i);
		return ;
	}
	match_files_count = files_count(files);
	new_len = command->argument_count + match_files_count;
	new_args = malloc(sizeof(char *) * (new_len));
	k = 0;
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
