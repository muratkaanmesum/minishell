/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:22:33 by eablak            #+#    #+#             */
/*   Updated: 2023/03/29 15:11:45 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

void	handle_wildcard(t_node *node)
{
	int	i;

	if (node->connection_count == 0 && node->is_arithmetic == 0
		&& node->command != NULL)
		handle_node_wildcard(node);
	else if (node->connection_count >= 1)
	{
		i = 0;
		while (i < node->connection_count)
		{
			handle_wildcard(node->connections[i]);
			i++;
		}
	}
}

void	wildcard(t_node *node)
{
	handle_wildcard(node);
	ambiguous(node);
}
