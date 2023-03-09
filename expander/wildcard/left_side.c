#include "wildcard.h"

int	is_left_side(char *str, int index)
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

char	*left_side(char *str, int *index)
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

int	left_side_files_count(char **files, char *str)
{
	int	i;
	int	j;
	int	k;
	int	count;

	count = 0;
	k = 0;
	i = 0;
	j = 0;
	while (files[i])
	{
		j = 0;
		while (str[j])
		{
			if (files[i][0] == str[0])
			{
				while (files[i][j] == str[k] && files[i][j] != '\0'
					&& str[k] != '\0')
				{
					j++;
					k++;
				}
				if (str[k] == '\0')
					count++;
			}
			k = 0;
			j++;
		}
		i++;
	}
	return (count);
}

char	**left_side_files(char **files, char *str)
{
	int count = left_side_files_count(files, str);
	char **new_files = malloc(sizeof(char *) * (count + 1));
	int i;
	int j;
	int k;
	int t = 0;

	i = 0;
	k = 0;
	j = 0;
	while (files[i])
	{
		k = 0;
		while (str[k])
		{
			if (files[i][0] == str[0])
			{
				j = 0;
				while (files[i][j] == str[k] && files[i][j] != '\0'
					&& str[k] != '\0')
				{
					j++;
					k++;
				}
				if (str[k] == '\0')
				{
					new_files[t] = files[i];
					t++;
				}
			}
			k++;
		}
		i++;
	}
	//free(files);
	new_files[t] = NULL;
	return (new_files);
}