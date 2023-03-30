/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:41:43 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/30 10:19:34 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_execute	*g_execute;

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

void	init_execute(char **env)
{
	g_execute = malloc(sizeof(t_execute));
	g_execute->last_exit_code = 0;
	g_execute->env = init_env(env);
	g_execute->export = init_env(env);
	g_execute->only_red_count = 0;
}

void	main_loop(void)
{
	t_node	*head;
	t_token	*tokens;

	signal(SIGINT, &ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		g_execute->input = readline("minishell: ");
		add_history(g_execute->input);
		ctrl_d(g_execute);
		tokens = lexer(g_execute->input);
		if (tokens == NULL)
		{
			free(g_execute->input);
			continue ;
		}
		if (first_check_free(tokens, g_execute->input) == 1)
			continue ;
		head = parser(tokens, g_execute);
		if (parse_error_free(head, tokens, g_execute->input) == 1)
			continue ;
		exec_rest(head);
	}
}

int	main(int argc, char **argv, char **env)
{
	if (argc != 1)
		return (0);
	(void)argv;
	init_execute(env);
	main_loop();
	return (0);
}
