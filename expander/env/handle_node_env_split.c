/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_node_env_split.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 07:59:14 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/28 17:35:31 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../expander.h"

void	pass_quotes(char *str, int *i)
{
	char	quote;

	quote = str[*i];
	if (str[*i] != '\0')
		(*i)++;
	while (str[*i] != quote && str[*i] != '\0')
		(*i)++;
	if (str[*i] != '\0')
		(*i)++;
}

int	check_outside_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == '\'' || str[i] == '\"') && str[i] != '\0')
			pass_quotes(str, &i);
		if (str[i] == ' ')
			return (1);
		if (str[i] != '\0')
			i++;
	}
	return (0);
}

void	add_argument(t_node *node, char *val)
{
	char	**new_args;
	int		i;

	i = 0;
	new_args = malloc(sizeof(char *) * (node->command->argument_count + 2));
	while (i < node->command->argument_count)
	{
		new_args[i] = ft_strdup(node->command->arguments[i]);
		i++;
	}
	new_args[i] = val;
	new_args[i + 1] = NULL;
	node->command->argument_count++;
	free_double_ptr(node->command->arguments);
	node->command->arguments = new_args;
}

void	handle_node_env_split(t_node *node)
{
	int		i;
	char	**val;

	i = 0;
	if (check_outside_quotes(node->command->command) == 1)
	{
		val = ft_split(node->command->command, ' ');
		free(node->command->command);
		node->command->command = val[0];
		while (val[++i] != NULL)
			add_argument(node, val[i]);
	}
	while (i < node->command->argument_count)
	{
		if (check_outside_quotes(node->command->arguments[i]) == 1)
		{
			val = ft_split(node->command->arguments[i], ' ');
			free(node->command->arguments[i]);
			node->command->arguments[i] = val[0];
			while (val[++i] != NULL)
				add_argument(node, val[i]);
		}
		i++;
	}
}
