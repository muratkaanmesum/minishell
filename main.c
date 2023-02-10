#include "minishell.h"

int	main(void)
{
	char	*inpt;

	while (1)
	{
		inpt = readline("minishell: ");
		add_history(inpt);
		lexer(inpt);
		free(inpt);
	}
	return (0);
}
//test"grep test"test < test.txt
