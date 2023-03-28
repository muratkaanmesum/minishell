/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 03:34:52 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/27 06:50:56 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

int	is_num(char **args)
{
	int	i;

	i = 0;
	while (args[0][i])
	{
		if (args[0][0] == '-' && i == 0)
			i++;
		if (!ft_isdigit(args[0][i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_exit_errors(t_node *node, char **args, int count)
{
	if (is_num(args) == 0)
	{
		ft_putendl_fd("exit", 2);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putendl_fd("numeric argument required", 2);
		free_exit(node, 2);
	}
	else if (count > 1)
	{
		ft_putendl_fd("exit", 2);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putendl_fd("too many arguments", 2);
		return (1);
	}
	return (0);
}
