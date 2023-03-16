/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 05:22:49 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/16 16:10:07 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	execute_node(t_node *node, char ***env)
{
	if (ft_strncmp(node->command->command, "pwd", 3) == 0)
		pwd(*env, node);
	else if (ft_strncmp(node->command->command, "cd", 2) == 0)
		cd(node->command->arguments[0], *env, node);
	else if (ft_strncmp(node->command->command, "echo", 4) == 0)
		echo(node);
	else if (ft_strncmp(node->command->command, "env", 3) == 0)
		print_env(*env, node);
	else if (ft_strncmp(node->command->command, "export", 6) == 0)
		export(node->command->arguments, env, node);
	else if (ft_strncmp(node->command->command, "unset", 5) == 0)
		unset(node->command->arguments, env, node);
	else if (ft_strncmp(node->command->command, "exit", 4) == 0)
		exit(0);
	else
		exec_builtin(node, *env);
	if (node->in_fd != 0)
		close(node->in_fd);
	if (node->out_fd != 1)
		close(node->out_fd);
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
		if (node->connections[i]->connection_count == 1 && node->connections[i
			+ 1]->left_operator == PIPE)
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

void	execute_rec(t_node *head, char ***env)
{
	int	i;

	i = 0;
	if (head->connection_count == 1)
		execute_node(head, env);
	else if (head->connection_count > 1)
	{
		while (i < head->connection_count)
		{
			execute_rec(head->connections[i], env);
			i++;
		}
	}
}
int	execute(t_node *head, char ***env)
{
	handle_pipes(head);
	handle_files(head);
	execute_rec(head, env);
	return (0);
}
