#include "lexer.h"

int	my_alpha(char c)
{
	if (c != '<' && c != '>' && c != '|' && c != ' ' && c != '&' && c != '('
		&& c != ')')
		return (1);
	return (0);
}

int	is_redirection(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == '&')
		return (1);
	return (0);
}
