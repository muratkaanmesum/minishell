/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 16:37:54 by mmesum            #+#    #+#             */
/*   Updated: 2023/02/28 10:08:59 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// test
//test < test.txt
// (test || ls || grep e)

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
		i++;
	}
	return (0);
}

// (test.txt test | asd < test.txt) < test.txt > test.txt
void	create_redirections(t_node *node)
{
	t_redirections	*red;

	if (does_include(node->tokens))
	{
		node->redirections = malloc(sizeof(t_redirections));
		handle_redirection(node);
	}
	else
		node->redirections = NULL;
}
