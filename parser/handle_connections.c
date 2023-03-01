/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_connections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 13:12:15 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/01 14:18:45 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	does_priority(t_token *tokens, enum e_token token)
{
	int	open_count;
	int	i;

	if (token == UNKNOWN)
		return (0);
	i = 0;
	open_count = 0;
	while (tokens[i].token != UNKNOWN)
	{
		pass_parantheses(tokens, &i);
		if ((tokens[i].token == AND || tokens[i].token == OR) && token == -1
			&& tokens[i].token != UNKNOWN)
			return (1);
		else if (tokens[i].token == token && tokens[i].token != UNKNOWN)
			return (1);
		if (tokens[i].token != UNKNOWN && (tokens[i].token != OPEN_PAR
				&& tokens[i].token != CLOSE_PAR))
		{
			i++;
		}
	}
	return (0);
}
// (cat test1.txt | grep e && ls) < test.txt |
t_node	*handle_connections(t_node *head, t_token *tokens)
{
	t_token			**split;
	int				i;
	enum e_token	split_type;
	int				j;
	int				t;
	t_token			*cleared_tokens;

	head->tokens = tokens;
	head->redirections = NULL;
	split_type = -5;
	head->is_subshell = 0;
	split = NULL;
	i = 0;
	//test.txt test | asd < test.txt < test.txt > test.txt
	cleared_tokens = create_redirections(head);
	if (cleared_tokens != NULL)
	{
		//free(tokens);
		head->tokens = cleared_tokens;
	}
	if (check_parantheses(head->tokens) == 1)
	{
		head->tokens = remove_parantheses(head->tokens);
		head->is_subshell = 1;
	}
	if (does_priority(head->tokens, -1) == 1)
		split_type = -1;
	else if (does_priority(head->tokens, PIPE) == 1)
		split_type = PIPE;
	else
		split_type = UNKNOWN;
	head->connection_count = connection_count(head->tokens, split_type);
	if (split_type != UNKNOWN)
	{
		j = 0;
		split = split_token(head->tokens, split_type);
	}
	else
		return (head);
	i = 0;
	if (split != NULL)
	{
		head->connections = malloc(sizeof(t_node *)
				* connection_count(head->tokens, split_type));
		while (i < connection_count(head->tokens, split_type))
		{
			head->connections[i] = handle_connections(malloc(sizeof(t_node)),
														split[i]);
			i++;
		}
	}
	return (head);
}
