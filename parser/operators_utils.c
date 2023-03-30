/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 12:06:38 by eablak            #+#    #+#             */
/*   Updated: 2023/03/30 12:06:40 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	get_in_all_tokens(t_token token, t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].token != UNKNOWN)
	{
		if (token.id == tokens[i].id)
			return (i);
		i++;
	}
	return (-1);
}

int	left_is_subshell_handle(t_token *tokens, int i)
{
	while (i >= 0 && tokens[i].token != UNKNOWN && tokens[i].token != PIPE
		&& tokens[i].token != AND && tokens[i].token != OR)
		i--;
	if (i < 0)
		return (UNKNOWN);
	return (tokens[i].token);
}
