/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:41:43 by mmesum            #+#    #+#             */
/*   Updated: 2023/02/21 18:08:27 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv)
{
	char	*inpt;
	t_token	*tokens;
	t_token	**split;
	int		i;

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
		// split = split_token(tokens);
		// split = check_split(split[0]);
		// printf("%d\n", connection_count(tokens));
		// printf("%d\n", get_split_tokens(tokens));
		i = 0;
		// while (i < connection_count(tokens))
		// {
		// 	while (split[i]->token != UNKNOWN)
		// 	{
		// 		printf("Token: %d, Start: %d, End: %d, Str: %s\n",
		// 				split[i]->token,
		// 				split[i]->start_index,
		// 				split[i]->end_index,
		// 				split[i]->str);
		// 		split[i]++;
		// 	}
		// 	i++;
		// 	printf("************\n");
		// }
		parser(tokens);
		free(inpt);
	}
	return (0);
}
