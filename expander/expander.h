/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 12:52:46 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/08 18:17:33 by mmesum           ###   ########.fr       */
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
t_env		*get_env_variables(char **env);
char		*find_env_variable(char *value, t_env *env);
char		*get_env_location(char *str);
char		*assign_env(char *str, char *env_value, t_node *node);
void		handle_node_env(t_node *node, t_env *env);
void		free_env(t_env *env);
char		*delete_quotes(char *str, t_node *node);
t_token		*get_token(t_node *node, char *str);
#endif
