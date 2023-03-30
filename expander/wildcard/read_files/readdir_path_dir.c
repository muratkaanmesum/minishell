/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readdir_path_dir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 16:46:08 by eablak            #+#    #+#             */
/*   Updated: 2023/03/30 10:09:42 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../wildcard.h"

int	get_dir_count(char *path)
{
	DIR				*d;
	struct dirent	*dir;
	int				i;

	i = 0;
	d = opendir(path);
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
	return (i);
}

void	get_dir_prcss(t_get *get)
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

char	**get_dir(char *path)
{
	t_get	*get;
	char	**files;

	get = malloc(sizeof(t_get) * 1);
	get->count = get_dir_count(path);
	get->files = (char **)malloc(sizeof(char *) * (get->count + 1));
	get->i = 0;
	get->d = opendir(path);
	if (get->d)
	{
		get->i = 0;
		get_dir_prcss(get);
	}
	closedir(get->d);
	files = get->files;
	free(get->dir);
	get->files[get->i] = NULL;
	free(get);
	return (files);
}
