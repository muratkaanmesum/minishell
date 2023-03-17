/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 17:48:31 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/17 10:17:16 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	close_node_fds(t_node *node)
{
	if (node->in_fd > 0)
	{
		close(node->in_fd);
		node->in_fd = -1;
	}
	if (node->out_fd > 1)
	{
		close(node->out_fd);
		node->in_fd = -1;
	}
}

int	get_last_execute_code(t_node *head)
{
	return (head->execute->last_exit_code % 255);
}

void	close_all_fds(t_node *top)
{
	int	i;

	i = 0;
	if (top->connection_count == 1)
		close_node_fds(top);
	else
	{
		close_node_fds(top);
		while (i < top->connection_count)
		{
			close_all_fds(top->connections[i]);
			i++;
		}
	}
}

int	check_priority(t_node *node)
{
	int	i;

	i = 0;
	while (node->tokens[i].token != UNKNOWN)
	{
		if (node->tokens[i].token == AND || node->tokens[i].token == OR)
			return (1);
		i++;
	}
}
char	*get_path(char *path)
{
	char	buff[1024];
	char	*tmp;

	getcwd(buff, 1024);
	if (path != NULL)
	{
		tmp = ft_strjoin(buff, "/");
		path = ft_strjoin(tmp, path);
		free(tmp);
		return (path);
	}
	return (ft_strdup(buff));
}

void	print_all_fds(t_node *node)
{
	int	i;

	i = 0;
	if (node->connection_count == 1)
	{
		printf("in_fd: %d, out_fd: %d\n", node->in_fd, node->out_fd);
	}
	else
	{
		while (i < node->connection_count)
		{
			if (i == 0)
				printf("in_fd: %d, out_fd: %d\n", node->in_fd, node->out_fd);
			print_all_fds(node->connections[i]);
			i++;
		}
	}
}
