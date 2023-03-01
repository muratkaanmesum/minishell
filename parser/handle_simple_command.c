/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_simple_command.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:41:00 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/01 19:26:20 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
void	handle_command(t_node *node)
{
	int	i;

	i = 0;
	while (node->tokens[i].token != UNKNOWN)
	{
		if (node->tokens[i].token == COMMAND
			|| node->tokens[i].token == ENV_COMMAND)
			node->command->command = node->tokens[i].str;
		i++;
	}
}
void	handle_option(t_node *node)
{
	int	i;
	int	count;
	int	j;

	i = 0;
	j = 0;
	count = 0;
	while (node->tokens[i].token != UNKNOWN)
	{
		if (node->tokens[i].token == OPTION)
			count++;
		i++;
	}
	node->command->option_count = count;
	i = 0;
	node->command->options = malloc(sizeof(char *) * (count + 1));
	while (node->tokens[i].token != UNKNOWN)
	{
		if (node->tokens[i].token == OPTION)
			node->command->options[j++] = node->tokens[i].str;
		i++;
	}
	node->command->options[count] = NULL;
}

void	handle_args(t_node *node)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (node->tokens[i].token != UNKNOWN)
	{
		if (node->tokens[i].token == ARG)
			count++;
		i++;
	}
	node->command->argument_count = count;
	i = 0;
	node->command->arguments = malloc(sizeof(char *) * (count + 1));
	j = 0;
	while (node->tokens[i].token != UNKNOWN)
	{
		if (node->tokens[i].token == ARG)
			node->command->arguments[j++] = node->tokens[i].str;
		i++;
	}
	node->command->arguments[j] = NULL;
}
void	handle_simple_command(t_node *node)
{
	node->command = malloc(sizeof(t_command));
	handle_command(node);
	handle_option(node);
	handle_args(node);
}
