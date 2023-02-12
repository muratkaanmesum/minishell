#include "../minishell.h"

int	my_alpha(char c)
{
	if (c != 60 && c != 62 && c != 124 && c != ' ' && c != '&')
		return (1);
	return (0);
}

int	is_redirection(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == '&')
		return (1);
	return (0);
}
