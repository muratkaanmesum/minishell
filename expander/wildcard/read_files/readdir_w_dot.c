/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readdir_w_dot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 11:16:56 by eablak            #+#    #+#             */
/*   Updated: 2023/03/29 21:12:27 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../wildcard.h"

int	get_w_path_count(void)
{
	t_get	*get;
	int		i;

	get = malloc(sizeof(t_get) * 1);
	get->i = 0;
	getcwd(get->buf, 1024);
	get->d = opendir(get->buf);
	if (get->d)
	{
		while (1)
		{
			get->dir = readdir(get->d);
			if (get->dir == NULL)
				break ;
			if (get->dir->d_name[0] != '.')
				get->i++;
		}
	}
	i = get->i;
	free(get->dir);
	closedir(get->d);
	free(get);
	return (i);
}

void	get_wdot_process(t_get *get)
{
	while (1)
	{
		get->dir = readdir(get->d);
		if (get->dir == NULL)
			break ;
		if (get->dir->d_name[0] != '.')
		{
			get->files[get->i] = ft_strdup(get->dir->d_name);
			get->i++;
		}
	}
}

char	**get_w_dot_files(void)
{
	t_get	*get;
	char	**files;

	get = malloc(sizeof(t_get) * 1);
	getcwd(get->buf, 1024);
	get->count = get_w_path_count();
	get->files = (char **)malloc(sizeof(char *) * (get->count + 1));
	get->d = opendir(get->buf);
	if (get->d)
	{
		get->i = 0;
		get_wdot_process(get);
	}
	closedir(get->d);
	files = get->files;
	free(get->dir);
	get->files[get->i] = NULL;
	free(get);
	return (files);
}
