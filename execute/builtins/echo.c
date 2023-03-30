/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 09:24:24 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/29 19:04:15 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

int	is_valid(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	does_have_option(t_node *node)
{
	int	i;

	if (node->command->argument_count == 0)
		return (0);
	i = 0;
	while (node->command->arguments[i])
	{
		if (is_valid(node->command->arguments[i]) == 0)
			return (i);
		i++;
	}
	return (0);
}

void	print_with_option(t_node *head, int index)
{
	while (index < head->command->argument_count)
	{
		if (head->command->arguments[index + 1] != NULL)
			printf("%s ", head->command->arguments[index]);
		else
			printf("%s", head->command->arguments[index]);
		index++;
	}
}

int	print_args(t_node *head)
{
	int	i;

	i = 0;
	while (i < head->command->argument_count)
	{
		if (head->command->arguments[i + 1] != NULL)
			printf("%s ", head->command->arguments[i]);
		else
			printf("%s", head->command->arguments[i]);
		i++;
	}
	printf("\n");
	return (1);
}

int	echo(t_node *head)
{
	int	pid;
	int	index;

	index = does_have_option(head);
	pid = fork();
	if (pid == 0)
	{
		dup2(head->in_fd, 0);
		dup2(head->out_fd, 1);
		close_all_fds(head);
		if (index != 0)
			print_with_option(head, index);
		else
			print_args(head);
		exit(0);
	}
	return (0);
}
