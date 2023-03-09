#include "wildcard.h"

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

int	search_str(char *file, char *str)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (file[i])
	{
		while (str[j] == file[i] && file[i] && str[j])
		{
			j++;
			i++;
			count++;
		}
		if (count == ft_strlen(str))
			return (1);
		i++;
		j = 0;
		count = 0;
	}
	return (0);
}

int	middle_files_count(char **files, char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (files[i])
	{
		if (search_str(files[i], str))
			count++;
		i++;
	}
	return (count);
}

char	**middle_files(char **files, char *str)
{
	int count = middle_files_count(files, str);
	char **new_files = malloc(sizeof(char *) * (count + 1));
	int i = 0;
	int k = 0;
	while (files[i])
	{
		if (search_str(files[i], str))
		{
			new_files[k] = files[i];
			k++;
		}
		i++;
	}
	free(files);
	new_files[k] = NULL;
	return (new_files);
}