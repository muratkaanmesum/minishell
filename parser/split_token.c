/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 12:00:41 by kali              #+#    #+#             */
/*   Updated: 2023/03/11 12:26:49 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	connection_count(t_token *tokens, enum e_token token)
{
	int	count;
	int	open_count;
	int	i;

	i = 0;
	open_count = 0;
	count = 0;
	while (tokens[i].token != UNKNOWN)
	{
		pass_parantheses(tokens, &i);
		if (tokens[i].token == token && tokens[i].token != UNKNOWN)
			count++;
		else if (token == -1 && (tokens[i].token == AND
				|| tokens[i].token == OR))
			count++;
		if (tokens[i].token != UNKNOWN)
			i++;
	}
	return (count + 1);
}

int	split_token_count(t_token *tokens, enum e_token token)
{
	int	i;
	int	open_count;
	int	token_count;

	i = 0;
	open_count = 0;
	token_count = 0;
	while (tokens[i].token != UNKNOWN)
	{
		pass_parantheses(tokens, &i);
		if (tokens[i].token == token && tokens[i].token != UNKNOWN)
			break ;
		else if (token == -1 && (tokens[i].token == AND
				|| tokens[i].token == OR))
			break ;
		if (tokens[i].token != UNKNOWN)
			i++;
		token_count++;
	}
	return (token_count);
}

void	assign_values(t_token *tokens, enum e_token token, int *i,
		t_token **split)
{
	t_token	*start;
	int		j;
	int		t_index;

	j = 0;
	t_index = 0;
	while (*i < connection_count(tokens, token))
	{
		j = 0;
		start = &tokens[t_index];
		split[*i] = malloc(sizeof(t_token) * (split_token_count(start, token)
					+ 1));
		while (j < split_token_count(start, token))
		{
			split[*i][j] = tokens[t_index];
			t_index++;
			j++;
		}
		split[*i][j].token = UNKNOWN;
		t_index++;
		*i = *i + 1;
	}
}

t_token	**split_token(t_token *tokens, enum e_token token)
{
	t_token	**split;
	int		i;

	i = 0;
	if (token == UNKNOWN)
		return (NULL);
	split = malloc(sizeof(t_token *) * (connection_count(tokens, token) + 1));
	assign_values(tokens, token, &i, split);
	split[i] = NULL;
	return (split);
}
