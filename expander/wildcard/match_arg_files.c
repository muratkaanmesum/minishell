/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_arg_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:22:22 by eablak            #+#    #+#             */
/*   Updated: 2023/03/25 13:16:02 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

void	mutual_len(t_match *match, t_command *command, int i)
{
	while (match->k < i)
	{
		match->new_args[match->k] = command->arguments[match->k];
		match->k++;
	}
	match->m = 0;
}

void	mutual_equalization(t_match *match, t_command *command)
{
	match->new_args[match->k + match->m] = NULL;
	command->arguments = match->new_args;
	command->argument_count = match->k + match->m;
}

void	assign_match_values(t_match *match, t_command *command, char **files)
{
	match->file_count = 0;
	match->k = 0;
	match->count = 0;
	match->count = files_w_dot_count(files);
	match->new_len = command->argument_count + match->count;
	match->new_args = malloc(sizeof(char *) * (match->new_len));
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
		while (command->arguments[match->k + 1])
		{
			match->new_args[match->k
				+ match->file_count] = ft_strdup(command->arguments[match->k
					+ 1]);
			match->k++;
		}
		// free_double_ptr(command->arguments);
		// free_double_ptr(files);
		mutual_equalization(match, command);
	}
}

void	match_arg_files(char **files, t_command *command, int i, t_match *match)
{
	if (command->arguments[i][0] != '.')
	{
		match_without_dot(files, command, i, match);
		return ;
	}
	match->match_files_count = files_count(files);
	match->new_len = command->argument_count + match->match_files_count;
	match->new_args = malloc(sizeof(char *) * (match->new_len));
	match->k = 0;
	if (files[0] != NULL)
	{
		mutual_len(match, command, i);
		while (match->m < match->match_files_count)
		{
			match->new_args[match->k + match->m] = ft_strdup(files[match->m]);
			match->m++;
		}
		while (command->arguments[match->k + 1])
		{
			match->new_args[match->k
				+ match->m] = ft_strdup(command->arguments[match->k + 1]);
			match->k++;
		}
		free_double_ptr(command->arguments);
		free_double_ptr(files);
		mutual_equalization(match, command);
	}
}
