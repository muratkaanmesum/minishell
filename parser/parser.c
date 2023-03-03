/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:42:46 by mmesum            #+#    #+#             */

/*   Updated: 2023/03/03 12:53:23 by eablak           ###   ########.fr       */

/*   Updated: 2023/03/02 16:45:02 by mmesum           ###   ########.fr       */

/*   Updated: 2023/03/02 19:06:51 by eablak           ###   ########.fr       */

/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_node	*parser(t_token *tokens)
{
	t_node	*head;

	head = malloc(sizeof(t_node));
	head->command = NULL;
	if (parse_error(tokens) == 0)
	{
		handle_connections(head, tokens);
		//print_tree(head);
	}
	return (head);
}
