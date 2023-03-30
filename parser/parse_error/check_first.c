/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_first.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 12:06:51 by eablak            #+#    #+#             */
/*   Updated: 2023/03/30 12:06:53 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_error.h"

int	incorrect_parantheses(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].token != UNKNOWN)
	{
		if (tokens[i].token == CLOSE_PAR && tokens[i + 1].token == OPEN_PAR)
		{
			printf("incorrect_parantheses minishell: ");
			printf("syntax error near unexpected token `)'\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_first_token(t_token *tokens)
{
	if (tokens[0].token == AND || tokens[0].token == OR
		|| tokens[0].token == PIPE)
	{
		printf("missing_tokens minishell: ");
		printf("syntax error near unexpected token %s\n", tokens[0].str);
		return (1);
	}
	return (0);
}

int	missing_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	if (check_first_token(tokens))
		return (1);
	while (tokens[i].token != UNKNOWN)
	{
		if (tokens[i].token == AND || tokens[i].token == OR
			|| tokens[i].token == PIPE)
		{
			if (tokens[i + 1].token == UNKNOWN)
			{
				printf("missing_tokens minishell: ");
				printf("syntax error near unexpected token %s\n",
					tokens[i].str);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	check_unknown_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].token != UNKNOWN)
	{
		if (tokens[i].token == UNKNOWN_TOKEN)
		{
			printf("unknown_tokens minishell: ");
			printf("syntax error near unexpected token %s\n", tokens[i].str);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_first(t_token *tokens)
{
	if (incorrect_parantheses(tokens))
		return (1);
	if (missing_tokens(tokens))
		return (1);
	if (check_unknown_tokens(tokens))
		return (1);
	return (0);
}
