/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:11:27 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/30 11:33:59 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H
# include "../minishell.h"
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>

int		echo(t_node *head);
void	cd(char **args, t_node *node);
int		pwd(t_node *node);
int		print_env(t_node *node);
void	export(char **args, t_node *node);
void	add_env(char *args, t_node *node);
void	add_export(char *args, t_node *node);
void	print_export(t_node *node);
int		unset(char **args, t_node *node);
char	*get_env_value(char **env, char *name);
int		check_exit_errors(t_node *node, char **args, int count);
int		free_exit(t_node *node, int exit_code);
void	ft_exit(t_node *node, int last_exit_code);
void	exec_builtin(t_node *node);
void	exec_single_command(t_node *node);
void	handle_node_files(t_node *head);
void	close_all_fds(t_node *top);
void	close_node_fds(t_node *node);
void	execute_subshell(t_node *node);
void	exec_all(t_node *head);
int		handle_priority(t_node *head, int i);
void	print_all_fds(t_node *node);
void	execute_node(t_node *node);
int		get_export_count(char **env);
int		check_errors(t_node *node);
char	*check_in_path(char *command, char *path);
void	handle_heredocs(t_node *node);
int		check_path(char *path, t_node *node, char **new_args);
void	heredoc_handler(int sig);
void	handle_heredoc(t_node *node, int i, char *ret_str, int fd[2]);
int		check_size(t_node *node, char *command);
int		len_str(char *arg, char *str);
#endif
