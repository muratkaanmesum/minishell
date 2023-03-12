#ifndef PARSE_ERROR_H
# define PARSE_ERROR_H
# include "../../minishell.h"
void	print_error(t_token *tokens);
int		tokens_count(t_token *tokens);
int	search_token_count(t_token *tokens,
						enum e_token type_token);
int		open_parantheses(t_token *tokens);
int		is_real_subshell(t_token *tokens);
int		out_of_use(t_token *tokens);
int		less_quotes(t_token *tokens);
int		check_red(t_token *tokens);
int		token_error(t_token *tokens);
int		misuse_parantheses(t_token *tokens);
int		check_redirections(t_token *tokens);
#endif
