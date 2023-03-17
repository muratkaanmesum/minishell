/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_subshell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 06:02:08 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/17 06:42:49 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	carry_to_command(t_node *head)
{
	int	i;

	i = 0;
	if (head->connection_count == 1)
		return ;
	else if (head->is_subshell == 0 && head->in_fd != 0)
		head->connections[0]->in_fd = head->in_fd;
	else if (head->connection_count > 0)
	{
		while (i < head->connection_count)
		{
			carry_to_command(head->connections[i]);
			i++;
		}
	}
}
void	redirect_subshell_rec(t_node *head)
{
	int	i;

	i = 0;
	if (head->connection_count == 1)
		return ;
	if (head->is_subshell == 1)
	{
		while (i < head->connection_count)
		{
			if (head->connections[i]->right_operator != PIPE)
				head->connections[i]->in_fd = head->in_fd;
			redirect_subshell(head->connections[i]);
			i++;
		}
	}
	else if (head->is_subshell == 0)
	{
	}
}
void	redirect_subshell(t_node *head)
{
	redirect_subshell_rec(head);
	carry_to_command(head);
}
