/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:22:00 by eablak            #+#    #+#             */
/*   Updated: 2023/03/12 19:43:46 by eablak           ###   ########.fr       */
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
	//free(path);
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
	{
		new_path[i] = prefix[j];
		i++;
		j++;
	}
	new_path[i] = '\0';
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

char	*prefix_add_file(char *prefix, char *file)
{
	int		len_file;
	int		len_prefix;
	int		i;
	char	*new_prefix;
	int		j;

	if (!prefix)
		return (file);
	len_file = ft_strlen(file);
	len_prefix = ft_strlen(prefix);
	i = 0;
	new_prefix = malloc(sizeof(char) * (len_file + len_prefix + 2));
	while (i < len_prefix)
	{
		new_prefix[i] = prefix[i];
		i++;
	}
	new_prefix[i++] = '/';
	j = 0;
	while (j < len_file)
	{
		new_prefix[i] = file[j];
		j++;
		i++;
	}
	new_prefix[i] = '\0';
	return (new_prefix);
}

void expandWildcard(char *prefix, char *suffix)
{
	char	*data;
	char	buf[1024];
	char	*path;
	char	**files;
	int		i;

	if (suffix == NULL)
	{
		printf("RETURN %s\n", prefix);
		return ;
	}
	data = find_data(suffix);
	path = getcwd(buf, 1024);
	path = add_slash(path);
	path = new_path(path, prefix);
	if (ft_strchr(data, '/') != NULL)
	{
		data = edit_data(data);
		files = get_dir(path);
		files = take_file(files, data);
	}
	else
	{
		files = get_all(path);
		files = take_file(files, data);
	}
	suffix = cut_suffix(suffix);
	i = 0;
	while (files[i])
	{
		files[i] = prefix_add_file(prefix, files[i]);
		expandWildcard(files[i], suffix);
		i++;
	}
}
