/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_connections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 13:12:15 by mmesum            #+#    #+#             */
/*   Updated: 2023/02/27 15:01:57 by eablak           ###   ########.fr       */
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
		pass_parantheses(tokens, &i);
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
	if (does_priority(tokens, -1))
		split_type = -1;
	else if (does_priority(tokens, PIPE))
		split_type = PIPE;
	else
		split_type = UNKNOWN;
	// head->connections = malloc(sizeof(t_tree_node *)
	// 		* connection_count(tokens,));
	if (split_type != UNKNOWN) // subshel veya düz komut
		split = split_token(tokens, split_type);
	else
	{
		split = malloc(sizeof(t_token *));
		split[0] = tokens;
	}
	while (i < connection_count(tokens, split_type))
	{
		printf("%d\n", connection_count(tokens, split_type));
		split[i] = check_parantheses(split[i]);
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
