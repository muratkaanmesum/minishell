/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readdir_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 10:43:15 by eablak            #+#    #+#             */
/*   Updated: 2023/03/30 10:09:43 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../wildcard.h"

int	get_all_count(char *path)
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
			i++;
		}
	}
	closedir(d);
	return (i);
}

void	get_all_prcss(t_get *get)
{
	while (1)
	{
		get->dir = readdir(get->d);
		if (get->dir == NULL)
			break ;
		get->files[get->i] = ft_strdup(get->dir->d_name);
		get->i++;
	}
}

char	**get_all(char *path)
{
	t_get	*get;
	char	**files;

	get = malloc(sizeof(t_get) * 1);
	get->i = 0;
	get->count = get_all_count(path);
	get->files = (char **)malloc(sizeof(char *) * (get->count + 1));
	get->d = opendir(path);
	if (get->d)
	{
		get->i = 0;
		get_all_prcss(get);
	}
	closedir(get->d);
	files = get->files;
	free(get->dir);
	get->files[get->i] = NULL;
	free(get);
	return (files);
}
