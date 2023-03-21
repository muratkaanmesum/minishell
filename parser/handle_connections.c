/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_connections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 13:12:15 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/21 15:33:35 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

void	check_if_subshell(t_node *head)
{
	t_token	*cleared_tokens;

	if (check_parantheses(head->tokens) == 1)
	{
		if (is_arithmetic(head->tokens) == 1)
			head->is_arithmetic = 1;
		else
		{
			head->tokens = remove_parantheses(head->tokens);
			head->is_subshell = 1;
			cleared_tokens = create_redirections(head);
			if (cleared_tokens != NULL)
				head->tokens = cleared_tokens;
		}
	}
}

void	assign_head_values(t_node *head, t_token *tokens, t_execute *execute)
{
	head->tokens = tokens;
	head->redirections = NULL;
	head->is_arithmetic = 0;
	head->is_subshell = 0;
	head->in_fd = STDIN_FILENO;
	head->out_fd = STDOUT_FILENO;
	head->execute = execute;
	head->is_executed = 0;
	head->left_operator = UNKNOWN_TOKEN;
	head->right_operator = UNKNOWN_TOKEN;
}

int	assign_split_type(t_node *head)
{
	int	split_type;

	if (does_priority(head->tokens, -1) == 1)
		split_type = -1;
	else if (does_priority(head->tokens, PIPE) == 1)
		split_type = PIPE;
	else
		split_type = UNKNOWN;
	return (split_type);
}

t_node	*handle_connections(t_node *head, t_token *tokens, t_execute *execute)
{
	t_token			**split;
	int				i;
	enum e_token	split_type;
	t_token			*cleared_tokens;

	split_type = -5;
	assign_head_values(head, tokens, execute);
	cleared_tokens = create_redirections(head);
	if (cleared_tokens != NULL)
		head->tokens = cleared_tokens;
	if (head->tokens[0].token == UNKNOWN)
		return (head);
	if (check_parantheses(head->tokens) == 1)
		check_if_subshell(head);
	split_type = assign_split_type(head);
	if (handle_split_type(split_type, head, &split) == 0)
		return (head);
	i = 0;
	assign_connections(head, split_type, split, execute);
	free(split);
	return (head);
}
