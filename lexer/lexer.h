/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 18:17:09 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/06 18:19:06 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "../minishell.h"

typedef struct s_lexer_args
{
	int				index;
	int				i;
	char			*str;
	int				counter;
	struct s_token	*tokens;
	int				is_redirection;
}					t_lexer_args;

int					is_redirection(char c);
int					my_alpha(char c);
int					get_token_count(char *str);
void				assign_tokens(t_token *tokens, char *str);
#endif
