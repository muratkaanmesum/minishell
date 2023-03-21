/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 12:52:46 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/21 13:17:31 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H
# include "../minishell.h"
typedef struct s_env
{
	char	*name;
	char	*value;
}			t_env;
void		handle_env(t_node *node, t_env *variables);
t_env		*get_env_variables(char **env, t_node *node);
char		*find_env_variable(char *value, t_env *env);
char		*get_env_location(char *str);
char		*assign_env(char *str, char *env_value, t_node *node);
void		handle_node_env(t_node *node, t_env *env);
void		free_env(t_env *env);
void		delete_all_quotes(t_node *node);
t_token		*get_token(t_node *node, char *str, enum e_token token, int index);
void		assign_env_value(char *new_str, char *env_value, int *index);
void		assign_default_values(int *i, int *in_quote, int *flag);
void		pass_env(char *str, int start_index, int *i);
void		handle_all_exec_code(t_node *node);
void		handle_redirection_env(t_node *node, t_env *env);
int			check_env_stop(char *str, int i);
#endif
