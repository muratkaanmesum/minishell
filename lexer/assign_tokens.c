/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:41:46 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/28 15:53:22 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	assign_arg(t_lexer_args *args)
{
	if (my_alpha(args->str[args->i]))
	{
		if (args->index - 1 < 0 && args->is_redirection != 1)
			args->counter++;
		else if (args->tokens[args->index - 1].token != RED_FILE
			&& args->is_redirection != 1)
			args->counter++;
		args->tokens[args->index].start_index = args->i;
		assign_token(args);
		while (my_alpha(args->str[args->i]) && args->str[args->i] != '\0')
			pass_character(args);
		args->tokens[args->index - 1].end_index = args->i;
	}
}

void	assign_character(t_lexer_args *args)
{
	int	red_count;

	assign_arg(args);
	if (is_redirection(args->str[args->i]))
	{
		red_count = 0;
		args->tokens[args->index].start_index = args->i;
		while (is_redirection(args->str[args->i]) && args->str[args->i] != '\0')
		{
			args->i++;
			red_count++;
			if (red_count == 2)
				break ;
		}
		assign_redirection(args, red_count);
		args->tokens[args->index].end_index = args->i;
		assign_red_arg(args, red_count);
		args->index++;
	}
}

void	assign_parantheses(t_lexer_args *args)
{
	if (args->str[args->i] == '(')
	{
		args->tokens[args->index].start_index = args->i;
		args->tokens[args->index].token = OPEN_PAR;
		args->i++;
		args->tokens[args->index].end_index = args->i;
		args->index++;
	}
	else if (args->str[args->i] == ')')
	{
		args->tokens[args->index].start_index = args->i;
		args->tokens[args->index].token = CLOSE_PAR;
		args->i++;
		args->tokens[args->index].end_index = args->i;
		args->index++;
	}
}

void	assign_tokens(t_token *tokens, char *str)
{
	t_lexer_args	*args;

	args = malloc(sizeof(t_lexer_args));
	args->tokens = tokens;
	args->str = str;
	args->i = 0;
	args->index = 0;
	args->counter = 0;
	args->is_redirection = 0;
	while (args->str[args->i] != '\0')
	{
		assign_character(args);
		assign_parantheses(args);
		if (args->str[args->i] == ' ')
		{
			while (args->str[args->i] == ' ' && args->str[args->i] != '\0')
				args->i++;
		}
	}
	free(args);
}
