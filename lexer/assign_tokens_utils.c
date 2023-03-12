/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_tokens_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 10:08:50 by kali              #+#    #+#             */
/*   Updated: 2023/03/11 10:34:27 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	pass_character(t_lexer_args *args)
{
	if (args->str[args->i] == '"' || args->str[args->i] == '\'')
	{
		args->i++;
		while (args->str[args->i] != '\0')
		{
			if (args->str[args->i] == '"' || args->str[args->i] == '\'')
				break ;
			args->i++;
		}
	}
	else
		args->i++;
}

void	assign_token(t_lexer_args *args)
{
	if (args->is_redirection == 1)
	{
		args->tokens[args->index].token = RED_FILE;
		args->is_redirection = 0;
	}
	else if (args->counter == 1)
		args->tokens[args->index].token = COMMAND;
	else if (args->counter > 1)
	{
		if (args->str[args->i] == '-')
			args->tokens[args->index].token = OPTION;
		else
			args->tokens[args->index].token = ARG;
	}
	args->index++;
}

void	assign_redirection(t_lexer_args *args, int red_count)
{
	if (args->str[args->i - red_count] == '<' && red_count == 1)
		args->tokens[args->index].token = I_REDIRECTION;
	else if (args->str[args->i - red_count] == '<' && red_count == 2)
		args->tokens[args->index].token = HERE_DOC;
	else if (args->str[args->i - red_count] == '>' && red_count == 1)
		args->tokens[args->index].token = O_REDIRECTION;
	else if (args->str[args->i - red_count] == '>' && red_count == 2)
		args->tokens[args->index].token = APPEND_RED;
	else if (args->str[args->i - red_count] == '|' && red_count == 1)
		args->tokens[args->index].token = PIPE;
	else if (args->str[args->i - red_count] == '|' && red_count == 2)
		args->tokens[args->index].token = OR;
	else if (args->str[args->i - red_count] == '&' && red_count == 2)
		args->tokens[args->index].token = AND;
}

void	assign_red_arg(t_lexer_args *args, int red_count)
{
	if ((args->str[args->i - red_count] == '<' && red_count == 1)
		|| (args->str[args->i - red_count] == '<' && red_count == 2)
		|| (args->str[args->i - red_count] == '>' && red_count == 2)
		|| (args->str[args->i - red_count] == '>' && red_count == 1))
	{
		args->is_redirection = 1;
		args->counter = 1;
	}
	else
		args->counter = 0;
}
