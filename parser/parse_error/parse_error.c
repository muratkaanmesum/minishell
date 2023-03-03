#include "../../minishell.h"

int	empty_line(t_token *tokens)
{
	if (!tokens)
		return (1);
	return (0);
}

int	parse_error(t_token *tokens)
{
	//print_token(tokens);
	if (empty_line(tokens) == 0)
	{
		if (out_of_use(tokens))
			return (1);
		if (open_parantheses(tokens) || is_real_subshell(tokens)
			|| less_quotes(tokens) || check_red(tokens) || token_error(tokens))
			return (1);
	}
	return (0);
}