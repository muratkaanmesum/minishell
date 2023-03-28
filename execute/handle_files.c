/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:56:29 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/28 13:28:19 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	print_infile_error(char *infile, t_node *head)
{
	char	*msg;

	msg = strerror(errno);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(infile, 2);
	write(2, " ", 1);
	ft_putendl_fd(msg, 2);
	head->in_fd = -1;
	return (-1);
}

int	handle_infiles(t_redirections *redirections, int *i)
{
	int	fd;

	fd = 0;
	while (*i < redirections->infile_count)
	{
		if (redirections->infile_type[*i] == I_REDIRECTION)
			fd = open(redirections->infile[*i], O_RDONLY, 0777);
		if (fd == -1)
			return (-1);
		if (*i + 1 < redirections->infile_count && redirections->infile_type[*i
				+ 1] == HERE_DOC && fd > 1)
		{
			close(fd);
			fd = -2;
		}
		if (redirections->infile[*i + 1] != NULL && fd > 0)
			close(fd);
		*i += 1;
	}
	return (fd);
}

int	handle_outfiles(t_redirections *redirections)
{
	int	i;
	int	fd;

	fd = 1;
	i = 0;
	while (i < redirections->outfile_count)
	{
		if (redirections->outfile_type[i] == O_REDIRECTION)
			fd = open(redirections->outfile[i], O_WRONLY | O_CREAT | O_TRUNC,
					0777);
		else if (redirections->outfile_type[i] == APPEND_RED)
			fd = open(redirections->outfile[i], O_WRONLY | O_CREAT | O_APPEND,
					0777);
		if (redirections->outfile[i + 1] != NULL && fd > 1)
			close(fd);
		i++;
	}
	return (fd);
}

void	handle_infile_loop(t_node *head)
{
	int	in_fd;
	int	i;

	i = 0;
	in_fd = 0;
	if (head->redirections->infile_count > 0)
	{
		in_fd = handle_infiles(head->redirections, &i);
		if (in_fd == -1)
		{
			print_infile_error(head->redirections->infile[i], head);
			return ;
		}
		else if (in_fd > 0)
		{
			if (head->in_fd != 0)
				close(head->in_fd);
			head->in_fd = in_fd;
		}
	}
}

void	handle_node_files(t_node *head)
{
	int	out_fd;

	out_fd = 1;
	if (head->redirections == NULL)
		return ;
	handle_infile_loop(head);
	if (head->redirections->outfile_count > 0)
	{
		out_fd = handle_outfiles(head->redirections);
		if (out_fd > 1)
		{
			if (head->out_fd != 1)
				close(head->out_fd);
			head->out_fd = out_fd;
		}
	}
}
