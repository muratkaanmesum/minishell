/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 16:37:54 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/20 15:40:16 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		// free_tokens_str(node->tokens);
		// free(node->tokens);
		return (token);
	}
	else
		return (NULL);
}
