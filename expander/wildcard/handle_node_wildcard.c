#include "wildcard.h"

void	handle_forarg(t_command *command)
{
	char	**match_files;
	int		i;

	i = 0;
	while (i < command->argument_count)
	{
		if (is_asterisk(command->arguments[i])
			&& asterisk_slash(command->arguments[i]) == 0)
		{
			match_files = just_asterisk(command->arguments[i]);
			match_files = sort_files(match_files, command->arguments[i]);
			match_arg_files(match_files, command, i);
			print_arg(command->arguments);
			printf("\n");
		}
		i++;
	}
}

void	handle_forcommand(t_command *command)
{
	char	**files;

	if (is_asterisk(command->command) || asterisk_slash(command->command) == 0)
	{
		files = just_asterisk(command->command);
		if (files[0] != NULL)
			command->command = files[0];
	}
	if (asterisk_slash(command->command) == 1
		&& is_asterisk(command->command) == 0)
	{
		command_file(command);
	}
}

void	handle_node_wildcard(t_node *node)
{
	handle_forcommand(node->command);
	handle_forarg(node->command);
}