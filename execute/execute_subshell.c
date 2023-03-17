/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:49:55 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/17 12:52:33 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	execute_subshell(t_node *node)
{
	int	pid;
	int	i;

	i = 0;
	pid = fork();
	if (pid == 0)
	{
		if (node->connection_count == 1)
			execute_node(node);
		else if (node->connection_count > 1)
		{
			while (i < node->connection_count)
			{
				exec_all(node->connections[i]);
				close_node_fds(node->connections[i]);
				i++;
			}
		}
		exit(0);
	}
	close_all_fds(node);
	waitpid(pid, &node->execute->last_exit_code, 0);
}
