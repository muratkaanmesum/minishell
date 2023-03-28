/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:59:13 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/28 15:55:42 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token	*remove_parantheses(t_token *tokens)
{
	int		i;
	int		j;
	t_token	*new_split;

	i = 0;
	j = 1;
	while (tokens[i].token != UNKNOWN)
		i++;
	if (tokens[0].token == OPEN_PAR && tokens[i - 1].token == CLOSE_PAR)
	{
		new_split = malloc(sizeof(t_token) * (i - 1));
		while (j < i - 1)
		{
			copy_token(&new_split[j - 1], tokens[j]);
			j++;
		}
		new_split[j - 1].token = UNKNOWN;
		return (new_split);
	}
	return (tokens);
}

void	pass_parantheses(t_token *tokens, int *i)
{
	int	open_count;

	open_count = 0;
	if (tokens[*i].token == OPEN_PAR)
	{
		open_count++;
		*i += 1;
		while (open_count != 0 && tokens[*i].token != UNKNOWN)
		{
			if (tokens[*i].token == OPEN_PAR)
				open_count++;
			if (tokens[*i].token == CLOSE_PAR)
				open_count--;
			*i += 1;
		}
	}
}

int	check_parantheses(t_token *tokens)
{
	int	i;

	i = 0;
	pass_parantheses(tokens, &i);
	if (tokens[i].token == UNKNOWN)
		return (1);
	return (0);
}

int	is_arithmetic(t_token *tokens)
{
	int	i;

	i = 1;
	pass_parantheses(tokens, &i);
	if (tokens[i].token == CLOSE_PAR && tokens[i + 1].token == UNKNOWN)
		return (1);
	return (0);
}

void	assign_connections(t_node *head, int split_type, t_token **split,
		t_execute *execute)
{
	int		i;
	t_token	*cleared_tokens;

	if (split_type == 200)
	{
		cleared_tokens = remove_parantheses(head->tokens);
		head->connections[0] = handle_connections(malloc(sizeof(t_node)),
				cleared_tokens, execute);
		return ;
	}
	i = 0;
	while (i < connection_count(head->tokens, split_type))
	{
		head->connections[i] = handle_connections(malloc(sizeof(t_node)),
				split[i], execute);
		i++;
	}
}
