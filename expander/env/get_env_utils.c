/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:44:24 by eablak            #+#    #+#             */
/*   Updated: 2023/03/29 13:49:57 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../expander.h"

void	env_location_utils(char *str, int *i, int *flag)
{
	if (str[*i] == '\'' && *flag == 0)
		pass_single_quote(str, i);
	if (str[*i] == '"')
		*flag = *flag != 1;
}

char	*get_env_location(char *str)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	while (str[i] != '\0')
	{
		env_location_utils(str, &i, &flag);
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
