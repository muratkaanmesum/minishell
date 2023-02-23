/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:59:13 by mmesum            #+#    #+#             */
/*   Updated: 2023/02/23 14:45:13 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


t_token	*check_split(t_token *split)
{
	int		i;
	int		j;
	t_token	*new_split;

	i = 0;
	j = 1;
	while (split[i].token != UNKNOWN)
		i++;
	if (split[0].token == OPEN_PAR && split[i].token == CLOSE_PAR)
	{
		new_split = malloc(sizeof(t_token) * (i - 1));
		while (j < i - 1)
		{
			new_split[j - 1] = split[j];
			j++;
		}
		new_split[j].token = UNKNOWN;
		free(split);
		return (new_split);
	}
	return (split);
}
//((cat test1.txt | grep e && ls) && wc -l | ls | ls | ls | ls (grep e && ls) || (cat))

//(((cat test.txt) && (echo hello) && (ls | (cat test.txt))))
//(cat test.txt && test)
// ls 
//(cat test.txt || test)

//((cat test.txt) && (echo hello) && (ls | ((cat test.txt))))
//cat test.txt
