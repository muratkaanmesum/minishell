/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_node_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 13:09:13 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/30 10:21:01 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../expander.h"

void	handle_env_command(t_node *node, t_env *env)
{
	char	*str;
	char	*env_value;

	str = NULL;
	env_value = NULL;
	str = get_env_location(node->command->command);
	if (str != NULL)
		env_value = find_env_variable(str, env);
	if (env_value == NULL)
		env_value = "";
	node->command->command = assign_env(node->command->command, env_value);
}

void	handle_env_arg(t_node *node, t_env *env, int i)
{
	char	*str;
	char	*env_value;

	str = NULL;
	env_value = NULL;
	str = get_env_location(node->command->arguments[i]);
	if (str != NULL)
		env_value = find_env_variable(str, env);
	if (env_value == NULL)
		env_value = "";
	node->command->arguments[i] = assign_env(node->command->arguments[i],
			env_value);
}

void	handle_node_env(t_node *node, t_env *env)
{
	int	i;

	if (node->command == NULL)
		return ;
	while (get_env_location(node->command->command) != NULL)
		handle_env_command(node, env);
	i = 0;
	while (i < node->command->argument_count)
	{
		while (get_env_location(node->command->arguments[i]) != NULL)
			handle_env_arg(node, env, i);
		i++;
	}
	if (node->redirections != NULL)
		handle_redirection_env(node, env);
	handle_all_exec_code(node);
	handle_env_split(node);
}
