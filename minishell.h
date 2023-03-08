/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:47:38 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/08 17:22:23 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
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
	char					**options;
	int						option_count;
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
}							t_node;
typedef struct s_token
{
	int						id;
	enum e_token			token;
	int						start_index;
	int						end_index;
	char					*str;
}							t_token;
t_token						*lexer(char *str);
t_node						*parser(t_token *tokens);
t_token						*create_redirections(t_node *node);
int							command_count(t_token *tokens);
void						handle_redirection(t_node *node);
int	connection_count(t_token *tokens,
						enum e_token token);
int							get_split_tokens(t_token *tokens);
t_token						**split_token(t_token *tokens, enum e_token token);
int							check_parantheses(t_token *tokens);
t_node	*handle_connections(t_node *head,
							t_token *tokens);
void						pass_parantheses(t_token *tokens, int *i);
t_token						*remove_parantheses(t_token *tokens);
void						print_token(t_token *token);
int							does_priority(t_token *tokens, enum e_token token);
t_token						*clear_redirections(t_node *node);
void						handle_simple_command(t_node *node);
int							parse_error(t_token *tokens);
void						expander(t_node *head, char **env);
int							is_arithmetic(t_token *tokens);
int							check_first(t_token *tokens);

int							execute(t_node *head, char **env);
#endif
