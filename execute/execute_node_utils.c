/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_node_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 12:19:30 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/22 08:08:05 by mmesum           ###   ########.fr       */
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

int	check_errors(t_node *node)
{
	if (node->is_arithmetic == 1)
	{
		write(2, "minishell: ", 11);
		ft_putendl_fd("Arithmetic Operator Entered", 2);
		close_node_fds(node);
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
