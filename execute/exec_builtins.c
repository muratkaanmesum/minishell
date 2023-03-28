/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 05:22:18 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/28 13:23:09 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

char	*find_in_path(char *command, char **env)
{
	int		i;
	char	**path;
	char	*path_str;
	char	*val;

	path_str = get_env_value(env, "PATH");
	if (path_str == NULL)
		return (NULL);
	path = ft_split(path_str, ':');
	i = 0;
	while (path[i])
	{
		val = check_in_path(command, path[i]);
		if (val != NULL)
		{
			free_double_ptr(path);
			return (val);
		}
		i++;
	}
	free_double_ptr(path);
	return (NULL);
}

void	print_new_arg(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		printf("%s\n", arg[i]);
		i++;
	}
}

char	**modified_args(t_node *node)
{
	char	**new_args;
	int		i;
	int		j;

	i = 1;
	j = 0;
	new_args = malloc(sizeof(char *) * (node->command->argument_count + 2));
	new_args[0] = ft_strdup(node->command->command);
	while (j < node->command->argument_count)
	{
		new_args[i] = ft_strdup(node->command->arguments[j]);
		i++;
		j++;
	}
	new_args[i] = NULL;
	return (new_args);
}

void	exec_node(t_node *node, char *path, char **new_args)
{
	if (node->in_fd == -1)
		exit(1);
	dup2(node->in_fd, 0);
	dup2(node->out_fd, 1);
	close_all_fds(node->execute->top_node);
	execve(path, new_args, node->execute->env);
	exit(1);
}

void	exec_builtin(t_node *node)
{
	char	*path;
	int		pid;
	char	**new_args;

	new_args = modified_args(node);
	path = NULL;
	if (ft_strchr(node->command->command, '/') == NULL)
		path = find_in_path(node->command->command, node->execute->env);
	else
		path = ft_strdup(node->command->command);
	if (check_path(path, node, new_args))
		return ;
	pid = fork();
	if (pid == 0)
		exec_node(node, path, new_args);
	free(path);
	free_double_ptr(new_args);
}
