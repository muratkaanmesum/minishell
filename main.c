#include "minishell.h"

int	main(int argc, char **argv)
{
	char	*inpt;

	if (argc != 1)
		return (0);
	(void)argv;
	while (1)
	{
		inpt = readline("minishell: ");
		add_history(inpt);
		lexer(inpt);
		free(inpt);
	}
	return (0);
}
