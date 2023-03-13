/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 12:25:54 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/13 20:00:51 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../expander.h"

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

int	get_node_size(char *str)
{
	int	i;
	int	flag;
	int	node_size;
	int	in_quote;
	int	start_index;

	start_index = 0;
	node_size = 0;
	assign_default_values(&i, &in_quote, &flag);
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
			in_quote = in_quote != 1;
		if (str[i] == '$' && flag == 0 && in_quote == 0)
		{
			start_index = i;
			flag = 1;
			pass_env(str, start_index, &i);
		}
		node_size++;
		if (str[i] != '\0')
			i++;
	}
	return (node_size);
}

char	*assign_env(char *str, char *env_value, t_node *node,
		enum e_token token_type, int index)
{
	int		value_size;
	char	*new_str;
	int		node_size;
	t_token	*token;

	node_size = get_node_size(str);
	value_size = (int)ft_strlen(env_value);
	new_str = malloc(sizeof(char) * (value_size + node_size + 1));
	change_str(str, env_value, new_str);
	if (token_type == RED_FILE)
	{
		free(str);
		return (new_str);
	}
	token = get_token(node, str, token_type, index);
	if (token->str != NULL)
		token->str = ft_strdup(new_str);
	free(str);
	return (new_str);
}
