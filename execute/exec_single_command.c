/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 07:27:05 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/29 14:59:20 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	exec_single_command(t_node *node)
{
	execute_node(node);
	waitpid(-1, &node->execute->last_exit_code, 0);
}
