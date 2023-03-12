/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connection_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 11:33:38 by kali              #+#    #+#             */
/*   Updated: 2023/03/11 13:26:22 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_split_type(enum e_token split_type, t_node *head, t_token ***split)
{
	head->connection_count = connection_count(head->tokens, split_type);
	head->connections = malloc(sizeof(t_node *) * connection_count(head->tokens,
				split_type));
	if (split_type != UNKNOWN && head->is_arithmetic != 1)
	{
		*split = split_token(head->tokens, split_type);
		return (1);
	}
	else if (split_type == UNKNOWN && head->is_arithmetic != 1)
	{
		handle_simple_command(head);
		return (0);
	}
	return (0);
}
