/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   middle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:22:24 by eablak            #+#    #+#             */
/*   Updated: 2023/03/29 20:48:51 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

int	is_middle(char *str, int index)
{
	int	i;

	i = index;
	if (index - 1 < 0 && str[index] == '*')
	{
		while (str[index] != '\0')
		{
			if (str[index] == '*')
				return (1);
			index++;
		}
	}
	index = i;
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
		if (count == (int)ft_strlen(str))
			return (1);
		if (file[i] != '\0')
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
	int		count;
	char	**new_files;
	int		i;
	int		k;

	count = middle_files_count(files, str);
	new_files = malloc(sizeof(char *) * (count + 1));
	i = 0;
	k = 0;
	while (files[i])
	{
		if (search_str(files[i], str))
		{
			new_files[k] = ft_strdup(files[i]);
			k++;
		}
		i++;
	}
	free_double_ptr(files);
	new_files[k] = NULL;
	return (new_files);
}
