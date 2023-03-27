/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readdir_o.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 16:54:09 by eablak            #+#    #+#             */
/*   Updated: 2023/03/27 16:58:30 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../wildcard.h"

int	get_o_count(void)
{
	char			buf[1024];
	DIR				*d;
	struct dirent	*dir;
	int				i;

	i = 0;
	getcwd(buf, 1024);
	d = opendir(buf);
	if (d)
	{
		while (1)
		{
			dir = readdir(d);
			if (dir == NULL)
				break ;
			if (dir->d_type == DT_DIR)
				i++;
		}
	}
	closedir(d);
	free(dir);
	return (i);
}

void	get_o_files_process(t_get *get)
{
	while (1)
	{
		get->dir = readdir(get->d);
		if (get->dir == NULL)
			break ;
		if (get->dir->d_type == DT_DIR)
		{
			get->files[get->i] = ft_strdup(get->dir->d_name);
			get->i++;
		}
	}
}

char	**get_o_files(void)
{
	t_get	*get;
	char	**files;

	get = malloc(sizeof(t_get) * 1);
	getcwd(get->buf, 1024);
	get->count = get_o_count();
	get->files = (char **)malloc(sizeof(char *) * (get->count + 1));
	get->d = opendir(get->buf);
	if (get->d)
	{
		get->i = 0;
		get_o_files_process(get);
	}
	closedir(get->d);
	free(get->dir);
	files = get->files;
	get->files[get->i] = NULL;
	free(get);
	return (files);
}