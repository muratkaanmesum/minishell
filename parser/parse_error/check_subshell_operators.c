/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_subshell_operators.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:25:15 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/29 19:09:01 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_error.h"

int	check_end(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].token != UNKNOWN)
	{
		if (tokens[i].token == CLOSE_PAR)
		{
			if (i - 1 >= 0 && (tokens[i - 1].token == PIPE || tokens[i
						- 1].token == AND || tokens[i - 1].token == OR))
			{
				printf("minishell : syntax error near unexpected token `|'\n");
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	check_start(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].token != UNKNOWN)
	{
		if (tokens[i].token == OPEN_PAR)
		{
			if (tokens[i + 1].token == PIPE || tokens[i + 1].token == AND
				|| tokens[i + 1].token == OR)
			{
				printf("minishell : syntax error near unexpected token `|'\n");
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	check_subshell_operators(t_token *tokens)
{
	if (check_start(tokens) == 1)
		return (1);
	if (check_end(tokens) == 1)
		return (1);
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
			if (check_before_subshell(tokens, i))
			{
				printf("minishell : syntax error near unexpected token `%s'\n",
					tokens[i + 1].str);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	check_empty_subshell(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].token != UNKNOWN)
	{
		if (tokens[i].token == OPEN_PAR)
		{
			if (tokens[i + 1].token == CLOSE_PAR)
			{
				printf("minishell : syntax error near unexpected token `)'\n");
				return (1);
			}
		}
		i++;
	}
	return (0);
}
