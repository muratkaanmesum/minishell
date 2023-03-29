/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredocs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:31:36 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/29 14:58:01 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		index;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	i = 0;
	index = 0;
	str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!str)
		return (0);
	while (s1[index] != '\0')
		str[i++] = s1[index++];
	index = 0;
	while (s2[index] != '\0')
		str[i++] = s2[index++];
	str[i] = '\0';
	free(s1);
	return (str);
}

char	*heredoc_str(t_node *node, int i)
{
	char	*str;
	char	*ret;
	char	*new_line;

	ret = NULL;
	new_line = "\n";
	while (1)
	{
		str = readline(">");
		if (str == NULL)
			break ;
		if (ft_strncmp(str, node->redirections->infile[i], ft_strlen(str)) == 0)
		{
			free(str);
			break ;
		}
		ret = ft_strjoin_free(ret, str);
		free(str);
		ret = ft_strjoin_free(ret, new_line);
	}
	return (ret);
}

void	heredoc_write(char *ret_str, t_node *node, int fd[2])
{
	write(fd[1], ret_str, ft_strlen(ret_str));
	close(fd[1]);
	close_all_fds(node->execute->top_node);
	if (node->in_fd != 0)
		close(node->in_fd);
	exit(0);
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
				heredoc_write(ret_str, node, fd);
			node->in_fd = fd[0];
			close(fd[1]);
			waitpid(pid, NULL, 0);
			free(ret_str);
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
