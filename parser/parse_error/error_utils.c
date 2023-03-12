/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 14:21:25 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/12 14:21:34 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_error.h"

int	tokens_count(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].token != UNKNOWN)
		i++;
	return (i);
}

int	search_token_count(t_token *tokens, enum e_token type_token)
{
	int	i;
	int	return_count;
	int	count;

	i = 0;
	return_count = 0;
	count = tokens_count(tokens);
	while (i < count)
	{
		if (tokens[i].token == type_token)
			return_count++;
		i++;
	}
	return (return_count);
}
