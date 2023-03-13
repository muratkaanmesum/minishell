/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:21:32 by kali              #+#    #+#             */
/*   Updated: 2023/03/13 18:52:53 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

int get_env_count(char **env)
{
	int i = 0;
	while(env[i])
	i++;
	return i;
}

int	add_env(char *args, char **env)
{
	int		i;
	
	int env_count;
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], args, ft_strchr(env[i], '=') - env[i]) == 0)
		{
			free(env[i]);
			env[i] = ft_strdup(args);
			return (0);
		}
		i++;
	}
	env[i] = ft_strdup(args);
	env[i + 1] = NULL;
	return (0);
}

int	export(char **args, char **env)
{
	if (args[0] == NULL)
		print_env(env);
	else
	{
		if (ft_strchr(args[0], '=') == NULL)
			return (1);
		else
			add_env(args[0], env);
	}
	return (0);
}
