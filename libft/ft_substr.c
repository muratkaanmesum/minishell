/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 10:34:56 by eablak            #+#    #+#             */
/*   Updated: 2022/10/15 12:49:15 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*alan;
	size_t	i;
	size_t	size;

	i = 0;
	if (!s)
		return (0);
	if ((unsigned int)ft_strlen(s) < start)
		return (ft_strdup(""));
	size = ft_strlen(s + start);
	if (size < len)
		len = size;
	alan = (char *)malloc(sizeof(char) * len + 1);
	if (alan == NULL)
		return (NULL);
	if (start < ft_strlen(s))
	{
		while (i < len && s[start])
		{
			*(alan + i) = *(s + start++);
			i++;
		}
	}
	*(alan + i) = '\0';
	return (alan);
}
