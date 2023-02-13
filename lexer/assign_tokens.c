#include "../minishell.h"

void	assign_token(t_lexer_args *args)
{
	if (args->counter == 1)
	{
		if (args->str[args->i] == '$')
			args->tokens[args->index].token = ENV_COMMAND;
		else
			args->tokens[args->index].token = COMMAND;
	}
	else if (args->counter > 1)
	{
		if (args->str[args->i] == '-')
			args->tokens[args->index].token = OPTION;
		else if (args->str[args->i] == '$')
			args->tokens[args->index].token = ENV;
		else
			args->tokens[args->index].token = ARG;
	}
	args->index++;
}
void	assign_arg(t_lexer_args *args)
{
	if (my_alpha(args->str[args->i]))
	{
		args->counter++;
		assign_token(args);
		while (my_alpha(args->str[args->i]) && args->str[args->i] != '\0')
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
			args->i++;
		}
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
		while (is_redirection(args->str[args->i]) && args->str[args->i] != '\0')
		{
			args->i++;
			red_count++;
			if (red_count == 2)
				break ;
		}
		assign_redirection(args, red_count);
		args->counter = 0;
		args->index++;
	}
}
//test << test test <tset | test
void	assign_tokens(t_token *tokens, char *str)
{
	t_lexer_args	*args;

	args = malloc(sizeof(t_lexer_args));
	args->tokens = tokens;
	args->str = str;
	args->i = 0;
	args->index = 0;
	args->counter = 0;
	while (args->str[args->i] != '\0')
	{
		assign_character(args);
		if (args->str[args->i] == ' ')
		{
			while (args->str[args->i] == ' ' && args->str[args->i] != '\0')
				args->i++;
		}
	}
}
