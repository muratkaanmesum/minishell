/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readdir_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 10:43:15 by eablak            #+#    #+#             */
/*   Updated: 2023/03/24 11:42:17 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

int	get_dir_count(char *path)
{
	char			buf[1024];
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
	free(dir);
	return (i);
}

char	**get_dir(char *path)
{
	t_get	*get;

	get = malloc(sizeof(t_get) * 1);
	get->count = get_dir_count(path);
	get->files = (char **)malloc(sizeof(char *) * (get->count + 1));
	get->i = 0;
	get->d = opendir(path);
	if (get->d)
	{
		get->i = 0;
		while (1)
		{
			get->dir = readdir(get->d);
			if (get->dir == NULL)
				break ;
			if (get->dir->d_type == DT_DIR)
			{
				get->files[get->i] = get->dir->d_name;
				get->i++;
			}
		}
	}
	free(get->dir);
	get->files[get->i] = NULL;
	return (get->files);
}

int	get_all_count(char *path)
{
	char			buf[1024];
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
			i++;
		}
	}
	free(dir);
	return (i);
}

char	**get_all(char *path)
{
	t_get	*get;

	get = malloc(sizeof(t_get) * 1);
	get->i = 0;
	get->count = get_all_count(path);
	get->files = (char **)malloc(sizeof(char *) * (get->count + 1));
	get->d = opendir(path);
	if (get->d)
	{
		get->i = 0;
		while (1)
		{
			get->dir = readdir(get->d);
			if (get->dir == NULL)
				break ;
			get->files[get->i] = get->dir->d_name;
			get->i++;
		}
	}
	free(get->dir);
	get->files[get->i] = NULL;
	return (get->files);
}
