/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:42:46 by mmesum            #+#    #+#             */
/*   Updated: 2023/02/28 10:52:30 by kali             ###   ########.fr       */
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
void	print_redirections(t_redirections *redirection)
{
	int	i;

	i = 0;
	printf("\n-----------\n");
	while (i < redirection->infile_count)
	{
		printf("infile: %s ", redirection->infile[i]);
		switch (redirection->infile_type[i])
		{
		case I_REDIRECTION:
			printf("I_REDIRECTION\n");
			break ;
		case HERE_DOC:
			printf("HERE_DOC\n");
			break ;
		default:
			printf("UNKNOWN\n");
			break ;
		}
		i++;
	}
	i = 0;
	while (i < redirection->outfile_count)
	{
		printf("outfile: %s ", redirection->outfile[i]);
		switch (redirection->outfile_type[i])
		{
		case O_REDIRECTION:
			printf("O_REDIRECTION\n");
			break ;
		case APPEND_RED:
			printf("APPEND_RED\n");
			break ;
		default:
			printf("UNKNOWN\n");
			break ;
		}
		i++;
	}
}
void	print_tree(t_node *head)
{
	int	i;

	i = 0;
	if (head->connection_count == 1)
	{
		print_token(head->tokens);
		if (head->redirections != NULL)
			print_redirections(head->redirections);
		printf("\n*************\n");
		return ;
	}
	else
		while (i < head->connection_count)
		{
			if (i == 0)
			{
				if (head->redirections != NULL)
					print_redirections(head->redirections);
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
