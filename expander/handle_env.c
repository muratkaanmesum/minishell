/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:02:41 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/02 16:40:16 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	handle_env_command(t_node *node, t_env *env)
{
	char	*str;
	char	*env_value;
	int		i;

	str = get_env_location(node->command->command);
	if (str != NULL)
		env_value = find_env_variable(str, env);
	node->command->command = assign_env(str, env_value);
	i = 0;
}

void	handle_node_env(t_node *node, t_env *env)
{
	int	i;

	while (get_env_location(node->command->command) != NULL)
		handle_env_command(node, env);
	i = 0;
	// while (i < node->command->argument_count)
	// {
	// 	while (get_env_location(node->command->arguments[i]) != NULL)
	// 		handle_env_arg(node, env);
	// }
}

void	assign_node_env(t_node *node, t_env *env)
{
	int	i;

	i = 0;
	if (node->connection_count == 1)
		handle_node_env(node, env);
	else if (node->connection_count > 1)
		while (i < node->connection_count)
			assign_node_env(node->connections[i++], env);
}
void	handle_env(t_node *node, char **env)
{
	t_env	*variables;

	//empty string segfaults
	variables = get_env_variables(env);
	assign_node_env(node, variables);
}
