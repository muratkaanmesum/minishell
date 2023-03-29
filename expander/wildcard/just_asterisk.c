/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   just_asterisk.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:22:07 by eablak            #+#    #+#             */
/*   Updated: 2023/03/29 16:19:08 by mmesum           ###   ########.fr       */
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

void	assign_t_asterisk(t_asterisk *t, char **files,
		char *command)
{
	t->files = files;
	t->command = command;
}

void	handle_all(t_asterisk *t, t_files *f_arg)
{
	if (is_left_side(t->command, t->i))
	{
		t->str = left_side(t->command, &(t->i));
		t->files = left_side_files(t->files, t->str, f_arg);
	}
	if (is_middle(t->command, t->i))
	{
		t->str = middle(t->command, &(t->i));
		t->files = middle_files(t->files, t->str);
	}
	if (is_right_side(t->command, t->i))
	{
		t->str = right_side(t->command, &(t->i));
		t->files = right_side_files(t->files, t->str, f_arg);
	}
}

char	**take_file(char **files, char *command)
{
	t_files		*f_arg;
	t_asterisk	*t;

	f_arg = malloc(sizeof(t_files) * 1);
	t = malloc(sizeof(t_asterisk) * 1);
	t->i = 0;
	assign_t_asterisk(t, files, command);
	while (t->command[t->i])
	{
		if (command[t->i] != '\0')
		{
			handle_all(t, f_arg);
			free(t->str);
		}
		if (command[t->i] != '\0')
			(t->i)++;
	}
	files = t->files;
	free(t);
	free(f_arg);
	return (files);
}

char	**just_asterisk(char *command)
{
	char	**my_files;

	if (command[0] == '.')
		my_files = get_files();
	else
		my_files = get_w_dot_files();
	my_files = take_file(my_files, command);
	return (my_files);
}
