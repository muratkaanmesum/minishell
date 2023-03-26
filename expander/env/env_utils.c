/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 12:53:41 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/25 18:32:33 by eablak           ###   ########.fr       */
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

	if (value[0] == '$')
		value++;
	i = 0;
	size = 0;
	while (check_env_stop(value, size))
		size++;
	while (env[i].name != NULL)
	{
		if (ft_strncmp(value, env[i].name, size) == 0)
			return (env[i].value);
		i++;
	}
	return (NULL);
}
int	check_inside_quote(char *str, int *i)
{
	char	c;

	c = str[*i];
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

char	*get_env_location(char *str)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && flag == 0)
			pass_single_quote(str, &i);
		if (str[i] == '"')
			flag = !flag;
		if (str[i] == '$')
		{
			if (str[i + 1] == '?')
			{
				i++;
				continue ;
			}
			if (str[i + 1] == '\0')
				return (NULL);
			return (&str[i]);
		}
		if (str[i] != '\0')
			i++;
	}
	return (NULL);
}
//ls -la
//ls -la
t_env	*get_env_variables(char **env)
{
	int		i;
	int		count;
	t_env	*env_variables;
	char	**value;

	count = 0;
	i = 0;
	env_variables = malloc(sizeof(t_env) * (get_double_ptr_len(env) + 1));
	while (env[i])
	{
		count = 0;
		value = ft_split(env[i], '=');
		while (value[count])
			count++;
		env_variables[i].name = ft_strdup(value[0]);
		if (value[1] == NULL)
			env_variables[i].value = ft_strdup("");
		else
			env_variables[i].value = ft_strdup(value[1]);
		free_double_ptr(value);
		i++;
	}
	env_variables[i].name = NULL;
	env_variables[i].value = NULL;
	return (env_variables);
}
