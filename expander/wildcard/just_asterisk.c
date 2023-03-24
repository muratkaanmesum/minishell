/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   just_asterisk.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:22:07 by eablak            #+#    #+#             */
/*   Updated: 2023/03/24 11:51:02 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

void	clean_files_operators(t_files *files)
{
	files->i = 0;
	files->j = 0;
	files->k = 0;
	files->t = 0;
}

char	**take_file(char **files, char *command)
{
	int		i;
	char	*str;
	t_files	*f_arg;

	i = 0;
	f_arg = malloc(sizeof(t_files) * 1);
	while (command[i])
	{
		if (command[i] != '\0')
		{
			if (is_left_side(command, i))
			{
				str = left_side(command, &i);
				files = left_side_files(files, str, f_arg);
			}
			if (is_middle(command, i))
			{
				str = middle(command, &i);
				files = middle_files(files, str);
			}
			if (is_right_side(command, i))
			{
				str = right_side(command, &i);
				files = right_side_files(files, str, f_arg);
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
