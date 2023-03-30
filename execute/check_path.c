/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 16:58:25 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/29 19:05:46 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	check_directory(char *path, t_node *node, char **new_args)
{
	struct stat	file_stat;

	if (lstat(path, &file_stat) == 0)
	{
		if ((((file_stat.st_mode) & 0170000) == 0040000))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(node->command->command, 2);
			ft_putendl_fd(": is a directory", 2);
			node->execute->last_exit_code = 126;
			free(path);
			free_double_ptr(new_args);
			return (1);
		}
	}
	return (0);
}

int	check_file_status(char *path, t_node *node, char **new_args)
{
	if (access(path, F_OK) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(node->command->command, 2);
		ft_putendl_fd(" : No such file or directory", 2);
		node->execute->last_exit_code = 127;
		free(path);
		free_double_ptr(new_args);
		return (1);
	}
	else if (access(path, X_OK) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(node->command->command, 2);
		ft_putendl_fd(" : Permission denied", 2);
		node->execute->last_exit_code = 126;
		free(path);
		free_double_ptr(new_args);
		return (1);
	}
	return (0);
}

int	check_path(char *path, t_node *node, char **new_args)
{
	if (path == NULL)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(node->command->command, 2);
		ft_putendl_fd(": command not found", 2);
		node->execute->last_exit_code = 127;
		free(path);
		free_double_ptr(new_args);
		return (1);
	}
	if (check_file_status(path, node, new_args))
		return (1);
	if (check_directory(path, node, new_args))
		return (1);
	return (0);
}
