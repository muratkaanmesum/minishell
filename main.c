/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:41:43 by mmesum            #+#    #+#             */
/*   Updated: 2023/02/14 16:53:51 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv)
{
	char	*inpt;
	t_token	*tokens;

	if (argc != 1)
		return (0);
	(void)argv;
	while (1)
	{
		inpt = readline("minishell: ");
		add_history(inpt);
		tokens = lexer(inpt);
		// for (int i = 0; i < get_token_count(inpt); i++)
		// {
		// 	printf("Token: %d, Start: %d, End: %d, Str: %s\n", tokens[i].token,
		// 			tokens[i].start_index, tokens[i].end_index, tokens[i].str);
		// }
		parser(tokens);
		free(inpt);
	}
	return (0);
}
