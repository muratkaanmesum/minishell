/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 13:52:33 by mmesum            #+#    #+#             */
/*   Updated: 2023/02/13 13:37:06 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*lexer(char *str)
{
	char	*t_str;
	t_token	*tokens;

	t_str = ft_strtrim(str, " ");
	tokens = malloc(sizeof(t_token) * (get_token_count(t_str) + 1));
	assign_tokens(tokens, t_str);
	for (int i = 0; i < get_token_count(t_str); i++)
	{
		switch (tokens[i].token)
		{
		case I_REDIRECTION:
			printf("I_REDIRECTION");
			break ;
		case O_REDIRECTION:
			printf("O_REDIRECTION");
			break ;
		case HERE_DOC:
			printf("HERE_DOC");
			break ;
		case APPEND_RED:
			printf("APPEND_RED");
			break ;
		case PIPE:
			printf("PIPE");
			break ;
		case COMMAND:
			printf("COMMAND");
			break ;
		case ARG:
			printf("ARG");
			break ;
		case OPTION:
			printf("OPTION");
			break ;
		case AND:
			printf("AND");
			break ;
		case OR:
			printf("OR");
			break ;
		case ENV:
			printf("ENV");
			break ;
		case ENV_COMMAND:
			printf("ENV_COMMAND");
			break ;
		case UNKNOWN:
			printf("UNKNOWN");
			break ;
		}
		printf("   ");
	}
	printf("\n\n");
	return (0);
}
