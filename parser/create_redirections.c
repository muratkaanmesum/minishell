/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 16:37:54 by mmesum            #+#    #+#             */
/*   Updated: 2023/02/14 16:49:51 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_first(t_token *tokens, int start, int end,
		t_redirections *redirection)
{
		int last_token;

	if (tokens[0].token == I_REDIRECTION || tokens[0].token == HERE_DOC)
		redirection[0].infile = tokens[1].str;
	else
	{
		while (start < end)
		{
			if (tokens[start].token == I_REDIRECTION
				|| tokens[start].token == HERE_DOC)
				last_token = start;
			start++;
		}
		redirection[0].infile = tokens[last_token + 1].str;
	}
}

void	handle_redirection(t_redirections *redirection, int start, int end,
		t_token *tokens)
{
	t_token	token;

	if (start == 0)
		handle_first(tokens, start, end, redirection);
	else
		handle_rest(tokens, start, end, redirection);
}
// cat < test.txt | wc -l | test > outfile.txt
// < test.txt cat | wc -l | test > outfile.txt
// cat < test.txt < test2.txt | wc -l | test > outfile.txt
int	does_include(t_token *tokens, int start, int end)
{
	while (start < end)
	{
		if (tokens->token == I_REDIRECTION || tokens->token == O_REDIRECTION
			|| tokens->token == HERE_DOC || tokens->token == APPEND_RED)
			return (1);
		start++;
	}
	return (0);
}
t_redirections	*create_redirections(t_token *tokens)
{
	int				i;
	t_redirections	*red;
	int				t_index;
	int				start;

	start = 0;
	i = 0;
	t_index = 0;
	while (i < command_count(tokens))
	{
		red = malloc(sizeof(t_redirections));
		while (tokens[t_index].token != PIPE && tokens[t_index].token != AND
			&& tokens[t_index].token != OR)
			t_index++;
		if (does_include(tokens, start, t_index) == 1)
			handle_redirection(red, start, t_index, tokens);
		else
		{
			//without_redirection();
		}
		start = t_index;
		i++;
	}
}
