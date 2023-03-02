/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:59:13 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/02 18:58:54 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_token(t_token *token)
{
	int	i;

	i = 0;
	while (token[i].token != UNKNOWN)
	{
		printf("value: %s id : %d token : ", token[i].str, token[i].id);
		switch (token[i].token)
		{
		case PIPE:
			printf("PIPE\n");
			break ;
		case UNKNOWN:
			printf("UNKNOWN\n");
			break ;
		case I_REDIRECTION:
			printf("I_REDIRECTION\n");
			break ;
		case O_REDIRECTION:
			printf("O_REDIRECTION\n");
			break ;
		case APPEND_RED:
			printf("APPEND_RED\n");
			break ;
		case HERE_DOC:
			printf("HERE_DOC\n");
			break ;
		case COMMAND:
			printf("COMMAND\n");
			break ;
		case ARG:
			printf("ARG\n");
			break ;
		case OPTION:
			printf("OPTION\n");
			break ;
		case AND:
			printf("AND\n");
			break ;
		case OR:
			printf("OR\n");
			break ;
		case ENV_COMMAND:
			printf("ENV_COMMAND\n");
			break ;
		case ENV:
			printf("ENV\n");
			break ;
		case RED_FILE:
			printf("RED_FILE\n");
			break ;
		case OPEN_PAR:
			printf("OPEN_PAR\n");
			break ;
		case CLOSE_PAR:
			printf("CLOSE_PAR\n");
			break ;
		}
		i++;
	}
}
t_token	*remove_parantheses(t_token *tokens)
{
	int		i;
	int		j;
	t_token	*new_split;

	i = 0;
	j = 1;
	while (tokens[i].token != UNKNOWN)
		i++;
	if (tokens[0].token == OPEN_PAR && tokens[i - 1].token == CLOSE_PAR)
	{
		new_split = malloc(sizeof(t_token) * (i - 1));
		while (j < i - 1)
		{
			new_split[j - 1] = tokens[j];
			j++;
		}
		new_split[j - 1].token = UNKNOWN;
		//free(tokens);
		return (new_split);
	}
	return (tokens);
}
int	check_parantheses(t_token *tokens)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (tokens[i].token != UNKNOWN)
		i++;
	if (tokens[0].token == OPEN_PAR && tokens[i - 1].token == CLOSE_PAR)
		return (1);
	return (0);
}
void	pass_parantheses(t_token *tokens, int *i)
{
	int	open_count;

	open_count = 0;
	if (tokens[*i].token == OPEN_PAR)
	{
		open_count++;
		*i += 1;
		while (open_count != 0 && tokens[*i].token != UNKNOWN)
		{
			if (tokens[*i].token == OPEN_PAR)
				open_count++;
			if (tokens[*i].token == CLOSE_PAR)
				open_count--;
			*i += 1;
		}
	}
}

//(cat test.txt (test.txt))
int	is_arithmetic(t_token *tokens)
{
	int open_count = 0;
	int close_count = 0;
	int i = 0;
	while (tokens[i].token != UNKNOWN && tokens[i].token == OPEN_PAR)
	{
		open_count++;
		i++;
	}
	i = 0;
	while (tokens[i].token != UNKNOWN)
		i++;
	i--;
	while (i >= 0 && tokens[i].token == CLOSE_PAR)
	{
		close_count++;
		i--;
	}
	if (open_count == close_count && open_count > 1)
	{
		printf("INSIDE OF SOMETHING\n");
		return (1);
	}
	return (0);
}