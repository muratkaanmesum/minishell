/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 09:26:23 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/18 09:26:24 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

int	print_env(t_node *node)
{
	int	i;
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(node->in_fd, 0);
		dup2(node->out_fd, 1);
		close_all_fds(node->execute->top_node);
		i = 0;
		while (node->execute->env[i] != NULL)
		{
			printf("%s\n", node->execute->env[i]);
			i++;
		}
		exit(0);
	}
	waitpid(pid, &node->execute->last_exit_code, 0);
	return (1);
}
