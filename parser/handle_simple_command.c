/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_simple_command.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:41:00 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/21 15:33:45 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	handle_command(t_node *node)
{
	int	i;

	i = 0;
	while (node->tokens[i].token != UNKNOWN)
	{
		if (node->tokens[i].token == COMMAND
			|| node->tokens[i].token == ENV_COMMAND)
			node->command->command = ft_strdup(node->tokens[i].str);
		i++;
	}
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
		if (node->tokens[i].token == ARG || node->tokens[i].token == OPTION)
			count++;
		i++;
	}
	node->command->argument_count = count;
	i = 0;
	node->command->arguments = malloc(sizeof(char *) * (count + 1));
	j = 0;
	while (node->tokens[i].token != UNKNOWN)
	{
		if (node->tokens[i].token == ARG || node->tokens[i].token == OPTION)
			node->command->arguments[j++] = ft_strdup(node->tokens[i].str);
		i++;
	}
	node->command->arguments[j] = NULL;
}

void	handle_simple_command(t_node *node)
{
	node->command = malloc(sizeof(t_command));
	handle_command(node);
	handle_args(node);
}
