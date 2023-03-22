/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:42:16 by eablak            #+#    #+#             */
/*   Updated: 2023/03/22 08:29:38 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*

    ioctl () sistem çağrısı , temel alınan cihazı yönetir
    fd bağımsız değişkeni bir olmalıdır dosya tanıtıcıyı açın.
    İkinci argüman, cihaza bağlı bir istek kodudur.
    üçüncü bağımsız değişken, belleğe yazılmamış bir işaretçidir.
    */

void	ctrl_c(int sig)
{
	(void)sig;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	write(1, "\033[A", 3);
}

void	ctrl_d(t_execute *execute)
{
	if (!execute->input)
	{
		printf("\nexit\n");
		free_execute(execute);
		exit(1);
	}
}
