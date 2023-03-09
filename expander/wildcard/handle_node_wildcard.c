#include "wildcard.h"

void	handle_node_wildcard(t_node *node)
{
	int i = 0;
	/*
    1) komut * ise işlem yap
    2) değilse argumanklaraki * lara  göre işlem yap
    */

	if (is_asterisk(node->command->command)
		|| asterisk_slash(node->command->command))
		handle_command_asterisk(node->command);
	// while (i < node->command->argument_count)
	// {
	// 	if (is_asterisk(node->command->arguments[i])
	// 		|| asterisk_slash(node->command->arguments[i]))
	// 		handle_arg_asterisk(node->command, i);
	// 	i++;
	// }
	handle_arg_asterisk(node->command);
}