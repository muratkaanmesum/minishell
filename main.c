#include "minishell.h"

int	main(int argc, char **argv)
{
	char	*inpt;
	t_token	*tokens;

	if (argc != 1)
		return (0);
	(void)argv;
	while (1)
	{
		inpt = readline("minishell: ");
		add_history(inpt);
		tokens = lexer(inpt);
		parser(tokens);
		free(inpt);
	}
	return (0);
}
