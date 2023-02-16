/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:55:12 by mmesum            #+#    #+#             */
/*   Updated: 2023/02/16 16:55:41 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_input(t_token *tokens, int start, int end,
		t_redirections *redirection)
{
	int	last_token;
	int	does_include;

	does_include = 0;
	while (start < end)
	{
		if (tokens[start].token == RED_FILE && (tokens[start
				- 1].token == I_REDIRECTION || tokens[start
				- 1].token == HERE_DOC))
		{
			does_include = 1;
			last_token = start;
		}
		start++;
	}
	if (does_include == 1)
	{
		redirection->infile = tokens[last_token].str;
		redirection->infile_type = tokens[last_token - 1].token;
	}
	else
		redirection->infile = "null";
}
void	handle_output(t_token *tokens, int start, int end,
		t_redirections *redirection)
{
	int	last_token;
	int	does_include;

	does_include = 0;
	while (start < end)
	{
		if (tokens[start].token == RED_FILE && (tokens[start
				- 1].token == O_REDIRECTION || tokens[start
				- 1].token == APPEND_RED))
		{
			does_include = 1;
			last_token = start;
		}
		start++;
	}
	if (does_include == 1)
	{
		redirection->outfile = tokens[last_token].str;
		redirection->outfile_type = tokens[last_token - 1].token;
	}
	else
		redirection->outfile = "null";
}
/*
	if (tokens[last_token - 1].token == HERE_DOC || tokens[last_token
		- 1].token == I_REDIRECTION)
		redirection->infile = tokens[last_token].str;
	if (tokens[last_token - 1].token == O_REDIRECTION || tokens[last_token
		- 1].token == APPEND_RED)
		redirection->outfile = tokens[last_token].str;
*/
void	handle_redirection(t_redirections *redirection, int start, int end,
		t_token *tokens)
{
	handle_input(tokens, start, end, redirection);
	handle_output(tokens, start, end, redirection);
}
