/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 16:37:54 by mmesum            #+#    #+#             */
/*   Updated: 2023/02/28 12:17:32 by kali             ###   ########.fr       */
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
void	clear_redirections(t_node *node)
{
	int		i;
	int		j;
	int		red_count;
	int		all;
	t_token	*new_token;

	all = 0;
	while (node->tokens[all].token != UNKNOWN)
		all++;
	i = 0;
	red_count = 0;
	while (node->tokens[i].token != UNKNOWN)
	{
		pass_parantheses(node->tokens, &i);
		if (node->tokens[i].token == HERE_DOC
			|| node->tokens[i].token == I_REDIRECTION
			|| node->tokens[i].token == O_REDIRECTION
			|| node->tokens[i].token == APPEND_RED
			|| node->tokens[i].token == RED_FILE)
			red_count++;
		i++;
	}
	new_token = malloc(sizeof(t_token) * (all - red_count + 1));
	j = 0;
	i = 0;
	while (node->tokens[i].token != UNKNOWN)
	{
		if (node->tokens[i].token != HERE_DOC
			&& node->tokens[i].token != I_REDIRECTION
			&& node->tokens[i].token != O_REDIRECTION
			&& node->tokens[i].token != APPEND_RED
			&& node->tokens[i].token != RED_FILE)
		{
			new_token[j] = node->tokens[i];
			j++;
		}
		i++;
	}
	new_token[j].token = UNKNOWN;
	//free(node->tokens);
	node->tokens = new_token;
	if (!new_token)
		print_token(new_token);
}
//  (test.txt test | asd < test.txt)
// TEST | test < test.txt > test.txt
void	create_redirections(t_node *node)
{
	t_redirections	*red;
	enum e_token	split_type;

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
		clear_redirections(node);
	}
	else
		node->redirections = NULL;
}
