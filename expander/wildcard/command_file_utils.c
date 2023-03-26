/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_file_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:38:38 by eablak            #+#    #+#             */
/*   Updated: 2023/03/26 08:57:54 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

char	*find_data(char *suffix)
{
	int		i;
	char	*data;

	i = 0;
	while (suffix[i] != '\0' && suffix[i] != '/')
		i++;
	if (suffix[i] == '/')
		i++;
	data = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (suffix[i] != '\0' && suffix[i] != '/')
	{
		data[i] = suffix[i];
		i++;
	}
	if (suffix[i] == '/')
		data[i++] = '/';
	data[i] = '\0';
	return (data);
}

char	*edit_data(char *data)
{
	char	*new_data;
	int		i;

	i = 0;
	while (data[i] != '\0')
		i++;
	if (data[i - 1] == '/')
		new_data = malloc(sizeof(char) * (i));
	else
		return (data);
	i = 0;
	while (data[i] != '/')
	{
		new_data[i] = data[i];
		i++;
	}
	new_data[i] = '\0';
	return (new_data);
}

char	*add_slash(char *path)
{
	char	*new_path;
	int		len;
	int		i;

	len = ft_strlen(path);
	new_path = malloc(sizeof(char) * (len + 2));
	i = 0;
	while (i < len)
	{
		new_path[i] = path[i];
		i++;
	}
	new_path[i] = '/';
	new_path[++i] = '\0';
	return (new_path);
}

char	*new_path(char *path, char *prefix)
{
	char	*new_path;
	int		len_prefix;
	int		len_path;
	int		i;
	int		j;

	if (!prefix)
		return (path);
	len_prefix = ft_strlen(prefix);
	len_path = ft_strlen(path);
	new_path = malloc(sizeof(char) * (len_path + len_prefix + 1));
	i = 0;
	while (i < len_path)
	{
		new_path[i] = path[i];
		i++;
	}
	j = 0;
	if (prefix[0] == '/')
		j++;
	while (j < len_prefix)
		new_path[i++] = prefix[j++];
	new_path[i] = '\0';
	free(path);
	return (new_path);
}

char	*cut_suffix(char *suffix)
{
	int	i;

	i = 0;
	while (suffix[i] != '/' && suffix[i] != '\0')
		i++;
	if (suffix[i] == '\0')
		return (NULL);
	else if (suffix[i + 1] == '\0')
		return (NULL);
	return (&suffix[i + 1]);
}
