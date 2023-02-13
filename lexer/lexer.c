/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 13:52:33 by mmesum            #+#    #+#             */
/*   Updated: 2023/02/13 15:39:15 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*lexer(char *str)
{
	char	*t_str;
	t_token	*tokens;

	t_str = ft_strtrim(str, " ");
	tokens = malloc(sizeof(t_token) * (get_token_count(t_str) + 1));
	assign_tokens(tokens, t_str);
	free(t_str);
	return (tokens);
}
