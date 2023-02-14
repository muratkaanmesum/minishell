/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:47:38 by mmesum            #+#    #+#             */
/*   Updated: 2023/02/14 16:53:28 by mmesum           ###   ########.fr       */
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
typedef struct s_redirections
{
	char					*infile;
	char					*outfile;
}							t_redirections;
typedef struct s_command
{
	char					*command;
	char					*option;
	char					**argument;
	struct s_redirections	*redirections;
	struct s_command		*next;
}							t_command;

typedef struct s_lexer_args
{
	int						index;
	int						i;
	char					*str;
	int						counter;
	struct s_token			*tokens;
}							t_lexer_args;
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
	UNKNOWN
};
typedef struct s_token
{
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
t_redirections				*create_redirections(t_token *tokens);
int							command_count(t_token *tokens);
#endif
