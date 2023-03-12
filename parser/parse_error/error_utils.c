/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:22:52 by eablak            #+#    #+#             */
/*   Updated: 2023/03/12 19:22:53 by eablak           ###   ########.fr       */
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