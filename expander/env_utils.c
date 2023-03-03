/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 12:53:41 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/03 16:49:57 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*find_env_variable(char *value, t_env *env)
{
	int	i;
	int	size;

	if (value[0] == '$')
		value++;
	i = 0;
	size = 0;
	while (value[size] != '\0' && value[size] != '\'' && value[size] != '"'
		&& value[size] != ' ' && value[size] != '$')
		size++;
	while (env[i].name != NULL)
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
	while (env[count] != NULL)
		count++;
	env_variables = malloc(sizeof(t_env) * count + 1);
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
