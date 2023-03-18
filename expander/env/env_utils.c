/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 12:53:41 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/18 13:54:37 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../expander.h"

void	free_env(t_env *env)
{
	int	i;

	i = 0;
	while (env[i].name != NULL)
	{
		free(env[i].name);
		free(env[i].value);
		i++;
	}
	free(env);
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
		{
			if (str[i + 1] == '\0')
				return (NULL);
			return (&str[i]);
		}
		i++;
	}
	return (NULL);
}

t_env	*get_env_variables(char **env, t_node *node)
{
	int		i;
	int		count;
	t_env	*env_variables;
	char	**value;

	count = 0;
	i = 0;
	while (env[count] != NULL)
		count++;
	env_variables = malloc(sizeof(t_env) * (count + 2));
	while (env[i])
	{
		count = 0;
		value = ft_split(env[i], '=');
		while (value[count])
			count++;
		env_variables[i].name = ft_strdup(value[0]);
		env_variables[i].value = ft_strdup(value[1]);
		free_double_ptr(value);
		i++;
	}
	env_variables[i].name = ft_strdup("?");
	env_variables[i].value = ft_itoa(get_last_execute_code(node));
	env_variables[i + 1].name = NULL;
	env_variables[i + 1].value = NULL;
	return (env_variables);
}
