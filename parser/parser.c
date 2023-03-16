/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 05:08:55 by kali              #+#    #+#             */
/*   Updated: 2023/03/16 14:51:59 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_node	*parser(t_token *tokens)
{
	t_node	*head;

	if (parse_error(tokens) == 1)
		return (NULL);
	head = malloc(sizeof(t_node));
	head->command = NULL;
	handle_connections(head, tokens);
	assign_operators(head, tokens);
	// print_token(tokens);
	return (head);
}
