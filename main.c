/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:41:43 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/28 18:15:39 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	signal(SIGINT, &ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		execute_struct->input = readline("minishell: ");
		add_history(execute_struct->input);
		ctrl_d(execute_struct);
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
