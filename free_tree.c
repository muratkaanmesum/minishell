/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:24:57 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/23 14:37:04 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	if (command == NULL)
		return ;
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

void	free_all(t_node *head)
{
	if (head->redirections != NULL)
		free_redirections(head->redirections);
	if (head->connections != NULL)
		free(head->connections);
	free(head);
}

void	free_tree_rec(t_node *head)
{
	int	i;

	i = 0;
	if (head->connection_count == 0 && head->is_arithmetic == 0)
	{
		free_simple_command(head->command);
		free_all(head);
	}
	else if (head->connection_count >= 1)
	{
		while (i < head->connection_count)
		{
			free_tree_rec(head->connections[i]);
			i++;
		}
		free_all(head);
	}
}

void	free_tree(t_node *head)
{
	free_tree_rec(head);
}
