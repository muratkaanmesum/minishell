/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:22:07 by eablak            #+#    #+#             */
/*   Updated: 2023/03/13 18:08:58 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

int	search_files_count(char **files, char *find)
{
	int	i;
	int	j;
	int	k;
	int	total;

	i = 0;
	j = 0;
	k = 0;
	total = 0;
	while (files[i] != NULL)
	{
		j = 0;
		while (files[i][j])
		{
			k = 0;
			if (files[i][j] == find[k])
			{
				while (find[k] == files[i][j])
				{
					j++;
					k++;
					if (find[k] == '\0')
					{
						total++;
						printf("totati arttıran dosay :%s\n", files[i]);
					}
					if (files[i][j] == '\0')
						break ;
				}
			}
			j++;
		}
		i++;
	}
	return (total);
}

char	**take_file(char **files, char *command)
{
	int		i;
	char	*str;

	i = 0;
	while (command[i])
	{
		if (command[i] != '\0')
		{
			if (is_left_side(command, i))
			{
				str = left_side(command, &i);
				files = left_side_files(files, str);
			}
			if (is_middle(command, i))
			{
				str = middle(command, &i);
				files = middle_files(files, str);
			}
			if (is_right_side(command, i))
			{
				str = right_side(command, &i);
				files = right_side_files(files, str);
			}
		}
		i++;
	}
	return (files);
}
int	get_w_path_count(void)
{
	char			buf[1024];
	DIR				*d;
	struct dirent	*dir;
	int				i;

	i = 0;
	getcwd(buf, 1024);
	d = opendir(buf); //gelen pwd için
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		if(dir->d_name[0] != '.')
			i++;
		closedir(d);
	}
	free(dir);
	return (i);
}

char	**get_w_dot_files(void)
{
	char			buf[1024];
	DIR				*d;
	struct dirent	*dir;
	int				count;
	char			**files;
	int				i;

	getcwd(buf, 1024);
	count = get_w_path_count();
	files = (char **)malloc(sizeof(char *) * (count + 1));
	d = opendir(buf); //gelen pwd için
	if (d)
	{
		i = 0;
		while ((dir = readdir(d)) != NULL)
		{
			if(dir->d_name[0] != '.')
			{
				files[i] = dir->d_name;
				i++;
			}
		}
		closedir(d);
	}
	free(dir);
	files[i] = NULL;
	return (files);
}
char	**just_asterisk(char *command)
{
	int		count;
	char	**my_files;
	int		i;
	if(command[0] == '.')
		my_files = get_files();
	else
		my_files = get_w_dot_files();
	count = get_path_count();
	i = 0;
	my_files = take_file(my_files, command);
	return (my_files);
}


char	**sort_files(char **files, char *str)
{
	int i;
	int m;
	int j;
	int count;
	char **sorted_files;
	int x;

	i = 0;
	m = 0;
	j = 0;
	count = 0;
	while (files[i])
	{
		m = 0;
		j = 0;
		while (files[i][j])
		{
			if (str[m] == files[i][j++])
				m++;
			if (str[m] == '*')
				m++;
		}
		if (str[m] == '\0')
			count++;
		i++;
	}
	sorted_files = malloc(sizeof(char *) * (count + 1));
	i = 0;
	m = 0;
	j = 0;
	x = 0;
	while (files[i])
	{
		m = 0;
		j = 0;
		while (files[i][j])
		{
			if (str[m] == files[i][j++])
				m++;
			if (str[m] == '*')
				m++;
		}
		if (str[m] == '\0')
			sorted_files[x++] = files[i];
		i++;
	}
	sorted_files[x] = NULL;
	return (sorted_files);
}