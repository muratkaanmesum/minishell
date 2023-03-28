/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 12:25:54 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/28 13:38:15 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../expander.h"

int	handle_node_exec(char *str, int *i, int *node_size)
{
	if (str[*i + 1] != '\0' && str[*i + 1] == '?')
	{
		(*node_size)++;
		(*i)++;
		return (1);
	}
	return (0);
}

void	pass_single_quote_count(char *str, int *i, int *node_size)
{
	(*node_size)++;
	(*i)++;
	while (str[*i] != '\0' && str[*i] != '\'')
	{
		(*node_size)++;
		(*i)++;
	}
	if (str[*i] != '\0')
	{
		(*node_size)++;
		(*i)++;
	}
}

void	get_node_size_op(char *str, int *node_size, int *i)
{
	if (str[*i] != '\0')
	{
		(*node_size)++;
		(*i)++;
	}
}

int	get_node_size(char *str)
{
	int	i;
	int	flag;
	int	node_size;
	int	q_flag;
	int	start_index;

	node_size = 0;
	assign_default_values(&i, &q_flag, &flag);
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && q_flag == 0)
			pass_single_quote_count(str, &i, &node_size);
		if (str[i] == '"')
			q_flag = !q_flag;
		if (str[i] == '$' && flag == 0)
		{
			if (handle_node_exec(str, &i, &node_size))
				continue ;
			start_index = i;
			flag = 1;
			pass_env(str, start_index, &i);
		}
		get_node_size_op(str, &node_size, &i);
	}
	return (node_size);
}

char	*assign_env(char *str, char *env_value)
{
	int		value_size;
	char	*new_str;
	int		node_size;

	node_size = get_node_size(str);
	value_size = (int)ft_strlen(env_value);
	new_str = malloc(sizeof(char) * (value_size + node_size + 1));
	change_str(str, env_value, new_str);
	free(str);
	return (new_str);
}
