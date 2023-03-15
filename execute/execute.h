/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:11:27 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/15 05:27:08 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H
# include "../minishell.h"
# include <sys/wait.h>
int		echo(t_node *head);
int		cd(char *args, char **env);
int		pwd(char **env);
int		print_env(char **env);
int		export(char **args, char ***env);
int		unset(char **args, char ***env);
int		get_env_len(char *env);
int		ft_exit(char **args);
void	exec_builtin(t_node *node, char **env);

#endif
