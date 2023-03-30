/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:49:55 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/29 16:21:31 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	assign_dup2(t_node *node)
{
	dup2(node->in_fd, 0);
	dup2(node->out_fd, 1);
}

void	exec_connections(t_node *node)
{
	int	next_exec_index;

	next_exec_index = 0;
	while (next_exec_index != -1)
	{
		exec_all(node->connections[next_exec_index]);
		close_node_fds(node->connections[next_exec_index]);
		next_exec_index = handle_priority(node, next_exec_index);
	}
}

void	execute_subshell(t_node *node)
{
	int	pid;

	handle_node_files(node);
	pid = fork();
	if (pid == 0)
	{
		assign_dup2(node);
		if (node->connection_count == 0)
			execute_node(node);
		else if (node->connection_count >= 1)
		{
			exec_connections(node);
			while (waitpid(-1, &node->execute->last_exit_code, 0) > 0)
				;
		}
		close_all_fds(node->execute->top_node);
		exit(get_last_execute_code(node));
	}
	close_all_fds(node);
}
