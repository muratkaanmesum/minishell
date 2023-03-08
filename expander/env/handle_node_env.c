/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_node_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 13:09:13 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/08 18:02:21 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../expander.h"

void	handle_env_command(t_node *node, t_env *env)
{
	char	*str;
	char	*env_value;
	int		i;

	str = get_env_location(node->command->command);
	if (str != NULL)
		env_value = find_env_variable(str, env);
	if (env_value == NULL)
		env_value = "";
	node->command->command = assign_env(node->command->command, env_value,
			node);
}

void	handle_env_arg(t_node *node, t_env *env, int i)
{
	char	*str;
	char	*env_value;

	str = get_env_location(node->command->arguments[i]);
	if (str != NULL)
		env_value = find_env_variable(str, env);
	if (env_value == NULL)
		env_value = "";
	node->command->arguments[i] = assign_env(node->command->arguments[i],
												env_value,
												node);
}

void	handle_env_infile(t_node *node, t_env *env, int i)
{
	char	*str;
	char	*env_value;

	str = get_env_location(node->redirections->infile[i]);
	if (str != NULL)
		env_value = find_env_variable(str, env);
	if (env_value == NULL)
		env_value = "";
	node->redirections->infile[i] = assign_env(node->redirections->infile[i],
												env_value,
												node);
}
void	handle_env_outfile(t_node *node, t_env *env, int i)
{
	char	*str;
	char	*env_value;

	str = get_env_location(node->redirections->outfile[i]);
	if (str != NULL)
		env_value = find_env_variable(str, env);
	if (env_value == NULL)
		env_value = "";
	node->redirections->outfile[i] = assign_env(node->redirections->outfile[i],
												env_value,
												node);
}
void	handle_node_env(t_node *node, t_env *env)
{
	int	i;

	while (get_env_location(node->command->command) != NULL)
		handle_env_command(node, env);
	node->command->command = delete_quotes(node->command->command);
	i = 0;
	while (i < node->command->argument_count)
	{
		while (get_env_location(node->command->arguments[i]) != NULL)
			handle_env_arg(node, env, i);
		node->command->arguments[i] = delete_quotes(node->command->arguments[i]);
		i++;
	}
	i = 0;
	if (node->redirections == NULL)
		return ;
	while (i < node->redirections->infile_count)
	{
		while (get_env_location(node->redirections->infile[i]) != NULL)
			handle_env_infile(node, env, i);
		node->redirections->infile[i] = delete_quotes(node->redirections->infile[i]);
		i++;
	}
	i = 0;
	while (i < node->redirections->outfile_count)
	{
		while (get_env_location(node->redirections->outfile[i]) != NULL)
			handle_env_outfile(node, env, i);
		node->redirections->outfile[i] = delete_quotes(node->redirections->outfile[i]);
		i++;
	}
}
