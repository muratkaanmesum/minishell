/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredocs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:31:36 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/21 15:47:43 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

char	*heredoc_str(t_node *node, int i)
{
	enum e_token	*in_type;
	char			*str;
	char			*ret;
	char			*new_line;

	ret = "";
	new_line = "\n";
	while (1)
	{
		str = readline(">");
		if (str == NULL)
			break ;
		if (ft_strncmp(str, node->redirections->infile[i], ft_strlen(str)) == 0)
			break ;
		ret = ft_strjoin(ret, str); //libft join
		ret = ft_strjoin(ret, new_line);
	}
	return (ret);
}

void	handle_node_heredoc(t_node *node)
{
	int		i;
	int		fd[2];
	char	*ret_str;
	int		pid;

	i = 0;
	while (i < node->redirections->infile_count)
	{
		if (node->redirections->infile_type[i] == HERE_DOC)
		{
			pipe(fd);
			ret_str = heredoc_str(node, i);
			pid = fork();
			if (pid == 0)
			{
				write(fd[1], ret_str, ft_strlen(ret_str));
				close(fd[1]);
				close_all_fds(node->execute->top_node);
				if (node->in_fd != 0)
					close(node->in_fd);
				exit(0);
			}
			node->in_fd = fd[0];
			close(fd[1]);
			waitpid(pid, NULL, 0);
		}
		i++;
	}
}

void	handle_heredocs(t_node *node)
{
	int	i;

	if (node->connection_count == 1 && node->redirections != NULL)
		handle_node_heredoc(node);
	else if (node->connection_count > 1)
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
