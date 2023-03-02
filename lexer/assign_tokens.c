/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:41:46 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/02 12:22:31 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	assign_arg(t_lexer_args *args)
{
	if (my_alpha(args->str[args->i]))
	{
		if (args->is_redirection != 1 && args->tokens[args->index
			- 1].token != RED_FILE)
			args->counter++;
		args->tokens[args->index].start_index = args->i;
		assign_token(args);
		while (my_alpha(args->str[args->i]) && args->str[args->i] != '\0')
		{
			if (args->str[args->i] == '$' && args->counter == 1)
				args->tokens[args->index - 1].token = ENV_COMMAND;
			else if (args->str[args->i] == '$' && args->counter > 1)
				args->tokens[args->index - 1].token = ENV;
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
			args->i++;
		}
		args->tokens[args->index - 1].end_index = args->i;
	}
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
		args->index++;
	}
}

// < test.txt grep e | uniq >outfile.txt
// < test.txt < test.txt grep

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
