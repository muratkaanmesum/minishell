#include "minishell.h"

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

void	free_simple_command(t_command *command)
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
	free(command->command);
	free(command);
}
void	free_tree_rec(t_node *head)
{
	int	i;

	i = 0;
	if (head->connection_count == 1)
		free_simple_command(head->command);
	else
	{
		while (i < head->connection_count)
		{
			free_tree_rec(head->connections[i]);
			i++;
		}
	}
	if (head->redirections != NULL)
		free_redirections(head->redirections);
	free(head->connections);
	free(head->tokens);
	free(head);
}

void	free_tree(t_node *head, t_token *tokens)
{
	free_tree_rec(head);
	free_tokens_str(head->tokens);
}
