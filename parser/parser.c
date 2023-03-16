/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 05:08:55 by kali              #+#    #+#             */
/*   Updated: 2023/03/16 18:18:35 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_node	*parser(t_token *tokens)
{
	t_node		*head;
	t_execute	*execute;

	if (parse_error(tokens) == 1)
		return (NULL);
	head = malloc(sizeof(t_node));
	head->command = NULL;
	execute = malloc(sizeof(t_execute));
	execute->last_exit_code = 0;
	execute->top_node = head;
	handle_connections(head, tokens, execute);
	assign_operators(head, tokens);
	return (head);
}
