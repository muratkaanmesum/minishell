/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 07:46:00 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/24 04:15:43 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

void	change_pwd(char **env, char *buf, char *old_pwd_buff)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
		{
			free(env[i]);
			env[i] = ft_strjoin("PWD=", buf);
		}
		if (ft_strncmp(env[i], "OLDPWD=", 7) == 0)
		{
			free(env[i]);
			env[i] = ft_strjoin("OLDPWD=", old_pwd_buff);
		}
		i++;
	}
}

int	check_arg(char **args, t_node *node)
{
	if (args == NULL || args[0] == NULL)
	{
		args[0] = get_env_value(node->execute->env, "HOME");
		if (args[0] == NULL)
		{
			node->execute->last_exit_code = 1;
			return (0);
		}
	}
	return (1);
}

int	check_arg_count(char **args, t_node *node)
{
	int	i;

	i = 0;
	while (args[i] != NULL)
		i++;
	if (i > 1)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		node->execute->last_exit_code = 1;
		return (0);
	}
	return (1);
}

void	cd(char **args, t_node *node)
{
	char	buf[1024];
	char	old_pwd_buff[1024];
	char	*str;

	if (check_arg_count(args, node) == 0)
		return ;
	if (check_arg(args, node) == 0)
		return ;
	getcwd(old_pwd_buff, 1024);
	if (chdir(args[0]) == -1)
	{
		str = strerror(errno);
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(" ", 2);
		ft_putstr_fd(str, 2);
		ft_putchar_fd('\n', 2);
		node->execute->last_exit_code = 1;
		return ;
	}
	getcwd(buf, 1024);
	change_pwd(node->execute->env, buf, old_pwd_buff);
	node->execute->last_exit_code = 0;
	return ;
}
