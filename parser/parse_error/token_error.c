#include "parse_error.h"

int	is_command(t_token *tokens, int start)
{
	if (tokens[start + 1].token != PIPE && tokens[start + 1].token != AND
		&& tokens[start + 1].token != OR && tokens[start + 1].token != UNKNOWN)
		return (1);
	return (0);
}

int	token_error(t_token *tokens)
{
	int i = 0;
	int ret = 0;
	while (tokens[i].token != UNKNOWN)
	{
		if (tokens[i].token == CLOSE_PAR)
		{
			if (is_command(tokens, i))
				printf("bash: syntax error near unexpected token %s\n", tokens[i
						+ 1].str);
		}
		i++;
	}
	return (ret);
}