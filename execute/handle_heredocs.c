/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredocs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:31:36 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/30 11:34:06 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	len_str(char *arg, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	i = ft_strlen(arg);
	j = ft_strlen(str);
	if (i >= j)
		return (i);
	else
		return (j);
}

void	handle_node_heredoc(t_node *node)
{
	int		i;
	int		fd[2];
	char	*ret_str;
	int		pid;

	i = 0;
	ret_str = NULL;
	while (i < node->redirections->infile_count)
	{
		if (node->redirections->infile_type[i] == HERE_DOC)
		{
			pipe(fd);
			pid = fork();
			if (pid == 0)
				handle_heredoc(node, i, ret_str, fd);
			else
				waitpid(pid, &g_execute->exit_code, 0);
			if (g_execute->exit_code == 256)
				g_execute->exit_code = 1;
			if (g_execute->exit_code == 0)
				node->in_fd = fd[0];
			close(fd[1]);
		}
		i++;
	}
}

void	handle_heredocs(t_node *node)
{
	int	i;

	if (node->connection_count == 0 && node->redirections != NULL)
		handle_node_heredoc(node);
	else if (node->connection_count >= 1)
	{
		i = 0;
		while (i < node->connection_count)
		{
			handle_heredocs(node->connections[i]);
			i++;
		}
		if (node->redirections != NULL)
			handle_node_heredoc(node);
	}
}
