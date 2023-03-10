/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:41:43 by mmesum            #+#    #+#             */

/*   Updated: 2023/03/03 15:52:16 by mmesum           ###   ########.fr       */

/*   Updated: 2023/03/03 14:38:57 by eablak           ###   ########.fr       */

/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void	print_redirections(t_redirections *redirection)
{
	int	i;

	//testasd
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
				// getchar();
				//print_token(head->tokens);
				if (head->redirections != NULL)
					print_redirections(head->redirections);
				// getchar();
				printf("\n*************\n");
			}
			print_tree(head->connections[i]);
			i++;
		}
}

int	main(int argc, char **argv, char **env)
{
	char	*inpt;
	t_token	*tokens;
	int		i;
	t_node	*head;

	if (argc != 1)
		return (0);
	(void)argv;
	while (1)
	{
		inpt = readline("minishell: ");
		add_history(inpt);
		tokens = lexer(inpt);
		if (tokens == NULL)
		{
			free(inpt);
			continue ;
		}
		if (check_first(tokens) != 1) //(a) command not found
		{
			//print_token(tokens);
			head = parser(tokens);
			if (head != NULL)
			{
				//free(inpt);
				//continue ;
				expander(head, env);
				wildcard(head);
				print_tree(head);
				free(inpt);
			}
		}
	}
	return (0);
}
