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
		//printf("files : %s\n", files[i]);
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

int	is_right_side(char *str, int index)
{
	int		count;
	char	*ret_str;
	int		j;

	count = 0;
	if (index == 0)
	{
		while (str[index] != '\0' && str[index] != '*')
		{
			count++;
			index += 1;
		}
		if (count > 0)
			return (1);
		else
			return (0);
	}
	return (0);
}

char	*right_side(char *str, int *index)
{
	int		count;
	char	*ret_str;
	int		j;

	count = 0;
	if (*index == 0)
	{
		while (str[*index] != '\0' && str[*index] != '*')
		{
			count++;
			*index += 1;
		}
		ret_str = malloc(sizeof(char) * (count + 1));
		*index -= count;
		j = 0;
		while (str[*index] != '\0' && str[*index] != '*')
		{
			ret_str[j] = str[*index];
			j++;
			*index += 1;
		}
		ret_str[j] = '\0';
		return (ret_str);
	}
	return (NULL);
}

int	is_left_side(char *str, int index)
{
	char	*new_str;
	int		count;
	int		j;

	if (index != 0)
	{
		if (str[index - 1] == '*')
		{
			while (str[index] != '\0')
			{
				if (str[index] == '*')
					return (0);
				index += 1;
				count++;
			}
			if (count > 0)
				return (1);
			else
				return (0);
		}
	}
	return (0);
}

char	*left_side(char *str, int *index)
{
	char	*new_str;
	int		count;
	int		j;

	// while (str[*index])
	// {
	// 	printf("%c", str[*index]);
	// 	*index += 1;
	// }
	// printf("\n");
	count = 0;
	if (*index != 0)
	{
		if (str[*index - 1] == '*')
		{
			while (str[*index] != '\0')
			{
				if (str[*index] == '*')
					return (NULL);
				*index += 1;
				count++;
			}
			new_str = malloc(sizeof(char) * (count + 1));
			*index -= count;
			j = 0;
			while (str[*index] != '\0')
			{
				new_str[j] = str[*index];
				j++;
				*index += 1;
			}
			new_str[j] = '\0';
		}
		return (new_str);
	}
	return (NULL);
}

int	is_middle(char *str, int index)
{
	if (str[index - 1] == '*')
	{
		while (str[index] != '\0')
		{
			if (str[index] == '*')
				return (1);
			index++;
		}
	}
	return (0);
}

char	*middle(char *str, int *index)
{
	int		count;
	char	*new_str;
	int		j;

	count = 0;
	while (str[*index] != '*')
	{
		count++;
		*index += 1;
	}
	new_str = malloc(sizeof(char) * (count + 1));
	*index -= count;
	j = 0;
	while (str[*index] != '*')
	{
		new_str[j] = str[*index];
		j++;
		*index += 1;
	}
	new_str[j] = '\0';
	return (new_str);
}

void	take_file(char **files, char *command)
{
	int	i;

	i = 0;
	while (command[i])
	{
		if (command[i] != '\0')
		{
			if (is_right_side(command, i))
				printf("right side: %s\n", right_side(command, &i));
			if (is_left_side(command, i))
				printf("left side: %s\n", left_side(command, &i));
			if (is_middle(command, i))
				printf("middle: %s\n", middle(command, &i));
		}
		i++;
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