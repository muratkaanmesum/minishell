/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:41:43 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/26 08:34:32 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	print_redirections(t_redirections *redirection)
// {
// 	int	i;

// 	i = 0;
// 	printf("--------\n");
// 	while (i < redirection->infile_count)
// 	{
// 		printf("infile: %s ", redirection->infile[i]);
// 		switch (redirection->infile_type[i])
// 		{
// 		case I_REDIRECTION:
// 			printf("I_REDIRECTION\n");
// 			break ;
// 		case HERE_DOC:
// 			printf("HERE_DOC\n");
// 			break ;
// 		default:
// 			printf("UNKNOWN\n");
// 			break ;
// 		}
// 		i++;
// 	}
// 	i = 0;
// 	while (i < redirection->outfile_count)
// 	{
// 		printf("outfile: %s ", redirection->outfile[i]);
// 		switch (redirection->outfile_type[i])
// 		{
// 		case O_REDIRECTION:
// 			printf("O_REDIRECTION\n");
// 			break ;
// 		case APPEND_RED:
// 			printf("APPEND_RED\n");
// 			break ;
// 		default:
// 			printf("UNKNOWN\n");
// 			break ;
// 		}
// 		i++;
// 	}
// }
// void	print_tree(t_node *head)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	if (head->connection_count == 0)
// 	{
// 		j = 0;
// 		if (head->command == NULL)
// 		{
// 			print_token(head->tokens);
// 			printf("left_operator %d  right_operator %d\n", head->left_operator,
// 					head->right_operator);
// 			printf("\n****NULL*****\n");
// 			return ;
// 		}
// 		printf("command : %s ", head->command->command);
// 		printf("\n");
// 		while (j < head->command->argument_count)
// 		{
// 			printf("argument : %s \n", head->command->arguments[j]);
// 			j++;
// 		}
// 		printf("\n");
// 		j = 0;
// 		if (head->redirections != NULL)
// 			print_redirections(head->redirections);
// 		printf("\n*************\n");
// 		printf("left_operator : %d\n", head->left_operator);
// 		printf("right_operator : %d\n", head->right_operator);
// 		printf("\n*************\n");
// 		return ;
// 	}
// 	else
// 		while (i < head->connection_count)
// 		{
// 			if (i == 0)
// 			{
// 					print_token(head->tokens);
// 				if (head->redirections != NULL)
// 					print_redirections(head->redirections);
// 				printf("\n*************\n");
// 				printf("left_operator : %d\n", head->left_operator);
// 				printf("right_operator : %d\n", head->right_operator);
// 				printf("\n*************\n");
// 			}
// 			print_tree(head->connections[i]);
// 			i++;
// 		}
// }

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

t_execute	*init_execute(char **env)
{
	t_execute	*execute_struct;

	execute_struct = malloc(sizeof(t_execute));
	execute_struct->last_exit_code = 0;
	execute_struct->env = init_env(env);
	execute_struct->export = init_env(env);
	execute_struct->only_red_count = 0;
	return (execute_struct);
}

void	main_loop(t_execute *execute_struct)
{
	t_node	*head;
	t_token	*tokens;

	while (1)
	{
		signal(SIGINT, &ctrl_c);
		signal(SIGQUIT, SIG_IGN);
		execute_struct->input = readline("minishell: ");
		write(1, "\033[0m", 4);
		ctrl_d(execute_struct);
		add_history(execute_struct->input);
		tokens = lexer(execute_struct->input);
		if (tokens == NULL)
		{
			free(execute_struct->input);
			continue ;
		}
		if (first_check_free(tokens, execute_struct->input) == 1)
			continue ;
		head = parser(tokens, execute_struct);
		if (parse_error_free(head, tokens, execute_struct->input) == 1)
			continue ;
		exec_rest(head);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_execute	*execute_struct;

	if (argc != 1)
		return (0);
	(void)argv;
	execute_struct = init_execute(env);
	main_loop(execute_struct);
	return (0);
}
