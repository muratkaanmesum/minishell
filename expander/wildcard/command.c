#include "wildcard.h"

void	command_file(void)
{
	printf("commanfd file\n");
}

void	handle_command_asterisk(t_command *command)
{
	char **files;

	if (is_asterisk(command->command) || asterisk_slash(command->command) == 0)
		files = just_asterisk(command->command);
	if (files[0] != NULL)
		command->command = files[0];
	printf("%s	", command->command);
}