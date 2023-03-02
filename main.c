/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:41:43 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/02 13:47:44 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		head = parser(tokens);
		//expander(head, env);
		free(inpt);
	}
	return (0);
}
