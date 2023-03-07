#include "../execute.h"

int	echo(char *arg, char *option)
{
	if (option == NULL)
		printf("%s\n", arg);
	else if (option[0] == 'n')
		printf("%s", arg);
	return (1);
}
