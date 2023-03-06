#include "parse_error.h"

int	empty_line(t_token *tokens)
{
	if (!tokens)
		return (1);
	return (0);
}
t_error	check_all_error(t_token *tokens)
{
	t_error error;

	if (empty_line(tokens) == 0)
	{
		if (out_of_use(tokens,error) && open_parantheses(tokens) == 0)
		{
			error.type
		}
		if (misuse_parantheses(tokens,error) && token_error(tokens) == 0)
			return (1);
		if (open_parantheses(tokens))
			return (1);
		if (is_real_subshell(tokens) && token_error(tokens) == 0)
			return (1);
		if (less_quotes(tokens))
			return (1);
		if (check_red(tokens))
			return (1);
		if (token_error(tokens))
			return (1);
	}
}
int	parse_error(t_token *tokens)
{
	t_error ret = check_all_error(tokens);

	return (0);
}