/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 07:10:27 by kali              #+#    #+#             */
/*   Updated: 2023/03/21 15:33:49 by mmesum           ###   ########.fr       */
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

int	left_is_subshell_handle(t_token token, t_token *tokens, int i)
{
	while (i >= 0 && tokens[i].token != UNKNOWN && tokens[i].token != PIPE
		&& tokens[i].token != AND && tokens[i].token != OR)
		i--;
	if (i < 0)
		return (UNKNOWN);
	return (tokens[i].token);
}
