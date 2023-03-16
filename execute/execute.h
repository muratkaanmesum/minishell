/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:11:27 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/16 17:02:55 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H
# include "../minishell.h"
# include <fcntl.h>
# include <sys/wait.h>
int		echo(t_node *head);
int		cd(char *args, t_node *node);
int		pwd(t_node *node);
int		print_env(t_node *node);
int		export(char **args, t_node *node);
int		unset(char **args, t_node *node);
int		get_env_len(char *env);
int		ft_exit(char **args);
void	exec_builtin(t_node *node);
void	handle_files(t_node *head);
void	close_all_fds(t_node *top);
void	close_node_fds(t_node *node);
#endif
