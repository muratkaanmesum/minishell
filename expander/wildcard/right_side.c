/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_side.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:22:29 by eablak            #+#    #+#             */
/*   Updated: 2023/03/16 19:33:05 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

int	is_right_side(char *str, int index)
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

char	*right_side(char *str, int *index)
{
	char	*new_str;
	int		count;
	int		j;

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

int	right_side_files_count(char **files, char *str)
{
	int	i;
	int	j;
	int	k;
	int	count;

	i = 0;
	j = 0;
	k = 0;
	count = 0;
	while (files[i])
	{
		j = 0;
		while (files[i][j])
		{
			if (files[i][j] == str[k])
			{
				while (files[i][j] == str[k] && files[i][j] != '\0'
					&& str[k] != '\0')
				{
					j++;
					k++;
					if (files[i][j] == '\0' && str[k] == '\0')
						count++;
				}
				k = 0;
			}
			j++;
		}
		i++;
	}
	return (count);
}

char	**right_side_files(char **files, char *str)
{
	int		i;
	int		j;
	int		k;
	int		t;
	int		count;
	char	**new_files;

	i = 0;
	j = 0;
	k = 0;
	t = 0;
	count = right_side_files_count(files, str);
	new_files = malloc(sizeof(char *) * (count + 1));
	while (files[i])
	{
		j = 0;
		while (files[i][j])
		{
			if (files[i][j] == str[k])
			{
				while (files[i][j] == str[k] && files[i][j] != '\0'
					&& str[k] != '\0')
				{
					j++;
					k++;
					if (files[i][j] == '\0' && str[k] == '\0')
					{
						new_files[t] = files[i];
						t++;
					}
				}
				k = 0;
			}
			j++;
		}
		i++;
	}
	free(files);
	new_files[t] = NULL;
	return (new_files);
}
