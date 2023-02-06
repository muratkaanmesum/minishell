#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>

int	main(void)
{
	char	*inpt;
	int		i;
//rtes
	i = 0;
	while (1)
	{
		inpt = readline("minishell: ");
		add_history(inpt);
		printf("%s\n", inpt);
		++i;
	}
	return (0);
}
