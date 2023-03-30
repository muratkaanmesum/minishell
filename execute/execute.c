/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 05:22:49 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/30 10:19:42 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	execute_node(t_node *node)
{
	if (check_errors(node))
		return ;
	if (ft_strncmp(node->command->command, "pwd", check_size(node, "pwd")) == 0)
		pwd(node);
	else if (ft_strncmp(node->command->command, "cd", check_size(node,
				"cd")) == 0)
		cd(node->command->arguments, node);
	else if (ft_strncmp(node->command->command, "echo", check_size(node,
				"echo")) == 0)
		echo(node);
	else if (ft_strncmp(node->command->command, "env", check_size(node,
				"env")) == 0)
		print_env(node);
	else if (ft_strncmp(node->command->command, "export", check_size(node,
				"export")) == 0)
		export(node->command->arguments, node);
	else if (ft_strncmp(node->command->command, "unset", check_size(node,
				"unset")) == 0)
		unset(node->command->arguments, node);
	else if (ft_strncmp(node->command->command, "exit", check_size(node,
				"exit")) == 0)
		ft_exit(node, get_last_execute_code(node));
	else
		exec_builtin(node);
	close_node_fds(node);
}

void	handle_pipes(t_node *node)
{
	int	i;
	int	fd[2];

	i = 0;
	if (node->connection_count == 0)
		return ;
	while (i < node->connection_count - 1)
	{
		if (node->connections[i]->right_operator == PIPE && i
			+ 1 < node->connection_count)
		{
			pipe(fd);
			node->connections[i]->out_fd = fd[1];
			node->connections[i + 1]->in_fd = fd[0];
			if (node->connections[i]->is_arithmetic == 1)
				close_node_fds(node->connections[i]);
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
	int	next_exec_index;

	next_exec_index = 0;
	if (head->is_subshell == 1)
		execute_subshell(head);
	else if (head->connection_count == 0)
		execute_node(head);
	else if (head->connection_count >= 1)
	{
		while (next_exec_index != -1)
		{
			exec_all(head->connections[next_exec_index]);
			next_exec_index = handle_priority(head, next_exec_index);
		}
		while (waitpid(-1, &head->execute->last_exit_code, 0) > 0)
			;
	}
	if (head->is_subshell == 1)
		waitpid(-1, &head->execute->last_exit_code, 0);
	if (head->right_operator != PIPE)
		waitpid(-1, &head->execute->last_exit_code, 0);
}

int	execute(t_node *head)
{
	handle_pipes(head);
	handle_heredocs(head);
	if (g_execute->exit_code == 1)
	{
		g_execute->exit_code = 0;
		return (0);
	}
	if (head->connection_count == 0)
		exec_single_command(head);
	else
		exec_all(head);
	close_all_fds(head);
	return (0);
}
