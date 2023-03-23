/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parantheses.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:22:49 by eablak            #+#    #+#             */
/*   Updated: 2023/03/23 15:20:10 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_error.h"

int	is_real_subshell(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].token != UNKNOWN)
	{
		if (tokens[i].token == OPEN_PAR && i != 0)
		{
			if (tokens[i - 1].token != AND && tokens[i - 1].token != OR
				&& tokens[i - 1].token != PIPE)
				return (1);
		}
		if (tokens[i].token == OPEN_PAR && i == 0)
			return (0);
		i++;
	}
	return (0);
}

int	open_parantheses(t_token *tokens)
{
	int	open_par;
	int	close_par;

	open_par = search_token_count(tokens, OPEN_PAR);
	close_par = search_token_count(tokens, CLOSE_PAR);
	if (close_par > open_par)
		return (1);
	else if (open_par > close_par)
		return (2);
	return (0);
}

int	check_missing_operator(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].token != UNKNOWN)
	{
		if (tokens[i].token == OPEN_PAR)
		{
			if (i - 1 >= 0 && tokens[i - 1].token != PIPE && tokens[i
				- 1].token != AND && tokens[i - 1].token != OR){
					printf("minishell : syntax error near unexpected token `('\n");
				return (1);
				}
		}
		i++;
	}
	return (0);
}
