/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 13:29:59 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/28 12:54:41 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

int	free_exit(t_node *node, int exit_code)
{
	t_node	*top_node;

	top_node = node->execute->top_node;
	free_execute(node->execute);
	free_tree(top_node);
	printf("exit\n");
	exit(exit_code);
}

int	get_arg_count(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

void	ft_exit_fork(t_node *node, int last_exit_code)
{
	int		count;
	char	**args;
	int		pid;

	args = node->command->arguments;
	pid = fork();
	if (pid == 0)
	{
		count = get_arg_count(args);
		if (count == 0)
			exit(last_exit_code);
		check_exit_errors(node, args, count);
		free_exit(node, ft_atoi(args[0]));
	}
	waitpid(pid, &node->execute->last_exit_code, 0);
	return ;
}

void	ft_exit(t_node *node, int last_exit_code)
{
	int			count;
	char		**args;
	long long	val;

	args = node->command->arguments;
	if (node->left_operator == PIPE || node->right_operator == PIPE)
	{
		(ft_exit_fork(node, last_exit_code));
		return ;
	}
	count = get_arg_count(args);
	if (count == 0)
		free_exit(node, last_exit_code % 256);
	if (check_exit_errors(node, args, count))
		return ;
	val = ft_atoi(args[0]);
	free_exit(node, val);
	return ;
}
