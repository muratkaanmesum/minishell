#include "wildcard.h"

void	handle_node_wildcard(t_node *node)
{
	int i = 0;
	/*
    1) komut * ise işlem yap
    2) değilse argumanklaraki * lara  göre işlem yap
    */

	
	handle_command_asterisk(node->command);
	handle_arg_asterisk(node->command);
}