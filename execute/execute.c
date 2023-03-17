/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 05:22:49 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/17 05:08:22 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	execute_node(t_node *node)
{
	if (ft_strncmp(node->command->command, "pwd", 3) == 0)
		pwd(node);
	else if (ft_strncmp(node->command->command, "cd", 2) == 0)
		cd(node->command->arguments[0], node);
	else if (ft_strncmp(node->command->command, "echo", 4) == 0)
		echo(node);
	else if (ft_strncmp(node->command->command, "env", 3) == 0)
		print_env(node);
	else if (ft_strncmp(node->command->command, "export", 6) == 0)
		export(node->command->arguments, node);
	else if (ft_strncmp(node->command->command, "unset", 5) == 0)
		unset(node->command->arguments, node);
	else if (ft_strncmp(node->command->command, "exit", 4) == 0)
		exit(0);
	else
		exec_builtin(node);
	close_node_fds(node);
}

void	handle_pipes(t_node *node)
{
	int	i;
	int	fd[2];

	i = 0;
	if (node->connection_count == 1)
		return ;
	while (i < node->connection_count - 1)
	{
		if (node->connections[i]->right_operator == PIPE && i
			+ 1 < node->connection_count)
		{
			pipe(fd);
			node->connections[i]->out_fd = fd[1];
			node->connections[i + 1]->in_fd = fd[0];
		}
		i++;
	}
	i = 0;
	while (i < node->connection_count)
	{
		handle_pipes(node->connections[i]);
		i++;
	}
}

void	execute_rec(t_node *head)
{
	int	i;

	i = 0;
	if (head->connection_count == 1)
	{
		execute_node(head);
		head->is_executed = 1;
	}
	else if (head->connection_count > 1)
	{
		while (i < head->connection_count)
		{
			if (head->connections[i]->left_operator == AND
				|| head->connections[i]->left_operator == OR)
				break ;
			execute_rec(head->connections[i]);
			i++;
		}
		if (i == head->connection_count - 1)
			head->is_executed = 1;
	}
}
void	exec_all(t_node *head)
{
	int	i;

	i = 0;
	if (head->connection_count == 1)
		execute_rec(head);
	else if (head->connection_count > 1)
	{
		while (i < head->connection_count)
		{
			execute_rec(head->connections[i]);
			if (i + 1 < head->connection_count)
			{
				if (head->connections[i + 1]->left_operator == AND)
				{
					if (get_last_execute_code(head) != 0)
						break ;
				}
				else if (head->connections[i + 1]->left_operator == OR)
				{
					if (get_last_execute_code(head) == 0)
						break ;
				}
			}
			i++;
		}
	}
}
int	execute(t_node *head)
{
	handle_pipes(head);
	handle_files(head);
	exec_all(head);
	close_all_fds(head);
	return (0);
}
