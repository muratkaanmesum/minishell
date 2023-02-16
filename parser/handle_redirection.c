/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:55:12 by mmesum            #+#    #+#             */
/*   Updated: 2023/02/16 12:16:29 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	hande_rest(t_token *tokens, int start, int end,
		t_redirections *redirection)
{
}

void	handle_first(t_token *tokens, int start, int end,
		t_redirections *redirection)
{
	int	last_token;

	if (tokens[0].token == I_REDIRECTION || tokens[0].token == HERE_DOC)
		redirection->infile = tokens[1].str;
	else
	{
		while (start < end)
		{
			if (tokens[start].token == I_REDIRECTION
				|| tokens[start].token == HERE_DOC)
			{
				last_token = start;
			}
			start++;
		}
		if (tokens[last_token].token != UNKNOWN)
			redirection->infile = tokens[last_token + 1].str;
	}
}

void	handle_redirection(t_redirections *redirection, int start, int end,
		t_token *tokens)
{
	if (start == 0)
		handle_first(tokens, start, end, redirection);
	else
		handle_rest(tokens, start, end, redirection);
}
