/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:21:32 by kali              #+#    #+#             */
/*   Updated: 2023/03/18 13:42:28 by mmesum           ###   ########.fr       */
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
	// free_double_ptr(node->execute->env);
	node->execute->env = new_env;
}

int	export(char **args, t_node *node)
{
	int	pid;
	int	i;

	i = 0;
	pid = fork();
	if (pid == 0)
	{
		dup2(node->in_fd, 0);
		dup2(node->out_fd, 1);
		close_all_fds(node->execute->top_node);
		if (args == NULL || args[0] == NULL)
			print_export(node);
		else
		{
			while (args[i])
			{
				if (ft_strchr(args[i], '=') == NULL)
					add_export(args[i], node);
				else
				{
					add_export(args[i], node);
					add_env(args[i], node);
				}
				i++;
			}
		}
		exit(0);
	}
	waitpid(pid, &node->execute->last_exit_code, 0);
	return (0);
}
