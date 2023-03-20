/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 17:19:55 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/19 15:05:16 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens_str(t_token *token)
{
	int	i;

	i = 0;
	while (token[i].token != UNKNOWN)
	{
		free(token[i].str);
		i++;
	}
}

void	free_double_ptr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	//free last one
	free(arr);
}

int get_double_ptr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

void	free_execute(t_execute *execute)
{
	int	i;

	i = 0;
	while (execute->env[i] != NULL)
		free(execute->env[i++]);
	free(execute->env);
	i = 0;
	while (execute->export[i] != NULL)
		free(execute->export[i++]);
	free(execute->export);
	free(execute);
}
