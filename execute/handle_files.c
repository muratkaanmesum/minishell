/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:56:29 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/16 12:27:38 by mmesum           ###   ########.fr       */
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

	fd = 1;
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
	int	in_fd;
	int	out_fd;

	in_fd = 0;
	out_fd = 1;
	if (head->redirections->infile_count > 0)
		in_fd = handle_infiles(head->redirections);
	if (in_fd != 0)
	{
		close(head->in_fd);
		head->in_fd = in_fd;
	}
	if (head->redirections->outfile_count > 0)
		out_fd = handle_outfiles(head->redirections);
	if (out_fd != 1)
	{
		close(head->out_fd);
		head->out_fd = out_fd;
	}
}
void	handle_files(t_node *head)
{
	int	i;

	i = 0;
	if (head->connection_count == 1 && head->redirections != NULL)
		handle_node_files(head);
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
