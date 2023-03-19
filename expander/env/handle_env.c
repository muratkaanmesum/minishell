/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:02:41 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/03 13:27:58 by mmesum           ###   ########.fr       */

/*   Updated: 2023/03/03 12:24:29 by mmesum           ###   ########.fr       */

/*                                                                            */
/* ************************************************************************** */

#include "../expander.h"

void	assign_node_env(t_node *node, t_env *env)
{
	int	i;

	i = 0;
	if (node->connection_count == 1 && node->is_arithmetic == 0)
		handle_node_env(node, env);
	else if (node->connection_count > 1)
		while (i < node->connection_count)
			assign_node_env(node->connections[i++], env);
}
void	handle_env(t_node *node, t_env *variables)
{
	assign_node_env(node, variables);
}
