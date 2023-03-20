/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 05:22:49 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/19 12:46:15 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	execute_node(t_node *node)
{
	if (node->is_arithmetic == 1)
	{
		write(1, "minishell: ", 11);
		ft_putendl_fd("Arithmetic Operator Entered", 1);
		node->execute->last_exit_code = 2;
		return ;
	}
	handle_node_files(node);
	if (ft_strncmp(node->command->command, "pwd", 3) == 0)
		pwd(node);
	else if (ft_strncmp(node->command->command, "cd", 2) == 0)
		cd(node->command->arguments, node);
	else if (ft_strncmp(node->command->command, "echo", 4) == 0)
		echo(node);
	else if (ft_strncmp(node->command->command, "env", 3) == 0)
		print_env(node);
	else if (ft_strncmp(node->command->command, "export", 6) == 0)
		export(node->command->arguments, node);
	else if (ft_strncmp(node->command->command, "unset", 5) == 0)
		unset(node->command->arguments, node);
	else if (ft_strncmp(node->command->command, "exit", 4) == 0)
		ft_exit(node->command->arguments, get_last_execute_code(node));
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

int	handle_priority(t_node *head, int i)
{
	while (i + 1 < head->connection_count)
	{
		if (head->connections[i + 1]->left_operator == AND)
		{
			if (get_last_execute_code(head->connections[i]) == 0)
				return (i + 1);
		}
		else if (head->connections[i + 1]->left_operator == OR)
		{
			if (get_last_execute_code(head->connections[i]) != 0)
				return (i + 1);
		}
		else if (head->connections[i + 1]->left_operator == PIPE)
			return (i + 1);
		i++;
	}
	return (-1);
}

void	exec_all(t_node *head)
{
	int	i;
	int	next_exec_index;

	next_exec_index = 0;
	i = 0;
	if (head->is_subshell == 1)
		execute_subshell(head);
	else if (head->connection_count == 1)
		execute_node(head);
	else if (head->connection_count > 1)
	{
		while (next_exec_index != -1)
		{
			exec_all(head->connections[next_exec_index]);
			next_exec_index = handle_priority(head, next_exec_index);
		}
	}
}

int	execute(t_node *head)
{
	handle_pipes(head);
	exec_all(head);
	close_all_fds(head);
	return (0);
}
