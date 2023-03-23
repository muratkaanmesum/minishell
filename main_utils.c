/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:09:51 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/23 11:18:06 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_error_free(t_node *head, t_token *tokens, char *inpt)
{
	if (head == NULL)
	{
		free(inpt);
		free_tokens_str(tokens);
		free(tokens);
		return (1);
	}
	return (0);
}

int	first_check_free(t_token *tokens, char *inpt)
{
	if (check_first(tokens) == 1)
	{
		free(inpt);
		free_tokens_str(tokens);
		free(tokens);
		return (1);
	}
}

void	exec_rest(t_node *head, t_token *tokens)
{
	 expander(head);
	//execute(head);
	// free(head->execute->input);
	free_execute(head->execute);
	free_tree(head);
}
