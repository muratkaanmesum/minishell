/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:42:46 by mmesum            #+#    #+#             */
/*   Updated: 2023/02/16 16:57:48 by mmesum           ###   ########.fr       */
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
			prev->redirections = malloc(sizeof(t_redirections));
			start = prev;
		}
		else
		{
			prev->next = new;
			new->redirections = malloc(sizeof(t_redirections));
			prev = new;
		}
		i++;
	}
	prev->next = NULL;
	return (start);
}

t_command	*fill_command(t_command *commands, t_token *tokens)
{
	t_redirections	*redirections;
	int				end;

	end = command_count(tokens);
	printf("end %d\n", end);
	redirections = create_redirections(tokens);
	for (int i = 0; i < end; i++)
	{
		if (redirections[i].infile != NULL || redirections[i].outfile != NULL)
		{
			printf("redirections[%d].input: %s\n", i, redirections[i].infile);
			printf("redirections[%d].output: %s\n", i, redirections[i].outfile);
		}
	}
	return (commands);
}

//cat <test.txt  | wc -l | ls | ls | uniq < test.txt | grep a <
void	parser(t_token *tokens)
{
	t_command	*command;

	command = fill_command(open_commands(command_count(tokens)), tokens);
	(void)command;
}
