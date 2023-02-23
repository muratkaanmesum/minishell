#include "../minishell.h"
int	check_simple_command(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].token != UNKNOWN)
		i++;
	if (tokens[0].token == OPEN_PAR && tokens[i - 1].token == CLOSE_PAR)
		return (0);
	return (1);
}

void	handle_simple_command(t_token *tokens)
{
}