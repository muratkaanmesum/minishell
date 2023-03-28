/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_operators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 15:55:03 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/28 15:56:48 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_error.h"

int	check_missing_redirections(t_token *tokens)
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

int	check_right_redirections(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].token != UNKNOWN)
	{
		if (tokens[i].token == AND && ft_strncmp(tokens[i].str, "&&", 2) != 0)
			return (1);
		else if (tokens[i].token == OR && ft_strncmp(tokens[i].str, "||",
				2) != 0)
			return (1);
		else if (tokens[i].token == I_REDIRECTION && ft_strncmp(tokens[i].str,
				"<", 1) != 0)
			return (1);
		else if (tokens[i].token == O_REDIRECTION && ft_strncmp(tokens[i].str,
				">", 1) != 0)
			return (1);
		else if (tokens[i].token == APPEND_RED && ft_strncmp(tokens[i].str,
				">>", 2) != 0)
			return (1);
		else if (tokens[i].token == HERE_DOC && ft_strncmp(tokens[i].str, "<<",
				2) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	check_all_redirections(t_token *tokens)
{
	if (check_right_redirections(tokens))
	{
		printf("minishell:");
		printf(" syntax error near unexpected token \n");
		return (1);
	}
	else if (check_missing_redirections(tokens))
		return (1);
	return (0);
}

int	check_all_operators(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].token != UNKNOWN)
	{
		if (tokens[i].token == AND || tokens[i].token == OR
			|| tokens[i].token == PIPE)
		{
			if (tokens[i + 1].token == AND || tokens[i + 1].token == OR
				|| tokens[i + 1].token == PIPE)
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
	if (check_missing_operator(tokens) == 1)
		return (1);
	if (check_subshell_operators(tokens) == 1)
		return (1);
	if (check_empty_subshell(tokens) == 1)
		return (1);
	return (0);
}
