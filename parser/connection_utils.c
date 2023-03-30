/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connection_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 12:06:26 by eablak            #+#    #+#             */
/*   Updated: 2023/03/30 12:06:28 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	handle_split_type(enum e_token split_type, t_node *head, t_token ***split)
{
	head->connection_count = connection_count(head->tokens, split_type);
	if (connection_count(head->tokens, split_type) != 0)
		head->connections = malloc(sizeof(t_node *) * head->connection_count);
	else
		head->connections = NULL;
	if (head->is_arithmetic == 1)
	{
		head->connection_count = 0;
		return (0);
	}
	if (split_type != UNKNOWN && head->is_arithmetic != 1 && split_type != 200)
	{
		*split = split_token(head->tokens, split_type);
		return (1);
	}
	else if (split_type == 200)
		return (1);
	else if (split_type == UNKNOWN && head->is_arithmetic != 1)
	{
		handle_simple_command(head);
		return (0);
	}
	return (0);
}

int	get_token_len(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].token != UNKNOWN)
		i++;
	return (i);
}
