/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:33:16 by eablak            #+#    #+#             */
/*   Updated: 2022/10/14 16:12:55 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last;
	int		i;

	last = 0;
	i = 0;
	c = (unsigned char)c;
	if (c == 0)
		return ((char *) s + ft_strlen(s));
	while (s[i] != '\0')
	{
		if (s[i] == c)
			last = ((char *)s + i);
		i++;
	}
	return (last);
}
