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

int	middle_files_count(char **files, char *str)
{
	int count = 0;
	return (count);
}