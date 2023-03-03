#include "parse_error.h"

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
		if (open_parantheses(tokens))
			return (1);
		if (is_real_subshell(tokens))
			return (1);
		if (less_quotes(tokens))
			return (1);
		if (check_red(tokens))
			return (1);
		if (token_error(tokens))
			return (1);
	}
	getchar();
	return (0);
}