/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 09:33:45 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/19 09:50:20 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

int	get_env_count(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
		i++;
	return (i);
}

void	print_export(t_node *node)
{
	int		i;
	char	**arr;

	i = 0;
	while (node->execute->export[i])
	{
		arr = ft_split(node->execute->export[i], '=');
		if (arr[1] == NULL)
			arr[1] = ft_strdup("");
		printf("declare -x %s=\"%s\"\n", arr[0], arr[1]);
		free_double_ptr(arr);
		i++;
	}
}

void	add_export(char *args, t_node *node)
{
	int		i;
	char	**new_export;

	new_export = malloc(sizeof(char *) * (get_env_count(node->execute->export)
				+ 2));
	i = 0;
	while (node->execute->export[i] != NULL)
	{
		new_export[i] = ft_strdup(node->execute->export[i]);
		i++;
	}
	new_export[i] = ft_strdup(args);
	new_export[i + 1] = NULL;
	free_double_ptr(node->execute->export);
	node->execute->export = new_export;
}

void	add_env(char *args, t_node *node)
{
	int		i;
	char	**new_env;

	new_env = malloc(sizeof(char *) * (get_env_count(node->execute->env) + 2));
	i = 0;
	while (node->execute->env[i])
	{
		new_env[i] = ft_strdup(node->execute->env[i]);
		i++;
	}
	new_env[i] = ft_strdup(args);
	new_env[i + 1] = NULL;
	free_double_ptr(node->execute->env);
	node->execute->env = new_env;
}
