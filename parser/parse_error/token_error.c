/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 14:31:46 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/23 14:43:37 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_error.h"

int	is_command(t_token *tokens, int start)
{
	if (tokens[start + 1].token == ARG)
		return (1);
	if (tokens[start + 1].token != PIPE
		&& tokens[start + 1].token != AND
		&& tokens[start + 1].token != OR
		&& tokens[start + 1].token != UNKNOWN
		&& tokens[start + 1].token != CLOSE_PAR
		&& tokens[start + 1].token != I_REDIRECTION
		&& tokens[start + 1].token != O_REDIRECTION
		&& tokens[start + 1].token != APPEND_RED
		&& tokens[start + 1].token != HERE_DOC)
		return (1);
	return (0);
}

int	token_error(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].token != UNKNOWN)
	{
		if (tokens[i].token == CLOSE_PAR)
		{
			if (is_command(tokens, i))
				return (1);
		}
		i++;
	}
	return (0);
}
