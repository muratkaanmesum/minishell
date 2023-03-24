/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 13:29:59 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/24 02:56:49 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

int	get_arg_count(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	is_num(char **args)
{
	int	i;

	i = 0;
	while (args[0][i])
	{
		if (!ft_isdigit(args[0][i]))
			return (0);
		i++;
	}
	return (1);
}

int	free_exit(t_node *node, int exit_code)
{
	t_node	*top_node;

	top_node = node->execute->top_node;
	free_execute(node->execute);
	free_tree(top_node);
	exit(exit_code);
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
		if (is_num(args) == 0)
		{
			printf("exit\nnumeric argument required\n");
			free_exit(node, 2);
		}
		else if (count > 1)
		{
			printf("exit\nminishell: exit: too many arguments\n");
			return ;
		}
		free_exit(node, ft_atoi(args[0]));
	}
	waitpid(pid, &node->execute->last_exit_code, 0);
	return ;
}

void	ft_exit(t_node *node, int last_exit_code)
{
	int		count;
	char	**args;

	args = node->command->arguments;
	if (node->left_operator == PIPE || node->right_operator == PIPE)
	{
		(ft_exit_fork(node, last_exit_code));
		return ;
	}
	count = get_arg_count(args);
	if (count == 0)
		exit(last_exit_code);
	if (is_num(args) == 0)
	{
		printf("exit\nnumeric argument required\n");
		free_exit(node, 2);
	}
	else if (count > 1)
	{
		printf("exit\nminishell: exit: too many arguments\n");
		return (1);
	}
	free_exit(node, ft_atoi(args[0]));
	return (0);
}
