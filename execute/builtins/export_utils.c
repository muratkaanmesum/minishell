/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 09:33:45 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/29 16:32:33 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

void	print_export(t_node *node)
{
	int		i;
	char	**arr;

	i = 0;
	while (node->execute->export[i])
	{
		arr = ft_split(node->execute->export[i], '=');
		if (arr[1] == NULL)
			printf("declare -x %s=\"\"\n", arr[0]);
		else
			printf("declare -x %s=\"%s\"\n", arr[0], arr[1]);
		free_double_ptr(arr);
		i++;
	}
}

int	check_env_exist(char *args, t_node *node)
{
	char	**arr;
	int		i;

	arr = ft_split(args, '=');
	i = 0;
	while (i < get_export_count(node->execute->env))
	{
		if (ft_strncmp(node->execute->env[i], arr[0], ft_strlen(arr[0])) == 0)
		{
			free(node->execute->env[i]);
			node->execute->env[i] = ft_strdup(args);
			free_double_ptr(arr);
			return (1);
		}
		i++;
	}
	free_double_ptr(arr);
	return (0);
}

int	check_export_exist(char *args, t_node *node)
{
	char	**arr;
	int		i;

	arr = ft_split(args, '=');
	i = 0;
	while (i < get_export_count(node->execute->export))
	{
		if (ft_strncmp(node->execute->export[i], arr[0],
				ft_strlen(arr[0])) == 0)
		{
			free(node->execute->export[i]);
			node->execute->export[i] = ft_strdup(args);
			free_double_ptr(arr);
			return (1);
		}
		i++;
	}
	free_double_ptr(arr);
	return (0);
}

void	add_export(char *args, t_node *node)
{
	int		i;
	char	**new_export;

	if (check_export_exist(args, node))
		return ;
	new_export = malloc(sizeof(char *)
			* (get_export_count(node->execute->export) + 2));
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

	if (check_env_exist(args, node))
		return ;
	new_env = malloc(sizeof(char *) * (get_export_count(node->execute->env)
				+ 2));
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
