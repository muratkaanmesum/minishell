/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 18:25:29 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/30 11:34:05 by eablak           ###   ########.fr       */
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
		if (g_execute->exit_code == 1)
			break ;
		str = readline(">");
		if (str == NULL)
			break ;
		if (ft_strncmp(str, node->redirections->infile[i],
				len_str(node->redirections->infile[i], str)) == 0)
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
	if (g_execute->exit_code == 1)
	{
		close_all_fds(node->execute->top_node);
		close(fd[0]);
		close(fd[1]);
		exit(1);
	}
	write(fd[1], ret_str, ft_strlen(ret_str));
	close(fd[1]);
	close_all_fds(node->execute->top_node);
	if (node->in_fd != 0)
		close(node->in_fd);
	free(ret_str);
	exit(0);
}

void	heredoc_handler(int sig)
{
	(void)sig;
	g_execute->exit_code = 1;
}

void	handle_heredoc(t_node *node, int i, char *ret_str, int fd[2])
{
	signal(SIGINT, heredoc_handler);
	ret_str = heredoc_str(node, i);
	heredoc_write(ret_str, node, fd);
}
