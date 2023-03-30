/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 12:53:41 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/30 10:20:49 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../expander.h"

int	check_env_stop(char *str, int i)
{
	if (str[i] != '\0' && str[i] != '\'' && str[i] != '"' && str[i] != ' '
		&& str[i] != '$' && str[i] != '*' && str[i] != '.' && str[i] != ':'
		&& str[i] != '/' && str[i] != ',' && str[i] != '?')
		return (1);
	return (0);
}

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
	int	used_size;

	if (value[0] == '$')
		value++;
	i = 0;
	size = 0;
	while (check_env_stop(value, size))
		size++;
	while (env[i].name != NULL)
	{
		if ((int)ft_strlen(env[i].name) > size)
			used_size = ft_strlen(env[i].name);
		else
			used_size = size;
		if (ft_strncmp(value, env[i].name, used_size) == 0)
			return (env[i].value);
		i++;
	}
	return (NULL);
}

int	check_inside_quote(char *str, int *i)
{
	(*i)++;
	while (str[*i] != '\0' && str[*i] != '"')
	{
		if (str[*i] == '$')
			return (1);
		(*i)++;
	}
	return (0);
}

void	pass_single_quote(char *str, int *i)
{
	(*i)++;
	while (str[*i] != '\0' && str[*i] != '\'')
		(*i)++;
	if (str[*i + 1] != '\0')
		(*i)++;
}
