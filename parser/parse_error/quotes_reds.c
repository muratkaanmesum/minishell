/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_reds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 14:31:22 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/28 15:57:59 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_error.h"

void	print_error(t_token *tokens)
{
	int	i;

	printf("print_error minishell : ");
	i = 0;
	while (tokens[i].token != UNKNOWN)
	{
		printf("%s ", tokens[i].str);
		i++;
	}
	printf("command not found\n");
}

int	in_count(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

int	less_quotes(t_token *tokens)
{
	int	i;
	int	double_q;
	int	single_q;

	i = 0;
	double_q = 0;
	single_q = 0;
	while (tokens[i].token != UNKNOWN)
	{
		if (ft_strchr(tokens[i].str, '\''))
			single_q += in_count(tokens[i].str, '\'');
		if (ft_strchr(tokens[i].str, '"'))
			double_q += in_count(tokens[i].str, '"');
		i++;
	}
	if (single_q % 2 != 0 || double_q % 2 != 0)
		return (1);
	return (0);
}

int	is_red(t_token *tokens, int start)
{
	if ((tokens[start].token == HERE_DOC || tokens[start].token == I_REDIRECTION
			|| tokens[start].token == O_REDIRECTION
			|| tokens[start].token == APPEND_RED) && (tokens[start
				+ 1].token == CLOSE_PAR))
		return (1);
	return (0);
}

int	check_red(t_token *tokens)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (tokens[i].token != UNKNOWN)
	{
		if (tokens[i].token == OPEN_PAR)
		{
			ret = is_red(tokens, i + 1);
			if (ret == 1)
				return (1);
		}
		i++;
	}
	return (0);
}
