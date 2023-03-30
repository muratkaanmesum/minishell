/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 17:48:31 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/30 10:17:20 by mmesum           ###   ########.fr       */
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
		node->out_fd = -1;
	}
}

int	get_last_execute_code(t_node *head)
{
	if (head->execute->last_exit_code != 0)
		return (1);
	return (0);
}

void	close_all_fds(t_node *top)
{
	int	i;

	i = 0;
	if (top->connection_count == 0)
		close_node_fds(top);
	else if (top->connection_count >= 1)
	{
		close_node_fds(top);
		while (i < top->connection_count)
		{
			close_all_fds(top->connections[i]);
			i++;
		}
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

int	check_size(t_node *node, char *command)
{
	if (ft_strlen(command) > ft_strlen(node->command->command))
		return (ft_strlen(command));
	else
		return (ft_strlen(node->command->command));
}
