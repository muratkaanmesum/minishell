/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:11:27 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/16 14:44:56 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H
# include "../minishell.h"
# include <fcntl.h>
# include <sys/wait.h>
int		echo(t_node *head);
int		cd(char *args, char **env, t_node *node);
int		pwd(char **env, t_node *node);
int		print_env(char **env, t_node *node);
int		export(char **args, char ***env, t_node *node);
int		unset(char **args, char ***env, t_node *node);
int		get_env_len(char *env);
int		ft_exit(char **args);
void	exec_builtin(t_node *node, char **env);
void	handle_files(t_node *head);
#endif
