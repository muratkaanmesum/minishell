#include "../minishell.h"

int	connection_count(t_token *tokens, enum e_token token)
{
	int	count;
	int	open_count;
	int	i;

	i = 0;
	open_count = 0;
	count = 0;
	while (tokens[i].token != UNKNOWN)
	{
		if (tokens[i].token == OPEN_PAR)
		{
			open_count++;
			i++;
			while (open_count != 0 && tokens[i].token != UNKNOWN)
			{
				if (tokens[i].token == OPEN_PAR)
					open_count++;
				if (tokens[i].token == CLOSE_PAR)
					open_count--;
				i++;
			}
		}
		if (tokens[i].token == token && tokens[i].token != UNKNOWN)
			count++;
		else if (token == -1 && (tokens[i].token == AND
					|| tokens[i].token == OR))
			count++;
		if (tokens[i].token != UNKNOWN)
			i++;
	}
	return (count + 1);
}

int	split_token_count(t_token *tokens, enum e_token token)
{
	int	i;
	int	open_count;
	int	token_count;

	i = 0;
	open_count = 0;
	token_count = 0;
	while (tokens[i].token != UNKNOWN)
	{
		if (tokens[i].token == OPEN_PAR)
		{
			open_count++;
			token_count++;
			i++;
			while (open_count != 0)
			{
				if (tokens[i].token == OPEN_PAR)
					open_count++;
				if (tokens[i].token == CLOSE_PAR)
					open_count--;
				token_count++;
				i++;
			}
		}
		if (tokens[i].token == token && tokens[i].token != UNKNOWN)
			break ;
		else if (token == -1 && (tokens[i].token == AND
					|| tokens[i].token == OR))
			break ;
		if (tokens[i].token != UNKNOWN)
			i++;
		token_count++;
	}
	return (token_count);
}

// (cat test1.txt | grep e && ls) && wc -l | ls | ls | ls
t_token	**split_token(t_token *tokens, enum e_token token)
{
	t_token	**split;
	t_token	*start;
	int		t_index;

	if (token == UNKNOWN)
		return (NULL);
	int i, j;
	t_index = 0;
	split = malloc(sizeof(t_token *) * (connection_count(tokens, token) + 1));
	i = 0;
	j = 0;
	while (i < connection_count(tokens, token))
	{
		j = 0;
		start = &tokens[t_index];
		split[i] = malloc(sizeof(t_token) * (split_token_count(start, token)
					+ 1));
		while (j < split_token_count(start, token))
		{
			split[i][j] = tokens[t_index];
			t_index++;
			j++;
		}
		split[i][j].token = UNKNOWN;
		t_index++;
		i++;
	}
	split[i] = NULL;
	return (split);
}
