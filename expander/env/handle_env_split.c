/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 07:39:31 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/26 12:18:43 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../expander.h"

void	handle_env_split(t_node *node)
{
	int	i;

	i = 0;
	if (node->connection_count == 0)
		handle_node_env_split(node);
	else if (node->connection_count >= 1)
	{
		while (i < node->connection_count)
			handle_env_split(node->connections[i++]);
	}
}
