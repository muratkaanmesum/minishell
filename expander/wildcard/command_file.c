/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:22:00 by eablak            #+#    #+#             */
/*   Updated: 2023/03/27 13:18:17 by eablak           ###   ########.fr       */
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
		new_prefix[i++] = file[j++];
	new_prefix[i] = '\0';
	free(file);
	return (new_prefix);
}

char	**mutual_wildcard(char *data, char *path)
{
	char	**files;

	if (ft_strchr(data, '/') != NULL)
	{
		data = edit_data(data);
		if (data[0] == '.')
			files = get_dir(path);
		else
			files = get_w_dot_files2(path, DT_DIR);
		files = take_file(files, data);
		free(data);
	}
	else
	{
		if (data[0] == '.')
			files = get_all(path);
		else
			files = get_w_dot_files2(path, 100);
		files = take_file(files, data);
	}
	free(path);
	return (files);
}

int	count_wildcard(char *prefix, char *suffix, int *count)
{
	t_wild	*wild;

	wild = malloc(sizeof(t_wild) * 1);
	if (suffix == NULL)
	{
		*count += 1;
		return (1);
	}
	wild->data = find_data(suffix);
	getcwd(wild->buf, 1024);
	wild->path = add_slash(wild->buf);
	wild->path = new_path(wild->path, prefix);
	wild->files = mutual_wildcard(wild->data, wild->path);
	suffix = cut_suffix(suffix);
	wild->i = 0;
	while (wild->files[wild->i])
	{
		wild->files[wild->i] = prefix_add_file(prefix, wild->files[wild->i]);
		count_wildcard(wild->files[wild->i], suffix, count);
		wild->i++;
	}
	free_double_ptr(wild->files);
	free(wild->data);
	free(wild);
	return (*count);
}

void	expand_wildcard(char *prefix, char *suffix, char **return_files,
		int *index)
{
	char	*data;
	char	buf[1024];
	char	*path;
	char	**files;
	int		i;

	if (suffix == NULL)
	{
		return_files[*index] = ft_strdup(prefix);
		*index += 1;
		return ;
	}
	data = find_data(suffix);
	path = getcwd(buf, 1024);
	path = add_slash(path);
	path = new_path(path, prefix);
	files = mutual_wildcard(data, path);
	suffix = cut_suffix(suffix);
	i = 0;
	while (files[i])
	{
		files[i] = prefix_add_file(prefix, files[i]);
		expand_wildcard(files[i], suffix, return_files, index);
		i++;
	}
	free_double_ptr(files);
	free(data);
	return ;
}
