/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:42:46 by mmesum            #+#    #+#             */
/*   Updated: 2023/02/23 16:32:11 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//((cat test1.txt | grep e && ls) && wc -l | ls | ls | ls
//(cat test1.txt | grep e && ls) && wc -l | ls | ls | ls

//(cat test1.txt | grep e && ls)
//wc -l | ls | ls | ls | ls (grep e && ls)

//(grep e && ls) && cat
//(grep e && ls)
//cat
//grep e
void	print(t_token *split, int i)
{
	while (split->token != UNKNOWN)
	{
		printf("Token: %d, Start: %d, End: %d, Str: %s\n",
				split->token,
				split->start_index,
				split->end_index,
				split->str);
		split++;
	}
	printf("***************\n");
}

void	parser(t_token *tokens)
{
	t_node	*head;
	int		i;

	head = malloc(sizeof(t_node));
	head->command = NULL;
	i = 0;
	handle_connections(head, tokens);
}
