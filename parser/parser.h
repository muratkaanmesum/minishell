/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:26:07 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/28 15:54:28 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "../minishell.h"

t_token	*create_redirections(t_node *node);
void	handle_redirection(t_node *node);
int		connection_count(t_token *tokens, enum e_token token);
void	assign_values(t_token *tokens, enum e_token token, int *i,
			t_token **split);
t_token	**split_token(t_token *tokens, enum e_token token);
int		check_parantheses(t_token *tokens);
t_node	*handle_connections(t_node *head, t_token *tokens, t_execute *execute);
void	pass_parantheses(t_token *tokens, int *i);
t_token	*remove_parantheses(t_token *tokens);
int		does_priority(t_token *tokens, enum e_token token);
t_token	*clear_redirections(t_node *node);
void	handle_simple_command(t_node *node);
void	assign_operators(t_node *head, t_token *tokens);
int		get_in_all_tokens(t_token token, t_token *tokens);
int		left_is_subshell_handle(t_token *tokens, int i);
int		handle_split_type(enum e_token split_type,
			t_node *head, t_token ***split);
void	handle_only_red(t_node *node, t_token *tokens);
void	copy_token(t_token *dest, t_token src);
void	assign_connections(t_node *head, int split_type, t_token **split,
			t_execute *execute);
#endif
