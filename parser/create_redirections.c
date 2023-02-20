/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 16:37:54 by mmesum            #+#    #+#             */
/*   Updated: 2023/02/20 16:05:25 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
int	command_count(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens->token != UNKNOWN)
	{
		if (tokens->token == PIPE || tokens->token == AND
			|| tokens->token == OR)
			count++;
		tokens++;
	}
	count++;
	return (count);
}
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
	red = malloc(command_count(tokens) * sizeof(t_redirections));
	while (i < command_count(tokens))
	{
		while (tokens[t_index].token != PIPE && tokens[t_index].token != AND
			&& tokens[t_index].token != OR && tokens[t_index].token != UNKNOWN)
			t_index++;
		if (does_include(tokens, start, t_index) == 1)
			handle_redirection(&red[i], start, t_index, tokens);
		else
		{
			red[i].infile = "none";
			red[i].outfile = "none";
		}
		start = t_index;
		t_index++;
		i++;
	}
	return (red);
}
