/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:21:32 by kali              #+#    #+#             */
/*   Updated: 2023/03/19 13:36:47 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

int	export_w_fork(char **args, t_node *node)
{
	int	i;

	i = 0;
	if (args == NULL || args[0] == NULL)
		print_export(node);
	else
	{
		while (args[i])
		{
			if (ft_strchr(args[i], '=') == NULL)
				add_export(args[i], node);
			else
			{
				add_export(args[i], node);
				add_env(args[i], node);
			}
			i++;
		}
	}
}

int	export_fork(char **args, t_node *node)
{
	int	pid;
	int	i;

	pid = fork();
	if (pid == 0)
	{
		i = -1;
		close_all_fds(node->execute->top_node);
		if (args == NULL || args[0] == NULL)
			print_export(node);
		exit(0);
	}
	waitpid(pid, &node->execute->last_exit_code, 0);
	return (0);
}

int	export(char **args, t_node *node)
{
	int	pid;
	int	i;

	i = 0;
	if (node->right_operator != PIPE)
		node->execute->last_exit_code = export_w_fork(args, node);
	else
		export_fork(args, node);
	return (0);
}
