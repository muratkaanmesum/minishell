/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:42:46 by mmesum            #+#    #+#             */
/*   Updated: 2023/02/21 13:14:51 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print(t_token *split, int i)
{
	while (split->token != UNKNOWN)
	{
		printf("Token: %d, Start: %d, End: %d, Str: %s\n",
				split->token,
				split->start_index,
				split->end_index,
				split->str);
		split++;
	}
	printf("***************\n");
}

void	parser(t_token *tokens)
{
	t_tree_node	*head;
	int			i;

	head = malloc(sizeof(t_tree_node));
	head->command = NULL;
	i = 0;
	handle_connections(head, tokens);
}
