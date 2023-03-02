/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:42:46 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/02 12:25:08 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_redirections(t_redirections *redirection)
{
	int	i;

	i = 0;
	printf("--------\n");
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
	int	j;

	i = 0;
	if (head->connection_count == 1)
	{
		j = 0;
		printf("command : %s ", head->command->command);
		printf("\n");
		while (j < head->command->argument_count)
		{
			printf("argument : %s ", head->command->arguments[j]);
			j++;
		}
		printf("\n");
		j = 0;
		while (j < head->command->option_count)
		{
			printf("option : %s : ", head->command->options[j]);
			j++;
		}
		printf("\n");
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
				getchar();
				print_token(head->tokens);
				if (head->redirections != NULL)
					print_redirections(head->redirections);
				getchar();
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
