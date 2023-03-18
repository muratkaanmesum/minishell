/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:11:27 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/18 11:38:58 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H
# include "../minishell.h"
# include <fcntl.h>
# include <sys/wait.h>
int		echo(t_node *head);
void	cd(char **args, t_node *node);
int		pwd(t_node *node);
int		print_env(t_node *node);
int		export(char **args, t_node *node);
int		unset(char **args, t_node *node);
int		get_env_len(char *env);
char	*get_env_value(char **env, char *name);
int		ft_exit(char **args, int last_exit_code);
void	exec_builtin(t_node *node);
void	handle_files(t_node *head);
void	handle_node_files(t_node *head);
void	close_all_fds(t_node *top);
void	close_node_fds(t_node *node);
int		get_last_execute_code(t_node *head);
void	redirect_subshell(t_node *head);
int		check_priority(t_node *node);
void	execute_subshell(t_node *node);
void	exec_all(t_node *head);
int		handle_priority(t_node *head, int i);
void	print_all_fds(t_node *node);
void	execute_node(t_node *node);
#endif
