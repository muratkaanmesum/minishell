/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   just_asterisk.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:22:07 by eablak            #+#    #+#             */
/*   Updated: 2023/03/21 20:45:38 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

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
		if (command[i] != '\0')
			i++;
	}
	return (files);
}

char	**just_asterisk(char *command)
{
	int		count;
	char	**my_files;
	int		i;

	if (command[0] == '.')
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
	int		i;
	int		m;
	int		j;
	int		count;
	char	**sorted_files;
	int		x;

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
