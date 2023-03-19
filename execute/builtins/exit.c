/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 13:29:59 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/19 13:30:00 by mmesum           ###   ########.fr       */
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

int	ft_exit(char **args, int last_exit_code)
{
	int	count;
	int	pid;

	count = get_arg_count(args);
	if (count == 0)
		exit(last_exit_code);
	if (is_num(args) == 0)
	{
		printf("exit\nnumeric argument required\n");
		exit(2);
	}
	else if (count > 1)
	{
		printf("exit\nminishell: exit: too many arguments\n");
		return (1);
	}
	exit(ft_atoi(args[0]));
	return (0);
}
