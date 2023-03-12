/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 15:55:03 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/12 15:57:16 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_error.h"

int	check_all_redirections(t_token *tokens)
{
	int	i;
	int	red_file_count;
	int	red_count;

	red_file_count = 0;
	red_count = 0;
	i = 0;
	while (tokens[i].token != UNKNOWN)
	{
		if (tokens[i].token == RED_FILE)
			red_file_count++;
		if (tokens[i].token == I_REDIRECTION || tokens[i].token == O_REDIRECTION
			|| tokens[i].token == APPEND_RED || tokens[i].token == HERE_DOC)
			red_count++;
		i++;
	}
	if (red_file_count != red_count)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}

int	check_all_operators(t_token *tokens)
{
	int				i;
	enum e_token	token;

	i = 0;
	while (tokens[i].token != UNKNOWN)
	{
		if (tokens[i].token == AND || tokens[i].token == OR
			|| tokens[i].token == PIPE)
		{
			token = tokens[i].token;
			if (tokens[i + 1].token == token)
			{
				printf("minishell: syntax error near unexpected token `%s'\n",
						tokens[i].str);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	check_operators(t_token *tokens)
{
	if (check_all_redirections(tokens) == 1)
		return (1);
	if (check_all_operators(tokens) == 1)
		return (1);
}
