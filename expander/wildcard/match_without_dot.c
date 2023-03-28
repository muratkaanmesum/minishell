/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_without_dot.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 16:31:37 by eablak            #+#    #+#             */
/*   Updated: 2023/03/27 16:42:28 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

void	assign_match_values(t_match *match, t_command *command, char **files)
{
	match->file_count = 0;
	match->k = 0;
	match->count = 0;
	match->count = files_w_dot_count(files);
	match->new_len = command->argument_count + match->count;
	match->new_args = malloc(sizeof(char *) * (match->new_len));
}

void	match_without_prcss(t_command *command, t_match *match)
{
	while (command->arguments[match->k + 1])
	{
		match->new_args[match->k
			+ match->file_count] = ft_strdup(command->arguments[match->k + 1]);
		match->k++;
	}
}

void	match_without_dot(char **files, t_command *command, int i,
		t_match *match)
{
	assign_match_values(match, command, files);
	if (files[0] != NULL)
	{
		mutual_len(match, command, i);
		while (match->m < match->count)
		{
			if (files[match->m][0] != '.')
			{
				match->new_args[match->k
					+ match->file_count] = ft_strdup(files[match->m]);
				match->file_count++;
			}
			match->m++;
		}
		match_without_prcss(command, match);
		free_double_ptr(command->arguments);
		free_double_ptr(files);
		mutual_equalization(match, command);
	}
	else
	{
		free_double_ptr(files);
		free(match->new_args);
	}
}
