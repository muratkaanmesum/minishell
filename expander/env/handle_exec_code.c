/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exec_code.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 14:07:26 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/18 14:32:04 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../expander.h"

int	get_str_count(char *str)
{
	int	i;
	int	node_size;
	int	flag;
	int	in_quote;
	int	start_index;

	node_size = 0;
	assign_default_values(&i, &in_quote, &flag);
	printf("%s\n", str);
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
			in_quote = in_quote != 1;
		if (str[i] == '$' && flag == 0 && in_quote == 0)
		{
			start_index = i;
			flag = 1;
			i += 2;
		}
		else
			node_size++;
		if (str[i] != '\0')
			i++;
	}
	return (node_size);
}

char	*handle_exec_code(char *str, char *env_value)
{
	int		i;
	int		in_quote;
	int		flag;
	char	*new_str;

	printf("asd%d\n", get_str_count(str));
	pause();
	assign_default_values(&i, &in_quote, &flag);
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '"')
			in_quote = !in_quote;
		if (str[i] == '$' && !in_quote)
		{
			assign_env_value(new_str, env_value, &i);
			pass_env(str, i, &i);
		}
		else
			new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
