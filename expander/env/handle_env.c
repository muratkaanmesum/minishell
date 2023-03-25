/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:02:41 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/23 05:11:40 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../expander.h"

void	assign_node_env(t_node *node, t_env *env)
{
	int	i;

	i = 0;
	if (node->connection_count == 0 && node->is_arithmetic == 0
		&& node->command != NULL)
		handle_node_env(node, env);
	else if (node->connection_count >= 1)
		while (i < node->connection_count)
			assign_node_env(node->connections[i++], env);
}

void	handle_env(t_node *node, t_env *variables)
{
	assign_node_env(node, variables);
}
