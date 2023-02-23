/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_connections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 13:12:15 by mmesum            #+#    #+#             */
/*   Updated: 2023/02/23 16:31:48 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
int	does_priority(t_token *tokens, enum e_token token)
{
	int	open_count;
	int	i;

	i = 0;
	open_count = 0;
	while (tokens[i].token != UNKNOWN)
	{
		if (tokens[i].token == OPEN_PAR)
		{
			open_count++;
			i++;
			while (open_count != 0 && tokens[i].token != UNKNOWN)
			{
				if (tokens[i].token == OPEN_PAR)
					open_count++;
				if (tokens[i].token == CLOSE_PAR)
					open_count--;
				i++;
			}
		}
		if ((tokens[i].token == AND || tokens[i].token == OR) && token == -1)
			return (1);
		else if (tokens[i].token == token)
			return (1);
		if (tokens[i].token != UNKNOWN && (tokens[i].token != OPEN_PAR
				&& tokens[i].token != CLOSE_PAR))
		{
			i++;
		}
	}
	return (0);
}

t_node	*handle_connections(t_node *head, t_token *tokens)
{
	t_token			**split;
	int				i;
	enum e_token	split_type;

	i = 0;
	// if (does_priority(tokens) == 0)
	// 	return (NULL);
	if (does_priority(tokens, -1))
		split_type = -1;
	else if (does_priority(tokens, PIPE))
		split_type = PIPE;
	else
		split_type = UNKNOWN;
	printf("%d\n", split_type);
	// head->connections = malloc(sizeof(t_tree_node *)
	// 		* connection_count(tokens,));
	if (split_type != UNKNOWN) // subshel veya düz komut
		split = split_token(tokens, split_type);
	else
	{
		if (check_simple_command(tokens))
			handle_simple_command(tokens);
		else
			handle_subshell(tokens);
	}
	while (i < connection_count(tokens, split_type))
	{
		while (split[i]->token != UNKNOWN)
		{
			printf("Token: %d, Start: %d, End: %d, Str: %s\n",
					split[i]->token,
					split[i]->start_index,
					split[i]->end_index,
					split[i]->str);
			split[i]++;
		}
		i++;
		printf("************\n");
	}
	return (head);
}
