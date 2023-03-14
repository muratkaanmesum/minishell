/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 05:08:55 by kali              #+#    #+#             */
/*   Updated: 2023/03/14 12:23:10 by mmesum           ###   ########.fr       */
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
	return (head);
}
