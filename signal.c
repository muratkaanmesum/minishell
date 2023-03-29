/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:42:16 by eablak            #+#    #+#             */
/*   Updated: 2023/03/29 16:29:50 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_c(int sig)
{
	(void)sig;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	write(1, "\033[A", 3);
	rl_on_new_line();
	rl_redisplay();
	g_execute->last_exit_code = 130;
}

void	ctrl_d(t_execute *execute)
{
	int	last_exec_code;

	last_exec_code = execute->last_exit_code;
	if (!execute->input)
	{
		printf("\nexit\n");
		free_execute(execute);
		exit(last_exec_code);
	}
}
