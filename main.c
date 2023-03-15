/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:41:43 by mmesum            #+#    #+#             */

/*   Updated: 2023/03/13 17:28:59 by mmesum           ###   ########.fr       */

/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (head->command == NULL)
		{
			print_token(head->tokens);
			return ;
		}
		printf("command : %s ", head->command->command);
		printf("\n");
		while (j < head->command->argument_count)
		{
			printf("argument : %s \n", head->command->arguments[j]);
			j++;
		}
		printf("\n");
		j = 0;
		if (head->redirections != NULL)
			print_redirections(head->redirections);
		printf("\n*************\n");
		printf("left_operator : %d\n", head->left_operator);
		printf("right_operator : %d\n", head->right_operator);
		printf("\n*************\n");
		return ;
	}
	else
		while (i < head->connection_count)
		{
			if (i == 0)
			{
				// 	print_token(head->tokens);
				if (head->redirections != NULL)
					print_redirections(head->redirections);
				printf("\n*************\n");
				printf("left_operator : %d\n", head->left_operator);
				printf("right_operator : %d\n", head->right_operator);
				printf("\n*************\n");
			}
			print_tree(head->connections[i]);
			i++;
		}
}

char	**init_env(char **env)
{
	int		i;
	char	**new_env;

	i = 0;
	while (env[i] != NULL)
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i] != NULL)
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

int	main(int argc, char **argv, char **env)
{
	char	*inpt;
	t_token	*tokens;
	int		i;
	t_node	*head;
	char	**new_env;

	if (argc != 1)
		return (0);
	(void)argv;
	new_env = init_env(env);
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
		if (check_first(tokens) == 1)
			continue ;
		head = parser(tokens);
		if (head == NULL)
			continue ;
		expander(head, new_env);
		execute(head, &new_env);
		//free_tree(head, tokens);
		//free_new_env(new_env);
		free(inpt);
	}
	return (0);
}
