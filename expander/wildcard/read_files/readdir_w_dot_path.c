/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readdir_w_dot_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 11:23:50 by eablak            #+#    #+#             */
/*   Updated: 2023/03/29 21:12:23 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../wildcard.h"

void	get_wpcount2_process(t_get *get, unsigned char d_type)
{
	if (d_type != 100)
	{
		if (get->dir->d_name[0] != '.' && get->dir->d_type == d_type)
			get->i++;
	}
	else
	{
		if (get->dir->d_name[0] != '.')
			get->i++;
	}
}

int	get_w_path_count2(char *path, unsigned char d_type)
{
	t_get	*get;
	int		i;

	get = malloc(sizeof(t_get) * 1);
	get->i = 0;
	get->d = opendir(path);
	if (get->d)
	{
		while (1)
		{
			get->dir = readdir(get->d);
			if (get->dir == NULL)
				break ;
			get_wpcount2_process(get, d_type);
		}
	}
	closedir(get->d);
	i = get->i;
	free(get->dir);
	free(get);
	return (i);
}

void	get_wdot_files_process(t_get *get, unsigned char d_type)
{
	if (d_type != 100)
	{
		if (get->dir->d_name[0] != '.' && get->dir->d_type == d_type)
		{
			get->files[get->i] = ft_strdup(get->dir->d_name);
			get->i++;
		}
	}
	else
	{
		if (get->dir->d_name[0] != '.')
		{
			get->files[get->i] = ft_strdup(get->dir->d_name);
			get->i++;
		}
	}
}

char	**get_w_dot_files2(char *path, unsigned char d_type)
{
	t_get	*get;
	char	**files;

	get = malloc(sizeof(t_get) * 1);
	get->count = get_w_path_count2(path, d_type);
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
			get_wdot_files_process(get, d_type);
		}
	}
	closedir(get->d);
	files = get->files;
	free(get->dir);
	get->files[get->i] = NULL;
	free(get);
	return (files);
}
