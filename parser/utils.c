/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:59:13 by mmesum            #+#    #+#             */
/*   Updated: 2023/02/21 11:59:54 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	connection_count(t_token *tokens)
{
	int	count;
	int	open_count;
	int	i;

	i = 0;
	open_count = 0;
	count = 0;
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
			count++;
		if (tokens[i].token != UNKNOWN)
			i++;
	}
	return (count + 1);
}

int	get_split_tokens(t_token *tokens)
{
	int	i;
	int	open_count;
	int	sayac;

	i = 0;
	open_count = 0;
	sayac = 0;
	while (tokens[i].token != UNKNOWN)
	{
		if (tokens[i].token == OPEN_PAR)
		{
			open_count++;
			sayac++;
			i++;
			while (open_count != 0)
			{
				if (tokens[i].token == OPEN_PAR)
					open_count++;
				if (tokens[i].token == CLOSE_PAR)
					open_count--;
				sayac++;
				i++;
			}
		}
		if (tokens[i].token == AND || tokens[i].token == OR)
			break ;
		if (tokens[i].token != UNKNOWN)
			i++;
		sayac++;
	}
	return (sayac);
}

t_token	**split_token(t_token *tokens)
{
	t_token	**split;
	t_token	*start;
	int		t_index;

	int i, j;
	t_index = 0;
	split = malloc(sizeof(t_token *) * connection_count(tokens) + 1);
	i = 0;
	j = 0;
	while (i < connection_count(tokens))
	{
		j = 0;
		start = &tokens[t_index];
		split[i] = malloc(sizeof(t_token) * (get_split_tokens(start) + 1));
		while (j < get_split_tokens(start))
		{
			split[i][j] = tokens[t_index];
			t_index++;
			j++;
		}
		split[i][j].token = UNKNOWN;
		t_index++;
		i++;
	}
	split[i] = NULL;
	return (split);
}
// 0 cmd red file unknown
//1 test pipe test pipe unknown
