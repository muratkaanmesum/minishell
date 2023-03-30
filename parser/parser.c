/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 12:06:43 by eablak            #+#    #+#             */
/*   Updated: 2023/03/30 12:06:45 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token	*copy_all_tokens(t_token *tokens)
{
	t_token	*cpy_token;
	int		i;

	cpy_token = malloc(sizeof(t_token) * (get_token_len(tokens) + 1));
	i = 0;
	while (tokens[i].token != UNKNOWN)
	{
		copy_token(&cpy_token[i], tokens[i]);
		i++;
	}
	cpy_token[i].token = UNKNOWN;
	return (cpy_token);
}

t_node	*parser(t_token *tokens, t_execute *execute)
{
	t_node	*head;
	t_token	*cpy_token;

	if (parse_error(tokens) == 1)
	{
		execute->last_exit_code = 258;
		return (NULL);
	}
	cpy_token = copy_all_tokens(tokens);
	head = malloc(sizeof(t_node));
	head->command = NULL;
	execute->top_node = head;
	handle_connections(head, tokens, execute);
	assign_operators(head, cpy_token);
	free_all_node_tokens(head);
	free_tokens(cpy_token);
	head->execute->only_red_count = 0;
	return (head);
}
