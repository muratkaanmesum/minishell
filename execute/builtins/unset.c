/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 13:15:50 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/27 06:31:55 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

int	find_env(t_node *node, char *arg)
{
	int	i;

	i = 0;
	while (node->execute->env[i] != NULL)
	{
		if (ft_strncmp(node->execute->env[i], arg,
				get_env_len(node->execute->env[i])) == 0)
		{
			free(node->execute->env[i]);
			while (node->execute->env[i + 1] != NULL)
			{
				node->execute->env[i] = node->execute->env[i + 1];
				i++;
			}
			node->execute->env[i] = NULL;
			return (0);
		}
		i++;
	}
	return (0);
}

int	find_export(t_node *node, char *arg)
{
	int	i;

	i = 0;
	while (node->execute->export[i] != NULL)
	{
		if (ft_strncmp(node->execute->export[i], arg,
				get_env_len(node->execute->export[i])) == 0)
		{
			free(node->execute->export[i]);
			while (node->execute->export[i + 1] != NULL)
			{
				node->execute->export[i] = node->execute->export[i + 1];
				i++;
			}
			node->execute->export[i] = NULL;
			return (0);
		}
		i++;
	}
	return (0);
}

void	unset_w_fork(char **args, t_node *node)
{
	int	i;

	i = 0;
	while (args[i] != NULL)
	{
		find_env(node, args[i]);
		find_export(node, args[i]);
		i++;
	}
}

int	unset(char **args, t_node *node)
{
	int	i;
	int	pid;

	if (node->right_operator != PIPE)
		unset_w_fork(args, node);
	pid = fork();
	if (pid == 0)
	{
		dup2(node->in_fd, 0);
		dup2(node->out_fd, 1);
		close_all_fds(node->execute->top_node);
		i = 0;
		while (args[i] != NULL)
			find_env(node, args[i++]);
		exit(0);
	}
	return (0);
}
