#include "wildcard.h"

int	search_files_count(char **files, char *find)
{
	int	i;
	int	j;
	int	k;
	int	total;

	i = 0;
	j = 0;
	k = 0;
	total = 0;
	while (files[i] != NULL)
	{
		j = 0;
		while (files[i][j])
		{
			k = 0;
			if (files[i][j] == find[k])
			{
				while (find[k] == files[i][j])
				{
					j++;
					k++;
					if (find[k] == '\0')
					{
						total++;
						printf("totati arttıran dosay :%s\n", files[i]);
					}
					if (files[i][j] == '\0')
						break ;
				}
			}
			j++;
		}
		i++;
	}
	return (total);
}

char	**take_file(char **files, char *command)
{
	int		i;
	char	*str;

	i = 0;
	print_files(files);
	printf("\n");
	while (command[i])
	{
		if (command[i] != '\0')
		{
			if (is_left_side(command, i))
			{
				str = left_side(command, &i);
				files = left_side_files(files, str);
			}
			if (is_middle(command, i))
			{
				str = middle(command, &i);
				files = middle_files(files, str);
			}
			if (is_right_side(command, i))
			{
				str = right_side(command, &i);
				files = right_side_files(files, str);
			}
		}
		i++;
	}
	return (files);
}

char	**just_asterisk(char *command)
{
	int		count;
	char	**my_files;
	int		i;

	my_files = get_files();
	count = get_path_count();
	i = 0;
	my_files = take_file(my_files, command);
	return (my_files);
}

void	handle_arg_asterisk(t_command *command, int index)
{
	char **match_files;
	int i = 0;
	printf("arg count :%d\n", command->argument_count);
	getchar();
	while (i < command->argument_count)
	{
		if (is_asterisk(command->arguments[i])
			&& asterisk_slash(command->arguments[i]) == 0)
		{
			match_files = just_asterisk(command->arguments[i]);
			printf("eşelşen dosyalar\n");
			print_files(match_files);
			match_arg_files(match_files, command, i);
		}
		i++;
	}
}