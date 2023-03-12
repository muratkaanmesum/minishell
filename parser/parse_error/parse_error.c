/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:22:54 by eablak            #+#    #+#             */
/*   Updated: 2023/03/12 19:22:55 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_error.h"

int	empty_line(t_token *tokens)
{
	if (!tokens)
		return (1);
	return (0);
}

int	parse_error(t_token *tokens)
{
	if (empty_line(tokens) == 0)
	{
		if (less_quotes(tokens))
		{
			print_error(tokens);
			return (1);
		}
		if (open_parantheses(tokens) == 1)
		{
			printf("open_parantheses minishell: syntax error near unexpected token `)'\n");
			return (1);
		}
		if (open_parantheses(tokens) == 2)
		{
			printf("open_parantheses minishell: syntax error near unexpected token `('\n");
			return (1);
		}
		if (out_of_use(tokens))
			return (1);
		if (is_real_subshell(tokens) && token_error(tokens) == 0)
		{
			printf("is_real_subshell minishell: syntax error near unexpected token `('\n");
			return (1);
		}
		if (check_red(tokens))
		{
			printf("check_red bash: syntax error near unexpected token `)'\n");
			return (1);
		}
		if (token_error(tokens))
		{
			printf("token_error bash: syntax error near unexpected token\n");
			return (1);
		}
		if (misuse_parantheses(tokens) == 1)
			return (1);
		if (misuse_parantheses(tokens) == 2)
		{
			printf("misuse_parantheses minishell: syntax error near unexpected token `('\n");
			return (1);
		}
	}
	return (0);
}