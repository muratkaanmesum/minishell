/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_side_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 17:02:36 by eablak            #+#    #+#             */
/*   Updated: 2023/03/29 20:48:12 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

int	is_right_side(char *str, int index)
{
	int		count;

	count = 0;
	if (index != 0)
	{
		if (str[index - 1] == '*')
		{
			while (str[index] != '\0')
			{
				if (str[index] == '*')
					return (0);
				index += 1;
				count++;
			}
			if (count > 0)
				return (1);
			else
				return (0);
		}
	}
	return (0);
}

void	right_side_prcss(char *str, int *index, int *j, char *new_str)
{
	while (str[*index] != '\0')
	{
		new_str[*j] = str[*index];
		(*j)++;
		*index += 1;
	}
	new_str[*j] = '\0';
}

char	*right_side(char *str, int *index)
{
	char	*new_str;
	int		count;
	int		j;

	count = 0;
	new_str = NULL;
	if (*index != 0)
	{
		if (str[*index - 1] == '*')
		{
			while (str[*index] != '\0')
			{
				if (str[*index] == '*')
					return (NULL);
				*index += 1;
				count++;
			}
			new_str = malloc(sizeof(char) * (count + 1));
			*index -= count;
			j = 0;
			right_side_prcss(str, index, &j, new_str);
		}
		return (new_str);
	}
	return (NULL);
}
