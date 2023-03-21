/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:47:38 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/21 14:36:55 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <unistd.h>

enum						e_token
{
	I_REDIRECTION,
	O_REDIRECTION,
	HERE_DOC,
	APPEND_RED,
	PIPE,
	COMMAND,
	ARG,
	OPTION,
	AND,
	OR,
	ENV_COMMAND,
	ENV,
	RED_FILE,
	OPEN_PAR,
	CLOSE_PAR,
	UNKNOWN_TOKEN,
	UNKNOWN
};
typedef struct s_redirections
{
	char					**infile;
	enum e_token			*infile_type;
	int						infile_count;
	char					**outfile;
	enum e_token			*outfile_type;
	int						outfile_count;
}							t_redirections;
typedef struct s_command
{
	char					*command;
	char					**arguments;
	int						argument_count;
}							t_command;
typedef struct s_node
{
	struct s_command		*command;
	struct s_node			**connections;
	int						connection_count;
	int						is_subshell;
	int						is_arithmetic;
	struct s_token			*tokens;
	struct s_redirections	*redirections;
	enum e_token			left_operator;
	enum e_token			right_operator;
	int						in_fd;
	int						out_fd;
	int						is_executed;
	struct s_execute		*execute;
}							t_node;

typedef struct s_execute
{
	int						last_exit_code;
	struct s_node			*top_node;
	char					**env;
	char					**export;
	int						only_red_count;
}							t_execute;

typedef struct s_token
{
	int						id;
	enum e_token			token;
	int						start_index;
	int						end_index;
	char					*str;
}							t_token;
t_token						*lexer(char *str);
t_node						*parser(t_token *tokens, t_execute *execute);
t_token						*create_redirections(t_node *node);
int							command_count(t_token *tokens);
void						handle_redirection(t_node *node);
int	connection_count(t_token *tokens,
						enum e_token token);
int							get_split_tokens(t_token *tokens);
void						assign_values(t_token *tokens, enum e_token token,
								int *i, t_token **split);
t_token						**split_token(t_token *tokens, enum e_token token);
int							check_parantheses(t_token *tokens);
t_node						*handle_connections(t_node *head, t_token *tokens,
								t_execute *execute);
void						pass_parantheses(t_token *tokens, int *i);
t_token						*remove_parantheses(t_token *tokens);
void						print_token(t_token *token);
int							does_priority(t_token *tokens, enum e_token token);
t_token						*clear_redirections(t_node *node);
void						handle_simple_command(t_node *node);
void						assign_operators(t_node *head, t_token *tokens);
int							get_in_all_tokens(t_token token, t_token *tokens);
int	left_is_subshell_handle(t_token token,
							t_token *tokens,
							int i);
int							parse_error(t_token *tokens);
void						expander(t_node *head);
int							is_arithmetic(t_token *tokens);
int							check_first(t_token *tokens);
void						wildcard(t_node *node);
void						print_tree(t_node *head);
int	handle_split_type(enum e_token split_type,
						t_node *head,
						t_token ***split);
int							get_last_execute_code(t_node *head);
;
int							execute(t_node *head);
int							free_token(t_token *tokens);
void						free_tree(t_node *head, t_token *tokens);
void						free_split(char **split);
int							get_length(char *str);
void						free_double_ptr(char **arr);
void						free_tokens_str(t_token *token);
void						ctrl_c(int sig);
void						ctrl_d(char *input, t_execute *execute);
void						free_execute(t_execute *execute);
int							get_env_len(char *env);
int							get_double_ptr_len(char **arr);
void						copy_token(t_token *dest, t_token src);
void						handle_only_red(t_node *node, t_token *tokens);
void	assign_connections(t_node *head,
						enum e_token split_type,
						t_token **split,
						t_execute *execute);
int							get_token_len(t_token *tokens);
#endif
