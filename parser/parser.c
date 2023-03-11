/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 05:08:55 by kali              #+#    #+#             */
/*   Updated: 2023/03/11 11:54:40 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_node	*parser(t_token *tokens)
{
	t_node	*head;

	if (parse_error(tokens) == 0)
	{
		head = malloc(sizeof(t_node));
		head->command = NULL;
		handle_connections(head, tokens);
		return (head);
	}
	return (NULL);
}
