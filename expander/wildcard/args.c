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

void	take_file(char **files, char *command)
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
	if (files[0] != NULL)
	{
		printf("eşelşen dosyalar\n");
		print_files(files);
	}
}

void	just_asterisk(char *command)
{
	int		count;
	char	**my_files;
	int		i;

	//gelen yıldızlının nasıl olduğuna bak ona uyumlu olan ilk dosyayı al
	my_files = get_files();
	count = get_path_count();
	i = 0;
	// while (my_files[i])
	// {
	// 	printf("%i. %s\n", i + 1, my_files[i]);
	// 	i++;
	// }
	take_file(my_files, command);
}

void	handle_arg_asterisk(t_command *command, int index)
{
	if (is_asterisk(command->arguments[0])
		&& asterisk_slash(command->arguments[0]) == 0)
		just_asterisk(command->arguments[0]);
}