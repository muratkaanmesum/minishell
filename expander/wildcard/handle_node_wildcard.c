/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_node_wildcard.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:22:17 by eablak            #+#    #+#             */
/*   Updated: 2023/03/29 20:47:16 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

void	handle_forcommand_option(t_command *command, t_com *com)
{
	com->count = 0;
	com->count = count_wildcard(NULL, com->str, &com->count);
	if (com->count >= 1)
	{
		com->command_files = malloc(sizeof(char *) * (com->count + 1));
		expand_wildcard(NULL, com->str, com->command_files, &com->index);
		com->command_files[com->index] = NULL;
		if (com->command_files == NULL || com->command_files[0] == NULL)
			return ;
		free(command->command);
		command->command = ft_strdup(com->command_files[0]);
		add_command_to_arg(command, com->command_files);
	}
}

void	handle_forcommand(t_command *command, t_com *com, t_sort *sort)
{
	com->index = 0;
	fix_str(command->command);
	if (quotes_control(command->command) == 1)
	{
		com->str = delete_quote(command->command);
		if (is_asterisk(com->str) && asterisk_slash(com->str) == 0)
		{
			com->files = just_asterisk(com->str);
			com->files = sort_files(com->files, com->str, sort);
			com->count_files = files_count(com->files);
			if (com->files[0] == NULL)
				return ;
			if (com->files[0] != NULL)
			{
				free(command->command);
				command->command = ft_strdup(com->files[0]);
			}
			add_command_to_arg(command, com->files);
		}
		else if (asterisk_slash(com->str) == 1)
			handle_forcommand_option(command, com);
		free(com->str);
	}
}

void	handle_forarg_option(t_command *command, t_arg *arg, t_match *match)
{
	arg->count = count_wildcard(NULL, arg->str, &arg->count);
	if (arg->count >= 1)
	{
		arg->index = 0;
		arg->arg_files = malloc(sizeof(char *) * (arg->count + 1));
		expand_wildcard(NULL, arg->str, arg->arg_files, &arg->index);
		arg->arg_files[arg->count] = NULL;
		match_arg_files(arg->arg_files, command, arg->i, match);
	}
}

void	handle_forarg(t_command *command, t_arg *arg, t_sort *sort)
{
	t_match	*match;

	arg->i = 0;
	arg->count = 0;
	match = malloc(sizeof(t_match) * 1);
	while (arg->i < command->argument_count)
	{
		if (quotes_control(command->arguments[arg->i]) == 1)
		{
			arg->str = delete_quote(command->arguments[arg->i]);
			if (is_asterisk(arg->str) && asterisk_slash(arg->str) == 0)
			{
				fix_str(arg->str);
				arg->match_files = just_asterisk(arg->str);
				arg->match_files = sort_files(arg->match_files, arg->str, sort);
				match_arg_files(arg->match_files, command, arg->i, match);
			}
			if (asterisk_slash(arg->str) == 1)
				handle_forarg_option(command, arg, match);
			free(arg->str);
		}
		arg->i++;
	}
	free(match);
}

void	handle_node_wildcard(t_node *node)
{
	t_com	*com;
	t_arg	*arg;
	t_sort	*sort;
	int		i;

	if (node->command->command[0] == '/')
		return ;
	i = 0;
	while (node->command->arguments[i])
	{
		if (node->command->arguments[i][0] == '/')
			return ;
		i++;
	}
	com = malloc(sizeof(t_com) * 1);
	arg = malloc(sizeof(t_arg) * 1);
	sort = malloc(sizeof(t_sort) * 1);
	handle_forcommand(node->command, com, sort);
	handle_forarg(node->command, arg, sort);
	free(com);
	free(arg);
	free(sort);
}
