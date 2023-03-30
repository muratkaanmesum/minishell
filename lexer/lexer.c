/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 13:52:33 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/30 11:52:18 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	add_str(t_token *tokens, char *t_str)
{
	int	i;

	i = 0;
	while (tokens[i].token != UNKNOWN)
	{
		tokens[i].str = ft_substr(t_str, tokens[i].start_index,
				tokens[i].end_index - tokens[i].start_index);
		tokens[i].id = i;
		i++;
	}
	tokens[i].str = NULL;
}

t_token	*lexer(char *str)
{
	char	*t_str;
	t_token	*tokens;

	if (ft_strlen(str) == 0)
		return (NULL);
	t_str = ft_strtrim(str, " ");
	if (ft_strlen(t_str) == 0)
	{
		free(t_str);
		return (NULL);
	}
	tokens = malloc(sizeof(t_token) * (get_token_count(t_str) + 1));
	assign_tokens(tokens, t_str);
	tokens[get_token_count(t_str)].token = UNKNOWN;
	add_str(tokens, t_str);
	free(t_str);
	return (tokens);
}
