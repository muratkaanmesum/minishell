/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_node_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 12:19:30 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/29 19:05:56 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

char	*check_in_path(char *command, char *path)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin(path, "/");
	tmp2 = ft_strjoin(tmp, command);
	if (access(tmp2, F_OK) == 0)
	{
		free(tmp);
		return (tmp2);
	}
	free(tmp);
	free(tmp2);
	return (NULL);
}

int	handle_outfile_ambg(t_node *node)
{
	int	i;

	i = 0;
	while (node->redirections->outfile[i] != NULL)
	{
		if (strchr(node->redirections->outfile[i], '*') != NULL)
		{
			write(2, "minishell:*: ", 11);
			ft_putendl_fd("ambiguous redirect", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_ambigious(t_node *node)
{
	int	i;

	if (node->redirections == NULL)
		return (0);
	i = 0;
	while (node->redirections->infile[i] != NULL)
	{
		if (strchr(node->redirections->infile[i], '*') != NULL
			&& node->redirections->infile_type[i] != HERE_DOC)
		{
			write(2, "minishell:*:", 11);
			ft_putendl_fd("ambiguous redirect", 2);
			return (1);
		}
		i++;
	}
	if (handle_outfile_ambg(node) == 1)
		return (1);
	return (0);
}

int	check_errors(t_node *node)
{
	if (node->is_arithmetic == 1)
	{
		write(2, "minishell:*:", 11);
		ft_putendl_fd("Arithmetic Operator Entered", 2);
		close_node_fds(node);
		node->execute->last_exit_code = 1;
		return (1);
	}
	expander(node);
	if (check_ambigious(node) == 1)
	{
		close_node_fds(node);
		node->execute->last_exit_code = 1;
		return (1);
	}
	handle_node_files(node);
	if (node->command == NULL)
	{
		close_node_fds(node);
		return (1);
	}
	return (0);
}
