#include "wildcard.h"

void	fix_str(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '*' && str[i + 1] == '*')
		{
			i++;
			continue ;
		}
		str[j] = str[i];
		i++;
		j++;
	}
	str[j] = '\0';
}

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
			fix_str(command->arguments[i]);
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
	char	buf[1024];
		static char *prefix;

	fix_str(command->command);
	if (is_asterisk(command->command) || asterisk_slash(command->command) == 0)
	{
		files = just_asterisk(command->command);
		if (files[0] != NULL)
			command->command = files[0];
	}
	if (asterisk_slash(command->command) == 1)
	{
		//command_file(NULL, command->command, getcwd(buf, 1024));
		expandWildcard(NULL, command->command);
	}
}

void	handle_node_wildcard(t_node *node)
{
	handle_forcommand(node->command);
	handle_forarg(node->command);
}
