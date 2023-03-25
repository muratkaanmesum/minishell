/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 12:25:54 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/25 18:49:39 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../expander.h"

int	check_exec_val(char *str, int *i, char *new_str, int *index)
{
	if (str[*i + 1] != '\0' && str[*i + 1] == '?')
	{
		new_str[*index] = '$';
		(*index)++;
		(*i)++;
		return (1);
	}
	return (0);
}

void	change_str(char *str, char *env_value, char *new_str)
{
	int	i;
	int	index;
	int	flag;
	int	in_quote;
	int	start_index;

	index = 0;
	assign_default_values(&i, &in_quote, &flag);
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
			in_quote = in_quote != 1;
		if (str[i] == '$' && flag == 0 && in_quote == 0)
		{
			if (check_exec_val(str, &i, new_str, &index))
				continue ;
			start_index = i;
			flag = 1;
			assign_env_value(new_str, env_value, &index);
			pass_env(str, start_index, &i);
		}
		if (str[i] != '\0')
			new_str[index++] = str[i++];
	}
	new_str[index] = '\0';
}

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
	(*i)++;
	(*node_size)++;
	while (str[*i] != '\0' && str[*i] != '\'')
	{
		(*i)++;
		(*node_size)++;
	}
	if (str[*i + 1] != '\0')
		(*i)++;
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
		if (str[i] != '\0')
			node_size++;
		if (str[i] != '\0')
			i++;
	}
	return (node_size);
}

char	*assign_env(char *str, char *env_value)
{
	int		value_size;
	char	*new_str;
	int		node_size;

	node_size = get_node_size(str);
	printf("node size %d\n", node_size);
	value_size = (int)ft_strlen(env_value);
	new_str = malloc(sizeof(char) * (value_size + node_size + 1));
	change_str(str, env_value, new_str);
	// free(str);
	return (new_str);
}
