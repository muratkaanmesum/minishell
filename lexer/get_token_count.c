/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_count.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:41:38 by mmesum            #+#    #+#             */
/*   Updated: 2023/03/06 18:18:43 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	define_character(char *str, int *i, int *count)
{
	int	counter;

	if (my_alpha(str[*i]))
	{
		*count += 1;
		while (my_alpha(str[*i]) && str[*i] != '\0')
		{
			if (str[*i] == '"' || str[*i] == '\'')
			{
				*i += 1;
				while (str[*i] != '\0')
				{
					if (str[*i] == '"' || str[*i] == '\'')
						break ;
					*i += 1;
				}
			}
			*i += 1;
		}
	}
	if (is_redirection(str[*i]))
	{
		*count += 1;
		counter = 0;
		while (is_redirection(str[*i]) && str[*i] != '\0')
		{
			*i += 1;
			counter++;
			if (counter == 2)
				break ;
		}
	}
	if (str[*i] == '(' || str[*i] == ')')
	{
		*count += 1;
		*i += 1;
	}
}

int	get_token_count(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		define_character(str, &i, &count);
		if (str[i] == ' ')
		{
			while (str[i] == ' ' && str[i] != '\0')
				i++;
		}
	}
	return (count);
}
