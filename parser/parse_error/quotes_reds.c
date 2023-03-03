#include "parse_error.h"

void	print_error(t_token *tokens)
{
	int	i;

	printf("minishell : ");
	i = 0;
	while (tokens[i].token != UNKNOWN)
	{
		printf("%s ", tokens[i].str);
		i++;
	}
	printf("command not found\n");
}

int	in_count(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

int	less_quotes(t_token *tokens)
{
	int	i;
	int	double_q;
	int	single_q;

	i = 0;
	double_q = 0;
	single_q = 0;
	while (tokens[i].token != UNKNOWN)
	{
		if (ft_strchr(tokens[i].str, '\''))
			single_q += in_count(tokens[i].str, '\'');
		if (ft_strchr(tokens[i].str, '"'))
			double_q += in_count(tokens[i].str, '"');
		i++;
	}
	//printf("\n\ntek: %d çift: %d\n", single_q, double_q);
	if (single_q % 2 != 0 || double_q % 2 != 0)
	{
		print_error(tokens);
		return (1);
	}
	return (0);
}

int	is_red(t_token *tokens, int start)
{
	while (tokens[start].token != CLOSE_PAR)
	{
		if ((tokens[start].token == HERE_DOC
				|| tokens[start].token == I_REDIRECTION
				|| tokens[start].token == O_REDIRECTION
				|| tokens[start].token == APPEND_RED) && (tokens[start
				+ 1].token == CLOSE_PAR))
			return (1);
		start++;
	}
	return (0);
}

int	check_red(t_token *tokens)
{
	int i;
	int ret;

	i = 0;
	ret = 0;
	while (tokens[i].token != UNKNOWN)
	{
		if (tokens[i].token == OPEN_PAR)
			ret = is_red(tokens, i++);
		i++;
	}
	if (ret == 1)
		printf("bash: syntax error near unexpected token `)'\n");
	return (ret);
}