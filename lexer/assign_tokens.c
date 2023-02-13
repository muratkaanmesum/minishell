#include "../minishell.h"

void	assign_token(t_token *tokens, char *str, int *i, int *index)
{
	static int	counter;

	if (counter == 1)
		tokens[*index].token = COMMAND;
	else if (counter > 1)
	{
		if (str[*i] == '-')
			tokens[*index].token = OPTION;
		else
			tokens[*index].token = ARG;
	}
}
void	assign_arg(char *str, int *i, t_token *tokens, int *index)
{
	static int	counter;

	if (my_alpha(str[*i]))
	{
		counter++;
		assign_token(tokens, str, i, index);
		while (my_alpha(str[*i]) && str[*i] != '\0')
		{
			if (str[*i] == '"' || str[*i] == '\'')
			{
				*i += 1;
				while (str[*i] != '\0')
				{
					if (str[*i] == '"' || str[*i] == '\'')
						break ;
					*i += 1;
				}
			}
			*i += 1;
		}
	}
}

void	define_character(char *str, int *i, t_token *tokens, int *index)
{
	int	red_count;

	assign_arg(str, &i, tokens, index);
	if (is_redirection(str[*i]))
	{
		red_count = 0;
		while (is_redirection(str[*i]) && str[*i] != '\0')
		{
			*i += 1;
			red_count++;
			if (red_count == 2)
				break ;
		}
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
	while (str[i] != '\0')
	{
		define_character(str, &i, tokens, &index);
		if (str[i] == ' ')
		{
			while (str[i] == ' ' && str[i] != '\0')
				i++;
		}
		index++;
	}
}
