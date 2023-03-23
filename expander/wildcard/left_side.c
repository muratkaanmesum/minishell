/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_side.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:22:19 by eablak            #+#    #+#             */
/*   Updated: 2023/03/23 11:24:38 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			if (str[j] != '\0')
				j++;
		}
		i++;
	}
	return (count);
}

char	**left_side_files(char **files, char *str)
{
	int		count;
	char	**new_files;
	int		i;
	int		j;
	int		k;
	int		t;

	count = left_side_files_count(files, str);
	new_files = malloc(sizeof(char *) * (count + 1));
	t = 0;
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
					new_files[t] = ft_strdup(files[i]);
					t++;
				}
			}
			if (str[k] != '\0')
				k++;
		}
		i++;
	}
	free_double_ptr(files);
	new_files[t] = NULL;
	return (new_files);
}
