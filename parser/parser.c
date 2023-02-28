/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:42:46 by mmesum            #+#    #+#             */
/*   Updated: 2023/02/28 09:10:52 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//((cat test1.txt | grep e && ls) && wc -l | ls | ls | ls)
//(cat test1.txt | grep e && ls) && wc -l | ls | ls | ls

//(cat test1.txt | grep e && ls)
//wc -l | ls | ls | ls | ls (grep e && ls)

//(grep e && ls) && cat
//(grep e && ls)
//cat
//grep e

// asd | test
void	print_tree(t_node *head)
{
	int	i;

	i = 0;
	if (head->connection_count == 1)
	{
		print_token(head->tokens);
		printf("\n*************\n");
		return ;
	}
	else
		while (i < head->connection_count)
		{
			if (i == 0)
			{
				print_token(head->tokens);
				printf("\n*************\n");
			}
			print_tree(head->connections[i]);
			i++;
		}
}

void	parser(t_token *tokens)
{
	t_node	*head;

	head = malloc(sizeof(t_node));
	head->command = NULL;
	handle_connections(head, tokens);
	print_tree(head);
}
