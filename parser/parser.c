/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:42:46 by mmesum            #+#    #+#             */
/*   Updated: 2023/02/13 19:00:46 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	command_count(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens->token != UNKNOWN)
	{
		if (tokens->token == PIPE || tokens->token == AND
			|| tokens->token == OR)
			count++;
		tokens++;
	}
	count++;
	return (count);
}

t_command	*open_commands(int count)
{
	int			i;
	t_command	*new;
	t_command	*prev;
	t_command	*start;

	i = 0;
	prev = NULL;
	while (i < count)
	{
		new = malloc(sizeof(t_command));
		if (prev == NULL)
		{
			prev = new;
			start = prev;
		}
		else
		{
			prev->next = new;
			prev = new;
		}
		i++;
	}
	prev->next = NULL;
	return (start);
}

//test asd < test | test asd "asddsa" && test asd ||ads
void	parser(t_token *tokens)
{
	int			i;
	t_command	*command;

	i = 0;
	command = open_commands(command_count(tokens));
}
