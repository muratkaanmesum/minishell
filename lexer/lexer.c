/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 13:52:33 by mmesum            #+#    #+#             */
/*   Updated: 2023/02/14 14:38:35 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_tokens(t_token *tokens)
{
	if (tokens[0].token == I_REDIRECTION || tokens[0].token == HERE_DOC
		|| tokens[0].token == APPEND_RED || tokens[0].token == O_REDIRECTION)
		tokens[2].token = COMMAND;
}
t_token	*lexer(char *str)
{
	char	*t_str;
	t_token	*tokens;
	int		i;

	t_str = ft_strtrim(str, " ");
	tokens = malloc(sizeof(t_token) * (get_token_count(t_str) + 1));
	assign_tokens(tokens, t_str);
	tokens[get_token_count(t_str)].token = UNKNOWN;
	i = 0;
	while (tokens[i].token != UNKNOWN)
	{
		tokens[i].str = ft_substr(t_str, tokens[i].start_index,
				tokens[i].end_index - tokens[i].start_index);
		i++;
	}
	free(t_str);
	check_tokens(tokens);
	return (tokens);
}
