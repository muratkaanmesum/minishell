#include "../../minishell.h"

int	tokens_count(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].token != UNKNOWN)
		i++;
	return (i);
}

void	print_error(t_token *tokens, int count, int i)
{
	while (i < count - 2)
	{
		printf("%s", tokens[i].str);
		if (i != count - 3)
			printf(" ");
		i++;
	}
}

int	search_token_count(t_token *tokens, enum e_token type_token)
{
	int i = 0;
	int return_count = 0;
	int count = tokens_count(tokens);
	while (i < count)
	{
		if (tokens[i].token == type_token)
			return_count++;
		i++;
	}
	return (return_count);
}