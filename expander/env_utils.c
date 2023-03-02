/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 12:53:41 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/02 16:50:20 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
char	*change_str(char *str, char *env_value, int size)
{
	char	*new_str;
	int		i;
	int		j;
	int		index;
	int		flag;

	index = 0;
	new_str = malloc(sizeof(char) * size);
	if (new_str == NULL)
		return (NULL);
	i = 0;
	flag = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$' && flag == 0)
		{
			flag = 1;
			while (env_value[j] != '\0')
				new_str[index++] = env_value[j++];
			j = 0;
			while (str[i] != '\0' && str[i] != '\'' && str[i] != '"'
				&& str[i] != ' ')
				i++;
		}
		new_str[index++] = str[i++];
	}
	new_str[index] = '\0';
	return (new_str);
}

char	*assign_env(char *str, char *env_value)
{
	int	value_size;
	int	node_size;
	int	i;
	int	flag;

	flag = 0;
	value_size = (int)ft_strlen(env_value);
	node_size = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$' && flag == 0)
		{
			flag = 1;
			while (str[i] != '\0' && str[i] != '\'' && str[i] != '"'
				&& str[i] != ' ')
				i++;
		}
		node_size++;
		i++;
	}
	return (change_str(str, env_value, value_size + node_size + 1));
}

char	*find_env_variable(char *value, t_env *env)
{
	int	i;
	int	size;

	if (value[0] == '$')
		value++;
	i = 0;
	size = 0;
	while (value[size] != '\0' && value[size] != '\'' && value[size] != '"'
		&& value[size] != ' ')
		size++;
	while (env[i].name)
	{
		if (ft_strncmp(value, env[i].name, size) == 0)
			return (env[i].value);
		i++;
	}
	return (NULL);
}

char	*get_env_location(char *str)
{
	int	i;
	int	in_quote;

	i = 0;
	in_quote = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
			in_quote = in_quote != 1;
		if (in_quote == 0 && str[i] == '$')
			return (&str[i]);
		i++;
	}
	return (NULL);
}

t_env	*get_env_variables(char **env)
{
	int		i;
	int		count;
	t_env	*env_variables;
	char	**value;

	count = 0;
	i = 0;
	while (env[count])
		count++;
	env_variables = malloc(sizeof(t_env) * count);
	while (env[i])
	{
		value = ft_split(env[i], '=');
		env_variables[i].name = value[0];
		env_variables[i].value = value[1];
		i++;
	}
	env_variables[i].name = NULL;
	env_variables[i].value = NULL;
	return (env_variables);
}
