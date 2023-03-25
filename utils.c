/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 17:19:55 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/23 13:28:26 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token *token)
{
	int	i;

	i = 0;
	while (token[i].token != UNKNOWN)
	{
		if (token[i].str != NULL)
		{
			free(token[i].str);
			token[i].str = NULL;
		}
		i++;
	}
	if (token != NULL)
		free(token);
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
	free(arr);
}

int	get_double_ptr_len(char **arr)
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
	free(execute->input);
	free(execute);
}

void	copy_token(t_token *dest, t_token src)
{
	dest->token = src.token;
	dest->id = src.id;
	dest->start_index = src.start_index;
	dest->end_index = src.end_index;
	if (src.str != NULL)
		dest->str = ft_strdup(src.str);
	else
		dest->str = NULL;
}
