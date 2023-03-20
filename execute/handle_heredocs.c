/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredocs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:31:36 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/20 21:09:03 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	heredoc_str(t_node *node, int i)
{
	char	*str;

	while (1)
	{
		str = readline(">");
		printf("%s\n", str);
		if (ft_strncmp(str, node->redirections->infile[i], ft_strlen(str)) == 0)
			break ;
	}
}

void	handle_node_heredoc(t_node *node)
{
	int	i;

	/*
		1) infile sayısı kadar dön
		2) readline ile kelimeleri al + join ile \n ekle ve birleştir
		3) fd[2] aç, pipe'la
		4) fd[1] e yaz
		5) fd[0] dan okunur
		6) in_fd != 0 (yani pipe'lanmıştır o zaman close yap)
	*/
	// int fd[2];
	// while(i < count)
	// {
	// 	heredoc_loop();
	// }
	// while(1){
	// 	char *str = readline(">");
	// 	//join
	// 	BREAK;
	// }
	// if()
	// pipe(fd);
	// fd[0];
	// write(fd[1],str,ft_strlen(str));
	// if(in_fd != 0)
	// 	close(fd);
	// 	node->in_fd = fd[0];
	i = 0;
	while (i < node->redirections->infile_count)
	{
		heredoc_str(node, i);
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
