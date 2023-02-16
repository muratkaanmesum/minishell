/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:55:12 by mmesum            #+#    #+#             */
/*   Updated: 2023/02/16 14:53:39 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_first(t_token *tokens, int start, int end,
		t_redirections *redirection)
{
	t_token	last_token;

	while (start < end)
	{
		if (tokens[start].token == RED_FILE)
			last_token = tokens[start];
		start++;
	}
	redirection->infile = last_token.str;
}
//< testc < test < testa grep e |wc -l < test.txt < test2.txt
void	handle_redirection(t_redirections *redirection, int start, int end,
		t_token *tokens)
{
	handle_first(tokens, start, end, redirection);
}
