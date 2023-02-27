/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:59:13 by mmesum            #+#    #+#             */
/*   Updated: 2023/02/27 14:47:41 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*check_parantheses(t_token *split)
{
	int		i;
	int		j;
	t_token	*new_split;

	i = 0;
	j = 1;
	while (split[i].token != UNKNOWN)
		i++;
	if (split[0].token == OPEN_PAR && split[i - 1].token == CLOSE_PAR)
	{
		new_split = malloc(sizeof(t_token) * (i - 1));
		while (j < i - 1)
		{
			new_split[j - 1] = split[j];
			j++;
		}
		new_split[j - 1].token = UNKNOWN;
		//free(split);
		return (new_split);
	}
	return (split);
}

void	pass_parantheses(t_token *tokens, int *i)
{
	int	open_count;

	open_count = 0;
	if (tokens[*i].token == OPEN_PAR)
	{
		open_count++;
		*i += 1;
		while (open_count != 0 && tokens[*i].token != UNKNOWN)
		{
			if (tokens[*i].token == OPEN_PAR)
				open_count++;
			if (tokens[*i].token == CLOSE_PAR)
				open_count--;
			*i += 1;
		}
	}
}
