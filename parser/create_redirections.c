/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 16:37:54 by mmesum            #+#    #+#             */
/*   Updated: 2023/02/14 17:17:03 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	// else
	// 	handle_rest(tokens, start, end, redirection);
}
// cat < test.txt | wc -l | test > outfile.txt
// < test.txt cat | wc -l | test > outfile.txt
// cat < test.txt < test2.txt | wc -l | test > outfile.txt
int	does_include(t_token *tokens, int start, int end)
{
	while (start < end)
	{
		if (tokens[start].token == I_REDIRECTION
			|| tokens[start].token == O_REDIRECTION
			|| tokens[start].token == HERE_DOC
			|| tokens[start].token == APPEND_RED)
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
			&& tokens[t_index].token != OR && tokens[t_index].token != UNKNOWN)
			t_index++;
		if (does_include(tokens, start, t_index) == 1)
			handle_redirection(red, start, t_index, tokens);
		else
		{
			//without_redirection();
		}
		start = t_index;
		i++;
		printf("%s\n", red->infile);
	}
	return (NULL);
}
