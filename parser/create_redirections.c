/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 16:37:54 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/01 15:38:17 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// test
//test < test.txt
// (test || ls || grep e)

//  (test.txt test | asd < test.txt)
// (TEST < asd | test && (testt.txt | wc -l <test2.txt)) < test.txt > test.txt
int	does_include(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].token != UNKNOWN)
	{
		pass_parantheses(tokens, &i);
		if (tokens[i].token == I_REDIRECTION || tokens[i].token == O_REDIRECTION
			|| tokens[i].token == APPEND_RED || tokens[i].token == HERE_DOC)
			return (1);
		if (tokens[i].token != UNKNOWN)
			i++;
	}
	return (0);
}
//((cat cat.txt | grep e > grep.txt && ls) < sub1.txt
//cat cat.txt | grep e > grep.txt
// && wc -l | ls > ls1 | ls | ls < ls2.txt)
t_token	*create_redirections(t_node *node)
{
	t_redirections	*red;
	enum e_token	split_type;
	t_token			*token;

	if (does_priority(node->tokens, -1) == 1)
		split_type = -1;
	else if (does_priority(node->tokens, PIPE) == 1)
		split_type = PIPE;
	else
		split_type = UNKNOWN;
	if (does_include(node->tokens) && split_type == UNKNOWN)
	{
		node->redirections = malloc(sizeof(t_redirections));
		handle_redirection(node);
		token = clear_redirections(node);
	}
	else
		return (NULL);
	return (token);
}
