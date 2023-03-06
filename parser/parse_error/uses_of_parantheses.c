#include "parse_error.h"

int	misuse_parantheses(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].token != UNKNOWN)
	{
		if ((tokens[i].token == OPEN_PAR && tokens[i + 2].token == CLOSE_PAR)
			&& tokens[i + 1].token == COMMAND && open_parantheses(tokens) == 0)
			return (1);
		if (tokens[i].token == OPEN_PAR && tokens[i + 1].token == CLOSE_PAR)
			return (2);
		i++;
	}
	return (0);
}

int	out_of_use(t_token *tokens)
{
	int i;
	int count;

	i = 0;
	while (tokens[i].token != UNKNOWN)
	{
		if (tokens[i].token == OPEN_PAR)
		{
			count = 0;
			while (tokens[i].token == OPEN_PAR && tokens[i].token != UNKNOWN)
			{
				count++;
				i++;
			}
			if (count == 2)
			{
				i -= count;
				if (tokens[i].token == OPEN_PAR && tokens[i
					+ 1].token == OPEN_PAR && tokens[i + 2].token == CLOSE_PAR
					&& tokens[i + 3].token == CLOSE_PAR)
					return (1);
				if (tokens[i].token == OPEN_PAR && tokens[i
					+ 1].token == OPEN_PAR && tokens[i + 2].token == COMMAND
					&& tokens[i + 3].token == CLOSE_PAR && tokens[i
					+ 4].token == CLOSE_PAR)
					return (1);
			}
		}
		if (tokens[i].token != UNKNOWN)
			i++;
	}
	return (0);
}