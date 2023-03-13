/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:21:32 by kali              #+#    #+#             */
/*   Updated: 2023/03/13 19:25:37 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

int	get_env_count(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	add_env(char **args, char ***env)
{
	int		i;
	char	**new_env;
	int		j;

	new_env = malloc(sizeof(char *) * (get_env_count(*env) + get_env_count(args)
				+ 1));
	i = 0;
	j = 0;
	while ((*env)[i])
	{
		new_env[i] = ft_strdup((*env)[i]);
		free((*env)[i]);
		i++;
	}
	while (args[j])
	{
		new_env[i] = ft_strdup(args[j]);
		i++;
		j++;
	}
	new_env[i] = NULL;
	free(*env);
	*env = new_env;
}

int	export(char **args, char ***env)
{
	if (args[0] == NULL)
		print_env(*env);
	else
	{
		if (ft_strchr(args[0], '=') == NULL)
			return (1);
		else
			add_env(args, env);
	}
	return (0);
}
