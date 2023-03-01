/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:47:38 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/01 15:02:17 by mmesum           ###   ########.fr       */
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
	char					*option;
	char					**argument;
	struct s_redirections	*redirections;
}							t_command;
typedef struct s_node
{
	struct s_command		*command;
	struct s_node			**connections;
	int						connection_count;
	int						is_subshell;
	struct s_token			*tokens;
	struct s_redirections	*redirections;
}							t_node;
typedef struct s_lexer_args
{
	int						index;
	int						i;
	char					*str;
	int						counter;
	struct s_token			*tokens;
	int						is_redirection;
}							t_lexer_args;

typedef struct s_token
{
	int						id;
	enum e_token			token;
	int						start_index;
	int						end_index;
	char					*str;
}							t_token;
t_token						*lexer(char *str);
int							my_alpha(char c);
int							is_redirection(char c);
int							get_token_count(char *str);
void						assign_tokens(t_token *tokens, char *str);
void						parser(t_token *tokens);
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
#endif
