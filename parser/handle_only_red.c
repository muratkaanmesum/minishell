/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_only_red.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 10:38:15 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/23 14:45:37 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	check_only_if_red(t_token *tokens, int start_index, int end_index)
{
	while (start_index < end_index)
	{
		if (tokens[start_index].token != I_REDIRECTION
			&& tokens[start_index].token != O_REDIRECTION
			&& tokens[start_index].token != APPEND_RED
			&& tokens[start_index].token != HERE_DOC
			&& tokens[start_index].token != RED_FILE)
			return (0);
		start_index++;
	}
	return (1);
}

void	assign_red_values(int *start_index, int *last_index,
		t_token *tokens)
{
	if (*last_index + 1 > get_token_len(tokens))
		*start_index = get_token_len(tokens);
	else
		*start_index = *last_index + 1;
	if (tokens[*last_index].token != UNKNOWN)
		(*last_index)++;
}

static void	assign_red_operators(t_node *node, int start_index, int last_index,
		t_token *tokens)
{
	if (start_index - 1 < 0)
		node->left_operator = UNKNOWN;
	else
		node->left_operator = tokens[start_index - 1].token;
	if (tokens[last_index].token == UNKNOWN)
		node->right_operator = UNKNOWN;
	else
		node->right_operator = tokens[last_index].token;
}

void	pass_to_priority(t_token *tokens, int *last_index)
{
	while (tokens[*last_index].token != PIPE && tokens[*last_index].token != AND
		&& tokens[*last_index].token != OR
		&& tokens[*last_index].token != UNKNOWN)
		(*last_index)++;
}

void	handle_only_red(t_node *node, t_token *tokens)
{
	int	start_index;
	int	last_index;
	int	count;
	int	red;

	count = 0;
	start_index = 0;
	last_index = 0;
	while (tokens[start_index].token != UNKNOWN)
	{
		pass_to_priority(tokens, &last_index);
		red = check_only_if_red(tokens, start_index, last_index);
		if (node->execute->only_red_count == count && red)
		{
			assign_red_operators(node, start_index, last_index, tokens);
			break ;
		}
		if (red == 1)
			count++;
		assign_red_values(&start_index, &last_index, tokens);
	}
	node->execute->only_red_count++;
}
