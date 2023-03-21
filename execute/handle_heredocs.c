/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredocs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:31:36 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/21 12:52:54 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

char	*heredoc_str(t_node *node, int i)
{
	enum e_token	*in_type;
	char			*str;
	char			*ret;
	char			*new_line;

	// printf("!%u\n", node->redirections->infile_type[i]);
	// printf("infile count %d\n", node->redirections->infile_count);
	ret = "";
	new_line = "\n";
	while (1)
	{
		str = readline(">");
		if (ft_strncmp(str, node->redirections->infile[i], ft_strlen(str)) == 0)
			break ;
		ret = ft_strjoin(ret, str);
		ret = ft_strjoin(ret, new_line);
	}
	return (ret);
}

void	handle_node_heredoc(t_node *node)
{
	int		i;
	int		fd[2];
	char	*ret_str;

	i = 0;
	//printf("count %d\n",node->redirections->infile_count);
	while (i < node->redirections->infile_count
		&& node->redirections->infile_type[i] == 2)
	{
		ret_str = heredoc_str(node, i);
		printf("--> %s", ret_str);
		write(fd[1], &ret_str, ft_strlen(ret_str));
		if (node->in_fd != 0)
			close(fd);
		pipe(fd);
		node->out_fd = fd[1];
		node->in_fd = fd[0];
		printf("in fd %d\n", node->in_fd);
		printf("out fd %d\n", node->out_fd);
		i++;
	}
	// printf("---\n");
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
