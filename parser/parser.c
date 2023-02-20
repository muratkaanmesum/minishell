/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:42:46 by mmesum            #+#    #+#             */
/*   Updated: 2023/02/20 19:37:27 by eablak           ###   ########.fr       */
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
		if (tokens[i].token != UNKNOWN)
			i++;
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
		new_split[j].token = UNKNOWN;
		free(split);
		return (new_split);
	}
	return (split);
}
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
t_tree_node	*handle_connections(t_tree_node *head, t_token *tokens)
{
	t_token	**split;
	int		i;

	i = 0;
	if (does_priority(tokens) == 0)
		return (NULL);
	i = 0;
	head->connections = malloc(sizeof(t_tree_node *)
			* connection_count(tokens));
	split = split_token(tokens);
	while (split[i] != NULL)
	{
		split[i] = check_split(split[i]);
		print(split[i], i);
		head->connections[i] = handle_connections(malloc(sizeof(t_tree_node)),
													split[i]);
		i++;
	}
	return (head);
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
