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
		printf("files : %s\n", files[i]);
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
						printf("totati arttıran dosay :%s\n",files[i]);
					}
					if (files[i][j] == '\0')
						break;
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
	int		count;
	char	*find;
	int		j;

	i = 0;
	count = 0;
	while (command[i])
	{
		if (command[i] == '*')
		{
			right_side();
			left_side();
			middle();
			i++;
			while (command[i] != '*')
			{
				i++;
				count++;
			}
			find = malloc(sizeof(char) * (count + 1));
			i -= count;
			j = 0;
			while (command[i] != '*')
			{
				find[j] = command[i];
				j++;
				i++;
			}
			find[j] = '\0';
			printf("find : %s\n", find);
			printf("dosya sayısı: %d\n", search_files_count(files, find));
		}
		i++;
	}
	// printf("command: %s\n", command);
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
	while (my_files[i])
	{
		printf("%i. %s\n", i + 1, my_files[i]);
		i++;
	}
	take_file(my_files, command);
}

void	handle_arg_asterisk(t_command *command, int index)
{
	if (is_asterisk(command->arguments[0])
		&& asterisk_slash(command->arguments[0]) == 0)
		just_asterisk(command->arguments[0]);
}