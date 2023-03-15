/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:56:29 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/15 14:46:55 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	handle_infiles(t_redirections *redirections)
{
	int	i;
	int	fd;

	fd = 0;
	i = 0;
	while (redirections->infile[i] != NULL)
	{
		fd = open(redirections->infile[i], O_RDONLY, 0777);
		if (redirections->infile[i + 1] != NULL)
			close(fd);
		i++;
	}
	return (fd);
}

int	handle_outfiles(t_redirections *redirections)
{
	int	i;
	int	fd;

	fd = 0;
	i = 0;
	while (redirections->outfile[i] != NULL)
	{
		if (redirections->outfile_type[i] == O_REDIRECTION)
			fd = open(redirections->outfile[i], O_WRONLY | O_CREAT, 0777);
		else if (redirections->outfile_type[i] == APPEND_RED)
			fd = open(redirections->outfile[i], O_WRONLY | O_CREAT | O_APPEND,
					0777);
		if (redirections->outfile[i + 1] != NULL)
			close(fd);
		i++;
	}
	return (fd);
}

void	handle_node_files(t_node *head)
{
	int	fd;

	fd = 0;
	if (head->redirections->infile_count > 0)
		fd = handle_infiles(head->redirections);
	head->in_fd = fd;
	if (head->redirections->outfile_count > 0)
		fd = handle_outfiles(head->redirections);
	head->out_fd = fd;
}
void	handle_files(t_node *head)
{
	int	i;

	i = 0;
	if (head->connection_count == 1 && head->redirections != NULL)
	{
		handle_node_files(head);
	}
	else if (head->connection_count > 1)
	{
		if (head->redirections != NULL)
			handle_node_files(head);
		while (i < head->connection_count)
		{
			handle_files(head->connections[i]);
			i++;
		}
	}
}
