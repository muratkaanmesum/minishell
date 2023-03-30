/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_tokens_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 10:08:50 by eablak            #+#    #+#             */
/*   Updated: 2023/03/30 12:05:58 by eablak           ###   ########.fr       */
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
		if (args->str[args->i] != '\0')
			args->i++;
	}
	else
		args->i++;
}

int	check_if_command(t_lexer_args *args)
{
	int	i;

	i = args->index - 1;
	while (i >= 0 && args->tokens[i].token != PIPE
		&& args->tokens[i].token != CLOSE_PAR
		&& args->tokens[i].token != OPEN_PAR && args->tokens[i].token != AND
		&& args->tokens[i].token != OR)
	{
		if (args->tokens[i].token == COMMAND)
		{
			args->counter = args->counter + 1;
			return (0);
		}
		i--;
	}
	return (1);
}

void	assign_token(t_lexer_args *args)
{
	if (args->is_redirection == 1)
	{
		args->tokens[args->index].token = RED_FILE;
		args->is_redirection = 0;
	}
	else if (args->counter == 1 && check_if_command(args))
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
	else
		args->tokens[args->index].token = UNKNOWN_TOKEN;
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
