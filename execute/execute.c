/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 05:22:49 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/15 08:25:28 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	execute_node(t_node *node, char ***env)
{
	// if (ft_strncmp(node->command->command, "pwd", 3) == 0)
	// 	pwd(*env);
	// else if (ft_strncmp(node->command->command, "cd", 2) == 0)
	// 	cd(node->command->arguments[0], *env);
	// else if (ft_strncmp(node->command->command, "echo", 4) == 0)
	// 	echo(node);
	// else if (ft_strncmp(node->command->command, "env", 3) == 0)
	// 	print_env(*env);
	// else if (ft_strncmp(node->command->command, "export", 6) == 0)
	// 	export(node->command->arguments, env);
	// else if (ft_strncmp(node->command->command, "unset", 5) == 0)
	// 	unset(node->command->arguments, env);
	// else if (ft_strncmp(node->command->command, "exit", 4) == 0)
	// 	exit(0);
	// else
	exec_builtin(node, *env);
}
int	execute_rec(t_node *head, char ***env)
{
	int	i;

	i = 0;
	if (head->connection_count == 1)
		execute_node(head, env);
	else if (head->connection_count > 1)
		while (i < head->connection_count)
		{
			execute_rec(head->connections[i], env);
			i++;
		}
}
int	execute(t_node *head, char ***env)
{
	execute_rec(head, env);
	waitpid(-1, NULL, 0);
	return (0);
}
