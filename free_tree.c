#include "minishell.h"



int	free_token(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].token != UNKNOWN)
	{
		free(tokens[i].str);
		i++;
	}
	free(tokens);
	return (0);
}

void	free_command(t_command *command)
{
	int	i;

	i = 0;
	while (i < command->argument_count)
	{
		free(command->arguments[i]);
		i++;
	}
	i = 0;
	free(command->arguments);
}
void	free_redirections(t_redirections *redirections)
{
	int	i;

	i = 0;
	while (i < redirections->infile_count)
	{
		free(redirections->infile[i]);
		i++;
	}
	i = 0;
	while (i < redirections->outfile_count)
	{
		free(redirections->outfile[i]);
		i++;
	}
	free(redirections->infile);
	free(redirections->infile_type);
	free(redirections->outfile);
	free(redirections->outfile_type);
	free(redirections);
}

void	free_simple_command(t_node *node)
{
	free_command(node->command);
	free_token(node->tokens);
	if (node->redirections != NULL)
		free_redirections(node->redirections);
}

void	free_tree(t_node *head)
{
	int	i;

	i = 0;
	if (head->connection_count == 1)
		free_simple_command(head);
	else
	{
		while (i < head->connection_count)
		{
			free_tree(head->connections[i]);
			free_token(head->tokens);
			if (head->redirections != NULL)
				free_redirections(head->redirections);
			free(head->connections[i]);
			i++;
		}
	}
	free(head->connections);
	free(head);
}
