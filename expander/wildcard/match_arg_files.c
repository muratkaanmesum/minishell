/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_arg_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:22:22 by eablak            #+#    #+#             */
/*   Updated: 2023/03/27 16:39:28 by eablak           ###   ########.fr       */
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

void	match_argfiles_prcs(t_command *command, t_match *match)
{
	while (command->arguments[match->k + 1])
	{
		match->new_args[match->k
			+ match->m] = ft_strdup(command->arguments[match->k + 1]);
		match->k++;
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
		match_argfiles_prcs(command, match);
		free_double_ptr(command->arguments);
		free_double_ptr(files);
		mutual_equalization(match, command);
	}
}
