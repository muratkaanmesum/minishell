/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 05:22:18 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/19 12:44:36 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

char	*find_in_path(char *command, char **env)
{
	int		i;
	char	**path;
	char	*tmp;
	char	*tmp2;

	path = ft_split(get_env_value(env, "PATH"), ':');
	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		tmp2 = ft_strjoin(tmp, command);
		if (access(tmp2, F_OK) == 0)
		{
			free(tmp);
			free_double_ptr(path);
			return (tmp2);
		}
		i++;
		free(tmp);
		free(tmp2);
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

int	check_path(char *path, t_node *node)
{
	if (path == NULL)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(node->command->command, 2);
		ft_putendl_fd(": command not found", 2);
		node->execute->last_exit_code = 127;
		return (1);
	}
	else if (access(path, F_OK) != 0)
	{
		printf("minishell: %s: No such file or directory\n",
				node->command->command);
		node->execute->last_exit_code = 127;
		return (1);
	}

	return (0);
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

void	exec_builtin(t_node *node)
{
	char	*path;
	int		pid;
	int		return_value;
	char	**new_args;

	new_args = modified_args(node);
	return_value = 0;
	path = NULL;
	if (ft_strchr(node->command->command, '/') == NULL)
		path = find_in_path(node->command->command, node->execute->env);
	else
		path = ft_strdup(node->command->command);
	if (check_path(path, node))
		return ;
	pid = fork();
	if (pid == 0)
	{
		if (node->in_fd == -1)
			exit(1);
		dup2(node->in_fd, 0);
		dup2(node->out_fd, 1);
		close_all_fds(node->execute->top_node);
		execve(path, new_args, node->execute->env);
	}
	free(path);
	free_double_ptr(new_args);
	waitpid(pid, &node->execute->last_exit_code, 0);
}
