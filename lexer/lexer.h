/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 12:06:10 by eablak            #+#    #+#             */
/*   Updated: 2023/03/30 12:06:12 by eablak           ###   ########.fr       */
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
void				pass_character(t_lexer_args *args);
void				assign_token(t_lexer_args *args);
void				assign_redirection(t_lexer_args *args, int red_count);
void				assign_red_arg(t_lexer_args *args, int red_count);
#endif
