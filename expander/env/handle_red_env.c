/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_red_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 06:32:37 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/29 20:45:50 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../expander.h"

void	handle_env_infile(t_node *node, t_env *env, int i)
{
	char	*str;
	char	*env_value;

	str = NULL;
	env_value = NULL;
	str = get_env_location(node->redirections->infile[i]);
	if (str != NULL)
		env_value = find_env_variable(str, env);
	if (env_value == NULL)
		env_value = "";
	node->redirections->infile[i] = assign_env(node->redirections->infile[i],
			env_value);
}

void	handle_env_outfile(t_node *node, t_env *env, int i)
{
	char	*str;
	char	*env_value;

	str = NULL;
	env_value = NULL;
	str = get_env_location(node->redirections->outfile[i]);
	if (str != NULL)
		env_value = find_env_variable(str, env);
	if (env_value == NULL)
		env_value = "";
	node->redirections->outfile[i] = assign_env(node->redirections->outfile[i],
			env_value);
}

void	handle_redirection_env(t_node *node, t_env *env)
{
	int	i;

	i = 0;
	while (i < node->redirections->infile_count
		&& get_env_location(node->redirections->infile[i]) != NULL)
	{
		handle_env_infile(node, env, i);
		i++;
	}
	while (i < node->redirections->outfile_count
		&& get_env_location(node->redirections->outfile[i]) != NULL)
	{
		handle_env_outfile(node, env, i);
		i++;
	}
}
