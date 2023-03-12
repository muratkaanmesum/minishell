#include "parse_error.h"

int	check_all_operators(t_token *tokens)
{
	int	i;
	int	red_file_count;
	int	red_count;

	red_file_count = 0;
	red_count = 0;
	i = 0;
	while (tokens[i].token != UNKNOWN)
	{
		if (tokens[i].token == RED_FILE)
			red_file_count++;
		if (tokens[i].token == I_REDIRECTION || tokens[i].token == O_REDIRECTION
			|| tokens[i].token == APPEND_RED || tokens[i].token == HERE_DOC)
			red_count++;
		i++;
	}
	if (red_file_count != red_count)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}
int	check_redirections(t_token *tokens)
{
	if (check_all_operators(tokens) == 1)
		return (1);
}
