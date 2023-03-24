/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:21:32 by kali              #+#    #+#             */
/*   Updated: 2023/03/24 04:44:32 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

int	check_identifier(char *arg)
{
	if (ft_isalpha(arg[0]) || arg[0] == '_')
		return (1);
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	return (0);
}

void	export_w_fork(char **args, t_node *node)
{
	int	i;

	i = 0;
	if (args == NULL || args[0] == NULL)
		print_export(node);
	else
	{
		while (args[i])
		{
			if (check_identifier(args[i]) == 0)
			{
				i++;
				node->execute->last_exit_code = 1;
				continue ;
			}
			if (ft_strchr(args[i], '=') == NULL)
				add_export(args[i], node);
			else
			{
				add_export(args[i], node);
				add_env(args[i], node);
			}
			node->execute->last_exit_code = 0;
			i++;
		}
	}
	return ;
}

int	export_fork(char **args, t_node *node)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		close_all_fds(node->execute->top_node);
		if (args == NULL || args[0] == NULL)
			print_export(node);
		exit(0);
	}
	waitpid(pid, &node->execute->last_exit_code, 0);
	return (0);
}

void	export(char **args, t_node *node)
{
	if (node->right_operator != PIPE)
		export_w_fork(args, node);
	else
		export_fork(args, node);
	return ;
}
