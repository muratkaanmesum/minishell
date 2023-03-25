/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 05:26:17 by kali              #+#    #+#             */
/*   Updated: 2023/03/22 20:04:26 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../expander.h"

int	get_length(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '"')
			i++;
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

char	*delete_quotes(char *str, t_node *node)
{
	char	*new_str;
	int		i;
	int		j;

	new_str = malloc(sizeof(char) * (get_length(str) + 1));
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '"')
			i++;
		else
		{
			new_str[j] = str[i];
			i++;
			j++;
		}
	}
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

void	delete_all_quotes(t_node *node)
{
	int	i;

	i = -1;
	node->command->command = delete_quotes(node->command->command, node);
	while (node->command->arguments[++i] != NULL)
	{
		if (quotes_control(node->command->arguments[i]) == 1)
			node->command->arguments[i] = delete_quotes(node->command->arguments[i],
														node);
	}
	i = -1;
	if (node->redirections == NULL)
		return ;
	while (node->redirections->infile[++i] != NULL)
		node->redirections->infile[i] = delete_quotes(node->redirections->infile[i],
														node);
	i = -1;
	while (node->redirections->outfile[++i] != NULL)
		node->redirections->outfile[i] = delete_quotes(node->redirections->outfile[i],
														node);
}
