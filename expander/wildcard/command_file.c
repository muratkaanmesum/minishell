/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:22:00 by eablak            #+#    #+#             */
/*   Updated: 2023/03/23 18:38:29 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

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

int	countWildcard(char *prefix, char *suffix, int *count)
{
	char	*data;
	char	buf[1024];
	char	*path;
	char	**files;
	int		i;

	if (suffix == NULL)
	{
		*count += 1;
		return (1);
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
		countWildcard(files[i], suffix, count);
		i++;
	}
	return (*count);
}

void	expandWildcard(char *prefix, char *suffix, char **return_files,
		int *index)
{
	char	*data;
	char	buf[1024];
	char	*path;
	char	**files;
	int		i;

	if (suffix == NULL)
	{
		return_files[*index] = prefix;
		*index += 1;
		return ;
	}
	data = find_data(suffix);
	path = getcwd(buf, 1024);
	path = add_slash(path);
	path = new_path(path, prefix);
	if (ft_strchr(data, '/') != NULL)
	{
		data = edit_data(data);
		if (data[0] == '.')
			files = get_dir(path);
		else
			files = get_w_dot_files2(path, DT_DIR);
		files = take_file(files, data);
	}
	else
	{
		if (data[0] == '.')
			files = get_all(path);
		else
			files = get_w_dot_files2(path, 100);
		files = take_file(files, data);
	}
	suffix = cut_suffix(suffix);
	i = 0;
	while (files[i])
	{
		files[i] = prefix_add_file(prefix, files[i]);
		expandWildcard(files[i], suffix, return_files, index);
		i++;
	}
	return ;
}
