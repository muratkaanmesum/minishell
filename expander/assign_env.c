/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 12:25:54 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/03 16:46:02 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	assign_env_value(char *new_str, char *env_value, int *index)
{
	int	i;

	i = 0;
	while (env_value[i] != '\0')
		new_str[(*index)++] = env_value[i++];
}

void	change_str(char *str, char *env_value, char *new_str)
{
	int	i;
	int	index;
	int	flag;
	int	in_quote;

	index = 0;
	in_quote = 0;
	i = 0;
	flag = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
			in_quote = in_quote != 1;
		if (str[i] == '$' && flag == 0 && in_quote == 0)
		{
			flag = 1;
			assign_env_value(new_str, env_value, &index);
			while (str[i] != '\0' && str[i] != '\'' && str[i] != '"'
				&& str[i] != ' ')
				i++;
		}
		new_str[index++] = str[i++];
	}
	new_str[index] = '\0';
	free(str);
}

int	get_node_size(char *str)
{
	int	i;
	int	flag;
	int	node_size;
	int	in_quote;

	node_size = 0;
	i = 0;
	flag = 0;
	in_quote = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
			in_quote = in_quote != 1;
		if (str[i] == '$' && flag == 0 && in_quote == 0)
		{
			flag = 1;
			while (str[i] != '\0' && str[i] != '\'' && str[i] != '"'
				&& str[i] != ' ')
				i++;
		}
		node_size++;
		i++;
	}
	return (node_size);
}

char	*assign_env(char *str, char *env_value)
{
	int		value_size;
	char	*new_str;

	value_size = (int)ft_strlen(env_value);
	new_str = malloc(sizeof(char) * (value_size + get_node_size(str) + 1));
	change_str(str, env_value, new_str);
	return (new_str);
}
