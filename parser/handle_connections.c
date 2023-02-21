/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_connections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 13:12:15 by mmesum            #+#    #+#             */
/*   Updated: 2023/02/21 18:08:16 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
int	does_priority(t_token *tokens)
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
		if (tokens[i].token == AND || tokens[i].token == OR)
			return (1);
		if (tokens[i].token != UNKNOWN && (tokens[i].token != OPEN_PAR
				&& tokens[i].token != CLOSE_PAR))
		{
			i++;
		}
	}
	return (0);
}

t_token	*check_split(t_token *split)
{
	int		i;
	int		j;
	t_token	*new_split;

	i = 0;
	j = 1;
	while (split[i].token != UNKNOWN)
		i++;
	if (split[0].token == OPEN_PAR && split[i - 1].token == CLOSE_PAR)
	{
		new_split = malloc(sizeof(t_token) * (i - 1));
		while (j < i - 1)
		{
			new_split[j - 1] = split[j];
			j++;
		}
		new_split[j - 1].token = UNKNOWN;
		free(split);
		return (new_split);
	}
	return (split);
}

void	handle_parantheses(t_token *tokens)
{
}

t_tree_node	*handle_connections(t_tree_node *head, t_token *tokens)
{
	t_token	**split;
	int		i;

	i = 0;
	// if (does_priority(tokens) == 0)
	// 	return (NULL);
	i = 0;
	if (does_priority(tokens) == 0)
	{
		handle_parantheses(tokens);
	}
	// head->connections = malloc(sizeof(t_tree_node *)
	// 		* connection_count(tokens));
	// split = split_token(tokens);
	// while (split[i] != NULL)
	// {
	// 	split[i] = check_split(split[i]);
	// 	head->connections[i] = handle_connections(malloc(sizeof(t_tree_node)),
	// 												split[i]);
	// 	i++;
	// }
	return (head);
}
