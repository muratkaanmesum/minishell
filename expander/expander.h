/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 12:52:46 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/28 14:35:03 by eablak           ###   ########.fr       */
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
typedef struct s_str
{
	int		i;
	int		index;
	int		flag;
	int		q_flag;
	int		start_index;

}			t_str;

typedef struct s_new_str
{
	int		i;
	int		keep;
	int		j;
	int		outside_double;
	int		outside_single;

}			t_new_str;
void		handle_env(t_node *node, t_env *variables);
t_env		*get_env_variables(char **env);
char		*find_env_variable(char *value, t_env *env);
char		*get_env_location(char *str);
char		*assign_env(char *str, char *env_value);
void		handle_node_env(t_node *node, t_env *env);
void		free_env(t_env *env);
void		delete_all_quotes(t_node *node);
t_token		*get_token(t_node *node, char *str, enum e_token token, int index);
void		assign_env_value(char *new_str, char *env_value, int *index);
void		assign_default_values(int *i, int *in_quote, int *flag);
void		pass_env(char *str, int start_index, int *i);
void		handle_all_exec_code(t_node *node);
void		handle_redirection_env(t_node *node, t_env *env);
void		handle_env_split(t_node *node);
void		handle_node_env_split(t_node *node);
int			check_env_stop(char *str, int i);
void		pass_single_quote(char *str, int *i);
void		change_str(char *str, char *env_value, char *new_str);
void		get_new_str(char *new_str, char *str);
void		single_quotes(t_new_str *new, char *str, char *new_str);
void		double_quotes(t_new_str *new, char *str, char *new_str);
#endif
