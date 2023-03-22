/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 13:29:59 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/22 08:40:26 by mmesum           ###   ########.fr       */
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
	free_tree(node->execute->top_node);
	free_execute(node->execute);
}
int	ft_exit(t_node *node, int last_exit_code)
{
	int		count;
	int		pid;
	char	**args;

	args = node->command->arguments;
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
