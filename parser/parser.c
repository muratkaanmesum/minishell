/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 05:08:55 by kali              #+#    #+#             */
/*   Updated: 2023/03/21 14:25:08 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_node	*parser(t_token *tokens, t_execute *execute)
{
	t_node	*head;

	if (parse_error(tokens) == 1)
		return (NULL);
	head = malloc(sizeof(t_node));
	head->command = NULL;
	execute->top_node = head;
	handle_connections(head, tokens, execute);
	assign_operators(head, tokens);
	head->execute->only_red_count = 0;
	return (head);
}
