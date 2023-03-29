/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:47:38 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/29 16:24:14 by mmesum           ###   ########.fr       */
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

extern struct s_execute		*g_execute;

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
	struct s_execute		*execute;
}							t_node;

typedef struct s_execute
{
	int						last_exit_code;
	struct s_node			*top_node;
	char					**env;
	char					**export;
	int						only_red_count;
	char					*input;
	int						exit_code;
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
void						print_token(t_token *token);
int							parse_error(t_token *tokens);
void						expander(t_node *head);
int							is_arithmetic(t_token *tokens);
int							check_first(t_token *tokens);
void						wildcard(t_node *node);
void						print_tree(t_node *head);
int							get_last_execute_code(t_node *head);
int							execute(t_node *head);
void						free_tree(t_node *head);
int							get_length(char *str);
void						free_double_ptr(char **arr);
void						free_tokens(t_token *token);
void						ctrl_c(int sig);
void						ctrl_d(t_execute *execute);
void						free_execute(t_execute *execute);
int							get_env_len(char *env);
int							get_double_ptr_len(char **arr);
int							get_token_len(t_token *tokens);
void						exec_rest(t_node *head);
int							parse_error_free(t_node *head, t_token *tokens,
								char *inpt);
int							first_check_free(t_token *tokens, char *inpt);
void						free_all_node_tokens(t_node *node);
int							quotes_control(char *command);
#endif
