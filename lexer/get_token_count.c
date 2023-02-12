#include "../minishell.h"

void	define_character(char *str, int *i, int *count)
{
	int	counter;

	if (my_alpha(str[*i]))
	{
		*count += 1;
		while (my_alpha(str[*i]) && str[*i] != '\0')
		{
			if (str[*i] == '"' || str[*i] == '\'')
			{
				*i += 1;
				while (str[*i] != '\0')
				{
					if (str[*i] == '"' || str[*i] == '\'')
						break ;
					*i += 1;
				}
			}
			*i += 1;
		}
	}
	if (is_redirection(str[*i]))
	{
		*count += 1;
		counter = 0;
		while (is_redirection(str[*i]) && str[*i] != '\0')
		{
			*i += 1;
			counter++;
			if (counter == 2)
				break ;
		}
	}
}

int	get_token_count(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		define_character(str, &i, &count);
		if (str[i] == ' ')
		{
			while (str[i] == ' ' && str[i] != '\0')
				i++;
		}
	}
	return (count);
}
