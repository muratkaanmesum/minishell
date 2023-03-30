/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 12:06:33 by eablak            #+#    #+#             */
/*   Updated: 2023/03/30 12:06:35 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_printable(t_token tokens)
{
	if (tokens.token == I_REDIRECTION || tokens.token == O_REDIRECTION
		|| tokens.token == APPEND_RED || tokens.token == HERE_DOC
		|| tokens.token == RED_FILE || tokens.token == UNKNOWN)
		return (1);
	return (0);
}

void	get_new_token(t_token *removed_tokens, t_token *new_token)
{
	int	i;
	int	j;
	int	open_count;

	i = 0;
	j = 0;
	open_count = 0;
	while (removed_tokens[i].token != UNKNOWN)
	{
		if (removed_tokens[i].token == OPEN_PAR)
			open_count++;
		if (removed_tokens[i].token == CLOSE_PAR)
			open_count--;
		if (open_count > 0)
			copy_token(&new_token[j++], removed_tokens[i]);
		else if (open_count == 0 && is_printable(removed_tokens[i]) == 0)
			copy_token(&new_token[j++], removed_tokens[i]);
		i++;
	}
	new_token[j].token = UNKNOWN;
}

int	count_redirections(t_token *tokens)
{
	int	i;
	int	red_count;

	i = 0;
	red_count = 0;
	while (tokens[i].token != UNKNOWN)
	{
		pass_parantheses(tokens, &i);
		if (tokens[i].token == HERE_DOC || tokens[i].token == I_REDIRECTION
			|| tokens[i].token == O_REDIRECTION || tokens[i].token == APPEND_RED
			|| tokens[i].token == RED_FILE)
			red_count++;
		i++;
	}
	return (red_count);
}

t_token	*clear_redirections(t_node *node)
{
	int		all;
	t_token	*new_token;
	t_token	*removed_tokens;

	if (check_parantheses(node->tokens) == 1)
		removed_tokens = remove_parantheses(node->tokens);
	else
		removed_tokens = node->tokens;
	all = 0;
	while (removed_tokens[all].token != UNKNOWN)
		all++;
	new_token = malloc(sizeof(t_token) * (all
				- count_redirections(removed_tokens) + 1));
	get_new_token(removed_tokens, new_token);
	if (check_parantheses(node->tokens) == 1)
		free(removed_tokens);
	return (new_token);
}
