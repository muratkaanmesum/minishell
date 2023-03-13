/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readdir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:22:26 by eablak            #+#    #+#             */
/*   Updated: 2023/03/12 19:22:27 by eablak           ###   ########.fr       */
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
	d = opendir(path); //gelen pwd için
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
			if (dir->d_type == DT_DIR)
				i++;
		closedir(d);
	}
	free(dir);
	return (i);
}

char	**get_dir(char *path)
{
	DIR				*d;
	struct dirent	*dir;
	int				count;
	char			**files;
	int				i;
	int				j;

	count = get_dir_count(path);
	files = (char **)malloc(sizeof(char *) * (count + 1));
	i = 0;
	d = opendir(path); //gelen pwd için
	if (d)
	{
		i = 0;
		while ((dir = readdir(d)) != NULL)
			if (dir->d_type == DT_DIR)
			{
				files[i] = dir->d_name;
				i++;
			}
		//closedir(d);
	}
	free(dir);
	files[i] = NULL;
	return (files);
}

int	get_all_count(char *path)
{
	char			buf[1024];
	DIR				*d;
	struct dirent	*dir;
	int				i;

	i = 0;
	//getcwd(buf, 1024);
	d = opendir(path); //gelen pwd için
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
			i++;
		closedir(d);
	}
	free(dir);
	return (i);
}

char	**get_all(char *path)
{
	char			buf[1024];
	DIR				*d;
	struct dirent	*dir;
	int				count;
	char			**files;
	int				i;

	//getcwd(buf, 1024);
	i = 0;
	count = get_all_count(path);
	files = (char **)malloc(sizeof(char *) * (count + 1));
	d = opendir(path); //gelen pwd için
	if (d)
	{
		i = 0;
		while ((dir = readdir(d)) != NULL)
		{
			files[i] = dir->d_name;
			i++;
		}
		closedir(d);
	}
	free(dir);
	files[i] = NULL;
	return (files);
}