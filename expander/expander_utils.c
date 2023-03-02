/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 12:53:41 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/02 13:28:34 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*find_env_variable(char *value, t_env *env)
{
	int	i;

	if (value[0] == '$')
		value++;
	i = 0;
	while (env[i].name)
	{
		if (ft_strncmp(value, env[i].name, ft_strlen(value)) != 0)
			i++;
	}
	return (env[i].value);
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
	return (env_variables);
}
