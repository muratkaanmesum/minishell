/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 05:10:28 by eablak            #+#    #+#             */
/*   Updated: 2023/03/30 12:05:44 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

int	pwd(t_node *node)
{
	int	pid;
	int	i;

	pid = fork();
	if (pid == 0)
	{
		dup2(node->in_fd, 0);
		dup2(node->out_fd, 1);
		close_all_fds(node->execute->top_node);
		i = 0;
		while (node->execute->env[i] != NULL)
		{
			if (ft_strncmp(node->execute->env[i], "PWD=", 4) == 0)
			{
				printf("%s\n", node->execute->env[i] + 4);
				exit(0);
			}
			i++;
		}
		exit(1);
	}
	return (1);
}
