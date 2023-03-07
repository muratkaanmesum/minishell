/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:21:32 by kali              #+#    #+#             */
/*   Updated: 2023/03/07 10:51:54 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

int	add_env(char *args, char **env)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = env;
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
}
